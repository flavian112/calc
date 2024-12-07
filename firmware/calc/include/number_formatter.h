#ifndef NUMBER_FORMATTER_H
#define NUMBER_FORMATTER_H

#include <complex.h>
#include "fc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

enum nf_number_format {
  NF_NUMBER_FORMAT_FIX,
  NF_NUMBER_FORMAT_SCI,
  NF_NUMBER_FORMAT_ENG,
  NF_NUMBER_FORMAT_ALL
} typedef nf_number_format_t;

void nf_format_double(nf_number_format_t mode, double val, int prec, char *out);
void nf_format_complex(nf_number_format_t mode, fc_scalar_t val, int prec, char *out);



#ifdef __cplusplus
}
#endif

#endif