#include "fc_format.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>

#define _TMP_BUF_LEN (256)

static char _tmp_buf[_TMP_BUF_LEN] = {0};

static void _format_u_bin(fc_scalar_u_t val, char *buf, size_t buflen) {
  buf[buflen - 1] = '\0';
  unsigned n_digits = 64 - __builtin_clzll(val | 1);
  if (n_digits >= buflen) return;
  for (int i = 0; i < n_digits; ++i) {
    buf[n_digits - i - 1] = '0' + (val & 1);
    val >>= 1;
  }
  buf[n_digits] = '\0';
}

static void _format_u(fc_scalar_u_t val, fc_base_t base, char *buf, size_t buflen) {
  switch (base) {
    case FC_BASE_BIN: _format_u_bin(val, buf, buflen); break;
    case FC_BASE_OCT: snprintf(buf, buflen, "%llo", val); break;
    case FC_BASE_DEC: snprintf(buf, buflen, "%llu", val); break;
    case FC_BASE_HEX: snprintf(buf, buflen, "%llX", val); break;
  }
}

static void _format_i(fc_scalar_i_t val, fc_base_t base, char *buf, size_t buflen) {
  bool neg = false;
  if (val < 0) {
    neg = true;
    val = -val;
  }
  if (neg) {
    *buf++ = '-';
    --buflen;
  }
  _format_u(val, base, buf, buflen);
}

static void _format_f(fc_scalar_f_t val, fc_base_t base, char *buf, size_t buflen) {
  if (isnan(val)) { snprintf(buf, buflen, "NaN"); return; }
  if (isinf(val)) { if (val < 0) *buf++ = '-'; snprintf(buf, buflen - 1, "Inf"); return; }
  if (base == FC_BASE_DEC) {
    snprintf(buf, buflen, "%g", val);
  } else {
    snprintf(buf, buflen, "%g", val); // TODO
  }
  
  if (strlen(buf) == 2 && buf[0] == '-' && buf[1] == '0') {
    snprintf(buf, buflen, "0");
  }

  char *ptr = strchr(buf, '+');
  if (ptr) memmove(ptr, ptr + 1, strlen(ptr));
}

static void _format_c(fc_scalar_c_t val, fc_base_t base, char *buf, size_t buflen) {
  if (isnan(creal(val)) || isnan(cimag(val))) { snprintf(buf, buflen, "NaN"); return; }
  char *real = _tmp_buf;
  char *imag = _tmp_buf + _TMP_BUF_LEN / 2;
  _format_f(creal(val), base, real, _TMP_BUF_LEN / 2);
  _format_f(cimag(val), base, imag, _TMP_BUF_LEN / 2);
  bool real_zero = strlen(real) == 1 && real[0] == '0';
  bool imag_zero = strlen(imag) == 1 && imag[0] == '0';
  
  if (real_zero && imag_zero) {
    snprintf(buf, buflen, "0");
  } else if (!real_zero && !imag_zero) {
    snprintf(buf, buflen, "%s,%si", real, imag);
  } else if (!real_zero && imag_zero) {
    snprintf(buf, buflen, "%s", real);
  } else if (real_zero && !imag_zero) {
    snprintf(buf, buflen, "%si", imag);
  }
}

void fc_format(fc_scalar_t scalar, fc_base_t base, char *buf, size_t buflen) {
  switch (scalar.type) {
    case FC_SCALAR_TYPE_U: _format_u(scalar.data.val_u, base, buf, buflen); break;
    case FC_SCALAR_TYPE_I: _format_i(scalar.data.val_i, base, buf, buflen); break;
    case FC_SCALAR_TYPE_F: _format_f(scalar.data.val_f, base, buf, buflen); break;
    case FC_SCALAR_TYPE_C: _format_c(scalar.data.val_c, base, buf, buflen); break;
  }
}
