#ifndef CALC_H
#define CALC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <complex.h>
#include "common.h"

#define STACK_SIZE 8
#define REG_SIZE 24



number_t ca_stack_pop_x(void);
void ca_stack_push_x(number_t number);
number_t ca_stack_get(size_t index);
void ca_stack_set(size_t index, number_t number);
void ca_stack_roll_down(void);
void ca_stack_roll_up(void);
void ca_stack_swap_yx(void);

/*
 registers
 */

void ca_reg_sto_x(size_t index);
void ca_reg_rcl_x(size_t index);

/*
 operations
*/

// basic arithmetic
void ca_op_add_yx(void);
void ca_op_sub_yx(void);
void ca_op_neg_x(void);
void ca_op_mul_yx(void);
void ca_op_div_yx(void);
void ca_op_inv_x(void);


void ca_op_sq_x(void);
void ca_op_expe_x(void);
void ca_op_pow_yx(void);
void ca_op_pow2_x(void);
void ca_op_pow10_x(void);
void ca_op_sqrt_x(void);
void ca_op_root_yx(void);
void ca_op_log10_x(void);
void ca_op_log2_x(void);
void ca_op_ln(void);
void ca_op_log_yx(void);

// other
void ca_op_abs_x(void);
void ca_op_arg_x(void);
void ca_op_real_x(void);
void ca_op_imag_x(void);

// trigonometry
void ca_op_sin_x(void);
void ca_op_cos_x(void);
void ca_op_tan_x(void);
void ca_op_asin_x(void);
void ca_op_acos_x(void);
void ca_op_atan_x(void);
void ca_op_sinh_x(void);
void ca_op_cosh_x(void);
void ca_op_tanh_x(void);
void ca_op_asinh_x(void);
void ca_op_acosh_x(void);
void ca_op_atanh_x(void);
void ca_op_fact_x(void);

#ifdef __cplusplus
}
#endif

#endif
