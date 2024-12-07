#include "fc_number_formatter.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


#define TMP_BUF_SIZE (128)

static const char *_digits = "0123456789ABCDEF";
static char _tmp_buf[TMP_BUF_SIZE];

static inline int _max(int a, int b) {
  return a > b ? a : b;
}

int _format_u(fc_number_formatter_config_t config, uint64_t number, char *buf, size_t buf_size) {
  uint8_t tmp_buf_idx = 0;
  
  do {
    if (tmp_buf_idx >= TMP_BUF_SIZE) return -1;
    _tmp_buf[tmp_buf_idx++] = _digits[number % config.base];
    number /= config.base;
  } while (number != 0);
  
  uint8_t buf_idx = 0;
  
  uint8_t sep_grp_size = config.base == FC_BASE_DEC ? 3 : 4;
  
  while (tmp_buf_idx != 0) {
    if (buf_idx >= buf_size) return -1;
    buf[buf_idx++] = _tmp_buf[--tmp_buf_idx];
    if (buf_idx >= buf_size) return -1;
    if (config.sep && tmp_buf_idx % sep_grp_size == 0 && tmp_buf_idx != 0) buf[buf_idx++] = '\'';
  }
  
  if (buf_idx >= buf_size) return -1;
  buf[buf_idx] = '\0';
  return 0;
}

int _format_i(fc_number_formatter_config_t config, int64_t number, char *buf, size_t buf_size) {
  bool sign = false;
  uint64_t number_unsigned = number;
  if (number < 0) {
    sign = true;
    number_unsigned = -number;
  }
  if (0 >= buf_size) return -1;
  if (sign) {
    buf[0] = '-';
    if (_format_u(config, number_unsigned, buf + 1, buf_size - 1)) return -1;
  } else {
    if (_format_u(config, number_unsigned, buf, buf_size)) return -1;
  }
  
  return 0;
}

void _trim_zero(char *buf) {
  char *dec = strchr(buf, '.');
  if (!dec) return;
  char *end = dec + strlen(dec) - 1;
  while (end > dec && *end == '0') *end-- = '\0';
  if (end == dec) *end = '\0';
}

void _add_exp(int e, char *buf, size_t buflen) {
  if (e == 0) return;
  sprintf(buf + strlen(buf), "e%d", e);
}

void _add_separator(char *buf) {
  char *dec = strchr(buf, '.');
  if (buf[0] == '-') ++buf;
  if (!dec) dec = buf + strlen(buf);
  size_t digit_count = dec - buf;
  strcpy(_tmp_buf, buf);
  int buf_idx = 0;
  for (int i = 0; i < digit_count; ++i) {
    buf[buf_idx++] = _tmp_buf[i];
    if ((digit_count - i - 1) % 3 == 0 && digit_count - i - 1 != 0) {
      buf[buf_idx++] = '\'';
    }
  }
  strcpy(&buf[buf_idx], &_tmp_buf[digit_count]);
}

void _format_sci(fc_number_formatter_config_t config, double number, bool trailing_zeros, char *buf, size_t buflen) {
  char fmt[8];
  int e = 0;
  
  if (number != 0) {
    e = floor(log10(fabs(number)));
    number /= pow(10, e);
  }
  
  if (trailing_zeros) {
    snprintf(fmt, sizeof(fmt), "%%.%df", config.sig - 1);
    snprintf(buf, buflen, fmt, number);
  } else {
    snprintf(buf, buflen, "%.*g", config.sig - 1, number);
  }
  
  size_t len = strnlen(buf, buflen);
  _add_exp(e, buf + len, buflen - len);
}

void _format_eng(fc_number_formatter_config_t config, double number, char *buf, size_t buflen) {
  char fmt[8];
  if (number == 0) {
    snprintf(fmt, sizeof(fmt), "%%.%df", config.sig - 1);
    snprintf(buf, buflen, fmt, number);
    return;
  }
  
  bool neg = number < 0;
  if (neg) {
    number = -number;
    *buf++ = '-';
    --buflen;
  }
  
  int e = log10(number);
  e = e > 0 ? e / 3 * 3 : (-e + 3) / 3 * -3;
  number *= pow(10, -e);
  
  int int_digits = 1;
  if (number >= 1000) {
    number /= 1000;
    e += 3;
  } else if (number >= 100) int_digits = 3;
  else if (number >= 10) int_digits = 2;
  
  int frac_digits = _max(config.sig - int_digits, 0);
  
  if (frac_digits > 0) snprintf(fmt, sizeof(fmt), "%%.%df", frac_digits);
  else snprintf(fmt, sizeof(fmt), "%%.0f");
  snprintf(buf, buflen, fmt, number);
  size_t len = strnlen(buf, buflen);
  _add_exp(e, buf + len, buflen - len);
}

void _format_all(fc_number_formatter_config_t config, double number, char *buf, size_t buflen) {
  snprintf(buf, buflen, "%.17g", number);
  _trim_zero(buf);
  if (!config.sep) return;
  _add_separator(buf[0] == '-' ? buf + 1 : buf);
}

int _count_digits(char *str) {
  int count = 0;
  while (*str) if (isdigit(*str++)) ++count;
  return count;
}

void _format_f(fc_number_formatter_config_t config, double number, char *buf, size_t buflen) {
  if (isnan(number)) { snprintf(buf, buflen, "NaN"); return; }
  if (isinf(number)) { snprintf(buf, buflen, "%sInf", number < 0 ? "-" : ""); return; }
  
  if (config.format == FC_NUMBER_FORMAT_SCI) {
    _format_sci(config, number, true, buf, buflen);
  } else if (config.format == FC_NUMBER_FORMAT_ENG) {
    _format_eng(config, number, buf, buflen);
  } else if (config.format == FC_NUMBER_FORMAT_ALL) {
    snprintf(buf, buflen, "%.17g", number);
    _trim_zero(buf);
    int total_digits = _count_digits(buf);
    if (total_digits <= config.lim) _format_all(config, number, buf, buflen);
    else _format_sci(config, number, false, buf, buflen);
  } else _format_all(config, number, buf, buflen);
}

void _format_c(fc_number_formatter_config_t config, double complex number, char *buf, size_t buflen) {
  _format_f(config, creal(number), buf, buflen);
  if (cimag(number) == 0) return;
  size_t len = strnlen(buf, buflen);
  buf += len;
  buflen -= len;
  if (cimag(number) >= 0) {
    *buf++ = '+';
    --buflen;
  }
  _format_f(config, cimag(number), buf, buflen);
  len = strnlen(buf, buflen);
  *buf++ = 'i';
  *buf++ = '\0';
}


void fc_format(fc_number_formatter_config_t config, fc_scalar_t number, char *buf, size_t buflen) {
  if (number.type == FC_SCALAR_TYPE_I) {
    _format_i(config, number.data.val_i, buf, buflen);
    return;
  }
  
  if (number.type == FC_SCALAR_TYPE_F) {
    _format_f(config, number.data.val_f, buf, buflen);
  }
  
  if (number.type == FC_SCALAR_TYPE_C) {
    _format_c(config, number.data.val_f, buf, buflen);
  }
}