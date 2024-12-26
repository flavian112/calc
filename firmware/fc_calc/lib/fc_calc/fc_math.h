#ifndef FC_MATH_H
#define FC_MATH_H

#include "fc_scalar.h"

#ifdef __cplusplus
extern "C" {
#endif

fc_scalar_t fc_math_add(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_subtract(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_negate(fc_scalar_t a);

fc_scalar_t fc_math_multiply(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_divide(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_inverse(fc_scalar_t a);
fc_scalar_t fc_math_modulo(fc_scalar_t a, fc_scalar_t b);

fc_scalar_t fc_math_square(fc_scalar_t a);
fc_scalar_t fc_math_squareroot(fc_scalar_t a);
fc_scalar_t fc_math_exp(fc_scalar_t a);
fc_scalar_t fc_math_exp2(fc_scalar_t a);
fc_scalar_t fc_math_exp10(fc_scalar_t a);
fc_scalar_t fc_math_ln(fc_scalar_t a);
fc_scalar_t fc_math_log2(fc_scalar_t a);
fc_scalar_t fc_math_log10(fc_scalar_t a);
fc_scalar_t fc_math_log(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_power(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_root(fc_scalar_t a, fc_scalar_t b);

fc_scalar_t fc_math_sin(fc_scalar_t a);
fc_scalar_t fc_math_cos(fc_scalar_t a);
fc_scalar_t fc_math_tan(fc_scalar_t a);
fc_scalar_t fc_math_asin(fc_scalar_t a);
fc_scalar_t fc_math_acos(fc_scalar_t a);
fc_scalar_t fc_math_atan(fc_scalar_t a);
fc_scalar_t fc_math_sinh(fc_scalar_t a);
fc_scalar_t fc_math_cosh(fc_scalar_t a);
fc_scalar_t fc_math_tanh(fc_scalar_t a);
fc_scalar_t fc_math_asinh(fc_scalar_t a);
fc_scalar_t fc_math_acosh(fc_scalar_t a);
fc_scalar_t fc_math_atanh(fc_scalar_t a);

fc_scalar_t fc_math_not(fc_scalar_t a);
fc_scalar_t fc_math_and(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_or(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_xor(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_nand(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_nor(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_xnor(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sll(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_srl(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sra(fc_scalar_t a, fc_scalar_t b);

fc_scalar_t fc_math_lnot(fc_scalar_t a);
fc_scalar_t fc_math_land(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_lor(fc_scalar_t a, fc_scalar_t b);

fc_scalar_t fc_math_lt(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_le(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_eq(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_ne(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_ge(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_gt(fc_scalar_t a, fc_scalar_t b);

fc_scalar_t fc_math_abs(fc_scalar_t a);
fc_scalar_t fc_math_arg(fc_scalar_t a);
fc_scalar_t fc_math_conj(fc_scalar_t a);
fc_scalar_t fc_math_real(fc_scalar_t a);
fc_scalar_t fc_math_imag(fc_scalar_t a);

fc_scalar_t fc_math_cvt(fc_scalar_t a, fc_scalar_type_t type);

#ifdef __cplusplus
}
#endif

#endif
