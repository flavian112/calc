#include "fc_math.h"

#include <math.h>

fc_scalar_t fc_math_set_c(double complex val) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = val;
  return res;
}

fc_scalar_t fc_math_add_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = fc_math_cvt_c(a).data.val_c + fc_math_cvt_c(b).data.val_c;
  return res;
}

fc_scalar_t fc_math_sub_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = fc_math_cvt_c(a).data.val_c - fc_math_cvt_c(b).data.val_c;
  return res;
}

fc_scalar_t fc_math_neg_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = -fc_math_cvt_c(a).data.val_c;
  return res;
}

fc_scalar_t fc_math_mul_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = fc_math_cvt_c(a).data.val_c * fc_math_cvt_c(b).data.val_c;
  return res;
}

fc_scalar_t fc_math_div_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = fc_math_cvt_c(a).data.val_c / fc_math_cvt_c(b).data.val_c;
  return res;
}

fc_scalar_t fc_math_inv_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = 1 / fc_math_cvt_c(a).data.val_c;
  return res;
}

fc_scalar_t fc_math_sin_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = csin(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_cos_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = ccos(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_tan_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = ctan(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_asin_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = casin(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_acos_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cacos(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_atan_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = catan(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_sinh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = csinh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_cosh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = ccosh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_tanh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = tanh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_asinh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = casinh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_acosh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cacosh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_atanh_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = catanh(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_exp_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cexp(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_exp2_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cpow(2, fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_exp10_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cpow(10, fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_pow_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cpow(fc_math_cvt_c(a).data.val_c, fc_math_cvt_c(b).data.val_c);
  return res;
}

fc_scalar_t fc_math_ln_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = clog(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_log2_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = clog(fc_math_cvt_c(a).data.val_c) / clog(2);
  return res;
}

fc_scalar_t fc_math_log10_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = clog(fc_math_cvt_c(a).data.val_c) / clog(10);
  return res;
}

fc_scalar_t fc_math_log_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = clog(fc_math_cvt_c(a).data.val_c) / clog(fc_math_cvt_c(b).data.val_c);
  return res;
}

fc_scalar_t fc_math_sq_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  double complex ac = fc_math_cvt_c(a).data.val_c;
  res.data.val_c = ac * ac;
  return res;
}

fc_scalar_t fc_math_sqrt_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = csqrt(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_root_cc_c(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = cpow(fc_math_cvt_c(a).data.val_c, 1 / fc_math_cvt_c(b).data.val_c);
  return res;
}

fc_scalar_t fc_math_real_c_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = creal(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_imag_c_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = cimag(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_abs_c_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = cabs(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_arg_c_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = carg(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_conj_c_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = conj(fc_math_cvt_c(a).data.val_c);
  return res;
}

fc_scalar_t fc_math_set_f(double val) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = val;
  return res;
}

fc_scalar_t fc_math_cmplt_ff_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_f(a).data.val_f < fc_math_cvt_f(b).data.val_f;
  return res;
}

fc_scalar_t fc_math_cmpgt_ff_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_f(a).data.val_f > fc_math_cvt_f(b).data.val_f;
  return res;
}

fc_scalar_t fc_math_sign_f_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  double af = fc_math_cvt_f(a).data.val_f;
  res.data.val_i = af ? 1 : af < 0 ? -1 : 0;
  return res;
}

fc_scalar_t fc_math_max_ff_f(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  double af = fc_math_cvt_f(a).data.val_f;
  double bf = fc_math_cvt_f(b).data.val_f;
  res.data.val_f = af > bf ? af : bf;
  return res;
}

fc_scalar_t fc_math_min_ff_f(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  double af = fc_math_cvt_f(a).data.val_f;
  double bf = fc_math_cvt_f(b).data.val_f;
  res.data.val_f = af < bf ? af : bf;
  return res;
}

fc_scalar_t fc_math_set_i(int64_t val) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = val;
  return res;
}

fc_scalar_t fc_math_inc_i_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i + 1;
  return res;
}

fc_scalar_t fc_math_dec_i_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i - 1;
  return res;
}

fc_scalar_t fc_math_add_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i + fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_sub_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i - fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_neg_i_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = -fc_math_cvt_i(a).data.val_i;
  return res;
}

fc_scalar_t fc_math_mul_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i * fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_div_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i / fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_mod_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i % fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_not_i_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = ~fc_math_cvt_i(a).data.val_i;
  return res;
}

fc_scalar_t fc_math_or_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i | fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_and_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i & fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_xor_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i ^ fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_nor_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = ~(fc_math_cvt_i(a).data.val_i | fc_math_cvt_i(b).data.val_i);
  return res;
}

