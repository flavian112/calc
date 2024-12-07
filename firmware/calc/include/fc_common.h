#ifndef FC_COMMON_H
#define FC_COMMON_H

#include <stdint.h>
#include <complex.h>

#ifdef __cplusplus
extern "C" {
#endif

enum fc_base_t {
  FC_BASE_BIN = 2,
  FC_BASE_OCT = 8,
  FC_BASE_DEC = 10,
  FC_BASE_HEX = 16
} typedef fc_base_t;

union fc_scalar_t {
  char data[16];
  double complex val_c;
  double val_d;
  int64_t val_i;
} typedef fc_scalar_t;

enum fc_scalar_type_t {
  FC_SCALAR_TYPE_C,
  FC_SCALAR_TYPE_D,
  FC_SCALAR_TYPE_I
} typedef fc_scalar_type_t;

#ifdef __cplusplus
}
#endif

#endif
