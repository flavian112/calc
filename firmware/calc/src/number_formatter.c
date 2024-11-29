#include "number_formatter.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

void nf_trim_trailing_zeros(char *str) {
  char *end = str + strlen(str) - 1;
  while (end > str && *end == '0') *end-- = '\0';
  if (*end == '.') *end = '\0';
}

void nf_format_all(char *buf, double val, int prec) {
  if (val == 0 || (val >= 0.0001 && val < 1000000)) {
    sprintf(buf, "%.*f", prec, val);
    nf_trim_trailing_zeros(buf);
  } else {
    sprintf(buf, "%.*E", prec, val);
  }
}

void nf_format_eng(char *buf, double val, int prec) {
  int exp = (int)floor(log10(fabs(val)) / 3) * 3;
  double mantissa = val / pow(10, exp);
  sprintf(buf, "%.*f", prec, mantissa);
  nf_trim_trailing_zeros(buf);
  sprintf(buf + strlen(buf), "E%d", exp);
}

void nf_format_double(nf_number_format_t mode, double val, int prec, char *out) {
  switch (mode) {
    case NF_NUMBER_FORMAT_FIX:
      sprintf(out, "%.*f", prec, val);
      nf_trim_trailing_zeros(out);
      break;
    case NF_NUMBER_FORMAT_SCI:
      sprintf(out, "%.*E", prec, val);
      break;
    case NF_NUMBER_FORMAT_ENG:
      nf_format_eng(out, val, prec);
      break;
    case NF_NUMBER_FORMAT_ALL:
      nf_format_all(out, val, prec);
      break;
    default:
      return;
  }
}

void nf_format_complex(nf_number_format_t mode, number_t val, int prec, char *out) {
  nf_format_double(mode, creal(val.cdval), prec, out);
  if (cimag(val.cdval) == 0) return;
  size_t len = strlen(out);
  out[len++] = 'i';
  nf_format_double(mode, cimag(val.cdval), prec, &out[len]);
}
