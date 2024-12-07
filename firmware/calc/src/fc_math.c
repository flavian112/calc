#include "fc_math.h"
#include <string.h>

fc_scalar_t fc_math_set_c(double complex val) {
  fc_scalar_t result;
  result.val_c = val;
  return result;
}
fc_scalar_t fc_math_add_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = b.val_c + a.val_c;
  return result;
}
fc_scalar_t fc_math_sub_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = b.val_c - a.val_c;
  return result;
}
fc_scalar_t fc_math_neg_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = -a.val_c;
  return result;
}

fc_scalar_t fc_math_mul_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = b.val_c * a.val_c;
  return result;
}
fc_scalar_t fc_math_div_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = b.val_c / a.val_c;
  return result;
}
fc_scalar_t fc_math_inv_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = 1 / a.val_c;
  return result;
}

fc_scalar_t fc_math_real_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_d = creal(a.val_c);
  return result;
}
fc_scalar_t fc_math_imag_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_d = cimag(a.val_c);
  return result;
}
fc_scalar_t fc_math_abs_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_d = cabs(a.val_c);
  return result;
}
fc_scalar_t fc_math_arg_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_d = carg(a.val_c);
  return result;
}
fc_scalar_t fc_math_conj_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = conj(a.val_c);
  return result;
}

fc_scalar_t fc_math_sin_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = csin(a.val_c);
  return result;
}
fc_scalar_t fc_math_cos_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = ccos(a.val_c);
  return result;
}
fc_scalar_t fc_math_tan_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = ctan(a.val_c);
  return result;
}

fc_scalar_t fc_math_asin_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = casin(a.val_c);
  return result;
}
fc_scalar_t fc_math_acos_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = cacos(a.val_c);
  return result;
}
fc_scalar_t fc_math_atan_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = catan(a.val_c);
  return result;
}

fc_scalar_t fc_math_sinh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = csinh(a.val_c);
  return result;
}
fc_scalar_t fc_math_cosh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = ccosh(a.val_c);
  return result;
}
fc_scalar_t fc_math_tanh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = ctanh(a.val_c);
  return result;
}

fc_scalar_t fc_math_asinh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = casinh(a.val_c);
  return result;
}
fc_scalar_t fc_math_acosh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = cacosh(a.val_c);
  return result;
}
fc_scalar_t fc_math_atanh_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = catanh(a.val_c);
  return result;
}

fc_scalar_t fc_math_exp_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = cexp(a.val_c);
  return result;
}
fc_scalar_t fc_math_exp2_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = cpow(2, a.val_c);
  return result;
}
fc_scalar_t fc_math_exp10_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = cpow(10, a.val_c);
  return result;
}
fc_scalar_t fc_math_pow_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = cpow(b.val_c, a.val_c);
  return result;
}
fc_scalar_t fc_math_ln_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = clog(a.val_c);
  return result;
}
fc_scalar_t fc_math_log2_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = clog(a.val_c) / clog(2);
  return result;
}
fc_scalar_t fc_math_log10_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = clog(a.val_c) / clog(10);
  return result;
}
fc_scalar_t fc_math_log_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = clog(b.val_c) / clog(a.val_c);
  return result;
}
fc_scalar_t fc_math_sq_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = a.val_c * a.val_c;
  return result;
}
fc_scalar_t fc_math_sqrt_c(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_c = csqrt(a.val_c);
  return result;
}
fc_scalar_t fc_math_root_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_c = cpow(b.val_c, 1 / a.val_c);
  return result;
}


fc_scalar_t fc_math_set_d(double val) {
  fc_scalar_t result;
  result.val_d = val;
  return result;
}

fc_scalar_t fc_math_cmplt_d(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_d < a.val_d;
  return result;
}
fc_scalar_t fc_math_cmpgt_d(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_d > a.val_d;
  return result;
}

fc_scalar_t fc_math_sign_d(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_i = 0;
  if (a.val_d > 0) result.val_i = 1;
  else if (a.val_d < 0) result.val_i = -1;
  return result;
}

fc_scalar_t fc_math_max_d(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_d = b.val_d > a.val_d ? b.val_d : a.val_d;
  return result;
}
fc_scalar_t fc_math_min_d(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_d = b.val_d < a.val_d ? b.val_d : a.val_d;
  return result;
}


fc_scalar_t fc_math_set_i(int64_t val) {
  fc_scalar_t result;
  result.val_i = val;
  return result;
}

fc_scalar_t fc_math_inc_i(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_i = a.val_i + 1;
  return result;
}
fc_scalar_t fc_math_dec_i(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_i = a.val_i - 1;
  return result;
}
fc_scalar_t fc_math_add_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i + a.val_i;
  return result;
}
fc_scalar_t fc_math_sub_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i - a.val_i;
  return result;
}
fc_scalar_t fc_math_neg_i(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_i = -a.val_i;
  return result;
}

fc_scalar_t fc_math_mul_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i * a.val_i;
  return result;
}
fc_scalar_t fc_math_div_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i / a.val_i;
  return result;
}
fc_scalar_t fc_math_mod_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i % a.val_i;
  return result;
}

fc_scalar_t fc_math_not_i(fc_scalar_t a) {
  fc_scalar_t result;
  result.val_i = ~a.val_i;
  return result;
}
fc_scalar_t fc_math_or_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i | a.val_i;
  return result;
}
fc_scalar_t fc_math_and_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i & a.val_i;
  return result;
}
fc_scalar_t fc_math_nor_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = ~(b.val_i | a.val_i);
  return result;
}
fc_scalar_t fc_math_nand_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = ~(b.val_i & a.val_i);
  return result;
}
fc_scalar_t fc_math_xor_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i ^ a.val_i;
  return result;
}
fc_scalar_t fc_math_xnor_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = ~(b.val_i ^ a.val_i);
  return result;
}
fc_scalar_t fc_math_sra_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i >> a.val_i;
  return result;
}
fc_scalar_t fc_math_sll_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i << a.val_i;
  return result;
}
fc_scalar_t fc_math_srl_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = (uint64_t)b.val_i >> a.val_i;
  return result;
}

fc_scalar_t fc_math_cmpeq_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i == a.val_i;
  return result;
}
fc_scalar_t fc_math_cmple_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i <= a.val_i;
  return result;
}
fc_scalar_t fc_math_cmplt_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i < a.val_i;
  return result;
}
fc_scalar_t fc_math_cmpge_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i >= a.val_i;
  return result;
}
fc_scalar_t fc_math_cmpgt_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i > a.val_i;
  return result;
}

fc_scalar_t fc_math_max_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i > a.val_i ? b.val_i : a.val_i;
  return result;
}
fc_scalar_t fc_math_min_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t result;
  result.val_i = b.val_i < a.val_i ? b.val_i : a.val_i;
  return result;
}



fc_scalar_t fc_math_cvt_d_to_c(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_c = a.val_d;
  return result;
}
fc_scalar_t fc_math_cvt_i_to_c(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_c = a.val_i;
  return result;
}
fc_scalar_t fc_math_cvt_c_to_d(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_d = creal(a.val_c);
  return result;
}
fc_scalar_t fc_math_cvt_i_to_d(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_d = a.val_i;
  return result;
}
fc_scalar_t fc_math_cvt_c_to_i(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_i = creal(a.val_c);
  return result;
}
fc_scalar_t fc_math_cvt_d_to_i(fc_scalar_t a) {
  fc_scalar_t result;
  memset(&result, 0, sizeof(fc_scalar_t));
  result.val_i = a.val_d;
  return result;
}