fc_scalar_t fc_math_nand_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = ~(fc_math_cvt_i(a).data.val_i & fc_math_cvt_i(b).data.val_i);
  return res;
}

fc_scalar_t fc_math_xnor_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = ~(fc_math_cvt_i(a).data.val_i ^ fc_math_cvt_i(b).data.val_i);
  return res;
}

fc_scalar_t fc_math_sra_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i >> fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_sll_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i << fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_srl_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = (uint64_t)fc_math_cvt_i(a).data.val_i >> fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_cmpeq_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i == fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_cmple_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i <= fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_cmplt_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i < fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_cmpge_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i >= fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_cmpgt_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = fc_math_cvt_i(a).data.val_i > fc_math_cvt_i(b).data.val_i;
  return res;
}

fc_scalar_t fc_math_max_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  int64_t ai = fc_math_cvt_i(a).data.val_i;
  int64_t bi = fc_math_cvt_i(b).data.val_i;
  res.data.val_i = ai > bi ? ai : bi;
  return res;
}

fc_scalar_t fc_math_min_ii_i(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  int64_t ai = fc_math_cvt_i(a).data.val_i;
  int64_t bi = fc_math_cvt_i(b).data.val_i;
  res.data.val_i = ai < bi ? ai : bi;
  return res;
}

fc_scalar_t fc_math_cvt_f_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = a.data.val_f;
  return res;
}

fc_scalar_t fc_math_cvt_i_c(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_C;
  res.data.val_c = a.data.val_i;
  return res;
}

fc_scalar_t fc_math_cvt_c_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = creal(a.data.val_c);
  return res;
}

fc_scalar_t fc_math_cvt_i_f(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_F;
  res.data.val_f = a.data.val_i;
  return res;
}

fc_scalar_t fc_math_cvt_c_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = creal(a.data.val_c);
  return res;
}

fc_scalar_t fc_math_cvt_f_i(fc_scalar_t a) {
  fc_scalar_t res;
  res.type = FC_SCALAR_TYPE_I;
  res.data.val_i = a.data.val_f;
  return res;
}

fc_scalar_t fc_math_cvt_c(fc_scalar_t a) {
  if (a.type == FC_SCALAR_TYPE_C) return a;
  if (a.type == FC_SCALAR_TYPE_F) return fc_math_cvt_f_c(a);
  if (a.type == FC_SCALAR_TYPE_I) return fc_math_cvt_i_c(a);
  return fc_math_set_c(0);
}

fc_scalar_t fc_math_cvt_f(fc_scalar_t a) {
  if (a.type == FC_SCALAR_TYPE_F) return a;
  if (a.type == FC_SCALAR_TYPE_C) return fc_math_cvt_c_f(a);
  if (a.type == FC_SCALAR_TYPE_I) return fc_math_cvt_i_f(a);
  return fc_math_set_f(0);
}

fc_scalar_t fc_math_cvt_i(fc_scalar_t a) {
  if (a.type == FC_SCALAR_TYPE_I) return a;
  if (a.type == FC_SCALAR_TYPE_C) return fc_math_cvt_c_i(a);
  if (a.type == FC_SCALAR_TYPE_F) return fc_math_cvt_f_i(a);
  return fc_math_set_i(0);
}

fc_scalar_t fc_math_cvt(fc_scalar_t a, fc_scalar_type_t type) {
  if (a.type == FC_SCALAR_TYPE_C) return fc_math_cvt_c(a);
  if (a.type == FC_SCALAR_TYPE_F) return fc_math_cvt_f(a);
  if (a.type == FC_SCALAR_TYPE_I) return fc_math_cvt_i(a);
  return a;
}
