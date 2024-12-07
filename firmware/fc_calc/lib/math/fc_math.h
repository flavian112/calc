#ifndef FC_MATH_H
#define FC_MATH_H

#include <complex.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum fc_base_t {
  FC_BASE_BIN = 2,
  FC_BASE_OCT = 8,
  FC_BASE_DEC = 10,
  FC_BASE_HEX = 16
} typedef fc_base_t;

enum fc_scalar_type_t {
  FC_SCALAR_TYPE_C,
  FC_SCALAR_TYPE_F,
  FC_SCALAR_TYPE_I
} typedef fc_scalar_type_t;

union fc_scalar_data_t {
  char bytes[16];
  double complex val_c;
  double val_f;
  int64_t val_i;
} typedef fc_scalar_data_t;

struct fc_scalar_t {
  fc_scalar_data_t data;
  fc_scalar_type_t type;
} typedef fc_scalar_t;

fc_scalar_t fc_math_set_c(double complex val);
fc_scalar_t fc_math_add_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sub_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_neg_c_c(fc_scalar_t a);
fc_scalar_t fc_math_mul_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_div_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_inv_c_c(fc_scalar_t a);
fc_scalar_t fc_math_sin_c_c(fc_scalar_t a);
fc_scalar_t fc_math_cos_c_c(fc_scalar_t a);
fc_scalar_t fc_math_tan_c_c(fc_scalar_t a);
fc_scalar_t fc_math_asin_c_c(fc_scalar_t a);
fc_scalar_t fc_math_acos_c_c(fc_scalar_t a);
fc_scalar_t fc_math_atan_c_c(fc_scalar_t a);
fc_scalar_t fc_math_sinh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_cosh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_tanh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_asinh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_acosh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_atanh_c_c(fc_scalar_t a);
fc_scalar_t fc_math_exp_c_c(fc_scalar_t a);
fc_scalar_t fc_math_exp2_c_c(fc_scalar_t a);
fc_scalar_t fc_math_exp10_c_c(fc_scalar_t a);
fc_scalar_t fc_math_pow_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_ln_c_c(fc_scalar_t a);
fc_scalar_t fc_math_log2_c_c(fc_scalar_t a);
fc_scalar_t fc_math_log10_c_c(fc_scalar_t a);
fc_scalar_t fc_math_log_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sq_c_c(fc_scalar_t a);
fc_scalar_t fc_math_sqrt_c_c(fc_scalar_t a);
fc_scalar_t fc_math_root_cc_c(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_real_c_f(fc_scalar_t a);
fc_scalar_t fc_math_imag_c_f(fc_scalar_t a);
fc_scalar_t fc_math_abs_c_f(fc_scalar_t a);
fc_scalar_t fc_math_arg_c_f(fc_scalar_t a);
fc_scalar_t fc_math_conj_c_c(fc_scalar_t a);
fc_scalar_t fc_math_set_f(double val);
fc_scalar_t fc_math_cmplt_ff_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmpgt_ff_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sign_f_i(fc_scalar_t a);
fc_scalar_t fc_math_max_ff_f(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_min_ff_f(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_set_i(int64_t val);
fc_scalar_t fc_math_inc_i_i(fc_scalar_t a);
fc_scalar_t fc_math_dec_i_i(fc_scalar_t a);
fc_scalar_t fc_math_add_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sub_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_neg_i_i(fc_scalar_t a);
fc_scalar_t fc_math_mul_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_div_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_mod_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_not_i_i(fc_scalar_t a);
fc_scalar_t fc_math_or_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_and_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_xor_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_nor_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_nand_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_xnor_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sra_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_sll_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_srl_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmpeq_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmple_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmplt_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmpge_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cmpgt_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_max_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_min_ii_i(fc_scalar_t a, fc_scalar_t b);
fc_scalar_t fc_math_cvt_f_c(fc_scalar_t a);
fc_scalar_t fc_math_cvt_i_c(fc_scalar_t a);
fc_scalar_t fc_math_cvt_c_f(fc_scalar_t a);
fc_scalar_t fc_math_cvt_i_f(fc_scalar_t a);
fc_scalar_t fc_math_cvt_c_i(fc_scalar_t a);
fc_scalar_t fc_math_cvt_f_i(fc_scalar_t a);
fc_scalar_t fc_math_cvt_c(fc_scalar_t a);
fc_scalar_t fc_math_cvt_f(fc_scalar_t a);
fc_scalar_t fc_math_cvt_i(fc_scalar_t a);
fc_scalar_t fc_math_cvt(fc_scalar_t a, fc_scalar_type_t type);


#ifdef __cplusplus
}
#endif

#endif