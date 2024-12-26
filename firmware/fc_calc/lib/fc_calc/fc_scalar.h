#ifndef FC_SCALAR_H
#define FC_SCALAR_H

#include <complex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long long fc_scalar_u_t;
typedef long long fc_scalar_i_t;
typedef double fc_scalar_f_t;
typedef double complex fc_scalar_c_t;

typedef enum {
  FC_BASE_BIN = 2,
  FC_BASE_OCT = 8,
  FC_BASE_DEC = 10,
  FC_BASE_HEX = 16
} fc_base_t;

typedef enum {
  FC_SCALAR_TYPE_U,
  FC_SCALAR_TYPE_I,
  FC_SCALAR_TYPE_F,
  FC_SCALAR_TYPE_C
} fc_scalar_type_t;

typedef union {
  fc_scalar_u_t val_u;
  fc_scalar_i_t val_i;
  fc_scalar_f_t val_f;
  fc_scalar_c_t val_c;
} fc_scalar_data_t;

typedef struct {
  fc_scalar_data_t data;
  fc_scalar_type_t type;
} fc_scalar_t;

fc_scalar_t fc_scalar_u(fc_scalar_u_t val);
fc_scalar_t fc_scalar_i(fc_scalar_i_t val);
fc_scalar_t fc_scalar_f(fc_scalar_f_t val);
fc_scalar_t fc_scalar_c(fc_scalar_c_t val);

fc_scalar_type_t fc_scalar_cast_type(fc_scalar_type_t a, fc_scalar_type_t b);

#ifdef __cplusplus
}
#endif

#endif
