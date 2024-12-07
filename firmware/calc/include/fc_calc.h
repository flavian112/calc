#ifndef FC_CALC_H
#define FC_CALC_H

#include "fc_common.h"

#define FC_CALC_STACK_SIZE (8)
#define FC_CALC_REGFILE_SIZE (24)

#ifdef __cplusplus
extern "C" {
#endif

enum fc_calc_op_t {
  FC_CALC_OP_ADD_CC_C,
  FC_CALC_OP_SUB_CC_C,
  FC_CALC_OP_NEG_C_C,
  FC_CALC_OP_MUL_CC_C,
  FC_CALC_OP_DIV_CC_C,
  FC_CALC_OP_INV_C_C,
  FC_CALC_OP_REAL_C_D,
  FC_CALC_OP_IMAG_C_D,
  FC_CALC_OP_ABS_C_D,
  FC_CALC_OP_ARG_C_D,
  FC_CALC_OP_CONJ_C_C,
  FC_CALC_OP_SIN_C_C,
  FC_CALC_OP_COS_C_C,
  FC_CALC_OP_TAN_C_C,
  FC_CALC_OP_ASIN_C_C,
  FC_CALC_OP_ACOS_C_C,
  FC_CALC_OP_ATAN_C_C,
  FC_CALC_OP_SINH_C_C,
  FC_CALC_OP_COSH_C_C,
  FC_CALC_OP_TANH_C_C,
  FC_CALC_OP_ASINH_C_C,
  FC_CALC_OP_ACOSH_C_C,
  FC_CALC_OP_ATANH_C_C,
  FC_CALC_OP_EXP_C_C,
  FC_CALC_OP_EXP2_C_C,
  FC_CALC_OP_EXP10_C_C,
  FC_CALC_OP_LN_C_C,
  FC_CALC_OP_LOG2_C_C,
  FC_CALC_OP_LOG10_C_C,
  FC_CALC_OP_LOG_CC_C,
  FC_CALC_OP_SQ_C_C,
  FC_CALC_OP_POW_CC_C,
  FC_CALC_OP_SQRT_C_C,
  FC_CALC_OP_ROOT_CC_C,
  FC_CALC_OP_CMPLT_DD_I,
  FC_CALC_OP_CMPGT_DD_I,
  FC_CALC_OP_SIGN_D_I,
  FC_CALC_OP_MAX_DD_D,
  FC_CALC_OP_MIN_DD_D,
  FC_CALC_OP_INC_I_I,
  FC_CALC_OP_DEC_I_I,
  FC_CALC_OP_ADD_II_I,
  FC_CALC_OP_SUB_II_I,
  FC_CALC_OP_NEG_I_I,
  FC_CALC_OP_MUL_II_I,
  FC_CALC_OP_DIV_II_I,
  FC_CALC_OP_MOD_II_I,
  FC_CALC_OP_NOT_I_I,
  FC_CALC_OP_OR_II_I,
  FC_CALC_OP_AND_II_I,
  FC_CALC_OP_NOR_II_I,
  FC_CALC_OP_NAND_II_I,
  FC_CALC_OP_XOR_II_I,
  FC_CALC_OP_XNOR_II_I,
  FC_CALC_OP_SRA_II_I,
  FC_CALC_OP_SLL_II_I,
  FC_CALC_OP_SRL_II_I,
  FC_CALC_OP_CMPEQ_II_I,
  FC_CALC_OP_CMPLE_II_I,
  FC_CALC_OP_CMPLT_II_I,
  FC_CALC_OP_CMPGE_II_I,
  FC_CALC_OP_CMPGT_II_I,
  FC_CALC_OP_MAX_II_I,
  FC_CALC_OP_MIN_II_I,
  FC_CALC_OP_CVT_D_C,
  FC_CALC_OP_CVT_I_C,
  FC_CALC_OP_CVT_C_D,
  FC_CALC_OP_CVT_I_D,
  FC_CALC_OP_CVT_C_I,
  FC_CALC_OP_CVT_D_I
} typedef fc_calc_op_t;

enum fc_calc_const_t {
  FC_CALC_CONST_E,
  FC_CALC_CONST_PI,
} typedef fc_calc_const_t;

struct fc_calc_state_t {
  fc_scalar_t stack[FC_CALC_STACK_SIZE];
  uint8_t stack_top;
  fc_scalar_t regfile[FC_CALC_REGFILE_SIZE];
  fc_scalar_t last_x;
} typedef fc_calc_state_t;

fc_calc_state_t fc_calc_init(void);
void fc_calc_stack_push(fc_calc_state_t *state, fc_scalar_t s);
fc_scalar_t fc_calc_stack_get(fc_calc_state_t *state, uint8_t index);
void fc_calc_stack_set(fc_calc_state_t *state, uint8_t index, fc_scalar_t s);
void fc_calc_stack_roll_down(fc_calc_state_t *state);
void fc_calc_stack_roll_up(fc_calc_state_t *state);
void fc_calc_stack_swap(fc_calc_state_t *state);
void fc_calc_op(fc_calc_state_t *state, fc_calc_op_t op);

#ifdef __cplusplus
}
#endif

#endif
