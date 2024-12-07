#include "fc_calc.h"
#include "fc_math.h"
#include <string.h>

void _fc_calc_stack_push(fc_calc_state_t *state, fc_scalar_t s) {
  state->stack_top = (state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE;
  state->stack[state->stack_top] = s;
}

fc_scalar_t _fc_calc_stack_pop(fc_calc_state_t *state) {
  fc_scalar_t s = state->stack[state->stack_top];
  state->stack[state->stack_top] = state->stack[(state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE];
  state->stack_top = (state->stack_top + 1) % FC_CALC_STACK_SIZE;
  return s;
}

void fc_calc_stack_push(fc_calc_state_t *state, fc_scalar_t s) {
  _fc_calc_stack_push(state, s);
}

fc_scalar_t fc_calc_stack_get(fc_calc_state_t *state, uint8_t index) {
  fc_scalar_t s = state->stack[(state->stack_top + index) % FC_CALC_STACK_SIZE];
  return s;
}

void fc_calc_stack_set(fc_calc_state_t *state, uint8_t index, fc_scalar_t s) {
  state->stack[(state->stack_top + index) % FC_CALC_STACK_SIZE] = s;
}

void fc_calc_stack_roll_down(fc_calc_state_t *state) {
  state->stack_top = (state->stack_top + 1) % FC_CALC_STACK_SIZE;
}

void fc_calc_stack_roll_up(fc_calc_state_t *state) {
  state->stack_top = (state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE;
}

void fc_calc_stack_swap(fc_calc_state_t *state) {
  fc_scalar_t tmp = fc_calc_stack_get(state, 0);
  fc_calc_stack_set(state, 0, fc_calc_stack_get(state, 1));
  fc_calc_stack_set(state, 1, tmp);
}

fc_calc_state_t fc_calc_init(void) {
  fc_calc_state_t state;
  memset(&state, 0, sizeof(fc_calc_state_t));
  return state;
}

void fc_calc_op(fc_calc_state_t *state, fc_calc_op_t op) {
  state->last_x = fc_calc_stack_get(state, 0);
  switch (op) {
    case FC_CALC_OP_ADD_CC_C:
      _fc_calc_stack_push(state, fc_math_add_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SUB_CC_C:
      _fc_calc_stack_push(state, fc_math_sub_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_NEG_C_C:
      _fc_calc_stack_push(state, fc_math_neg_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MUL_CC_C:
      _fc_calc_stack_push(state, fc_math_mul_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_DIV_CC_C:
      _fc_calc_stack_push(state, fc_math_div_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_INV_C_C:
      _fc_calc_stack_push(state, fc_math_inv_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_REAL_C_D:
      _fc_calc_stack_push(state, fc_math_real_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_IMAG_C_D:
      _fc_calc_stack_push(state, fc_math_imag_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ABS_C_D:
      _fc_calc_stack_push(state, fc_math_abs_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ARG_C_D:
      _fc_calc_stack_push(state, fc_math_arg_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CONJ_C_C:
      _fc_calc_stack_push(state, fc_math_conj_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SIN_C_C:
      _fc_calc_stack_push(state, fc_math_sin_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_COS_C_C:
      _fc_calc_stack_push(state, fc_math_cos_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_TAN_C_C:
      _fc_calc_stack_push(state, fc_math_tan_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ASIN_C_C:
      _fc_calc_stack_push(state, fc_math_asin_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ACOS_C_C:
      _fc_calc_stack_push(state, fc_math_acos_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ATAN_C_C:
      _fc_calc_stack_push(state, fc_math_atan_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SINH_C_C:
      _fc_calc_stack_push(state, fc_math_sinh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_COSH_C_C:
      _fc_calc_stack_push(state, fc_math_cosh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_TANH_C_C:
      _fc_calc_stack_push(state, fc_math_tanh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ASINH_C_C:
      _fc_calc_stack_push(state, fc_math_asinh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ACOSH_C_C:
      _fc_calc_stack_push(state, fc_math_acosh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ATANH_C_C:
      _fc_calc_stack_push(state, fc_math_atanh_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_EXP_C_C:
      _fc_calc_stack_push(state, fc_math_exp_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_EXP2_C_C:
      _fc_calc_stack_push(state, fc_math_exp2_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_EXP10_C_C:
      _fc_calc_stack_push(state, fc_math_exp10_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_LN_C_C:
      _fc_calc_stack_push(state, fc_math_ln_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_LOG2_C_C:
      _fc_calc_stack_push(state, fc_math_log2_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_LOG10_C_C:
      _fc_calc_stack_push(state, fc_math_log10_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_LOG_CC_C:
      _fc_calc_stack_push(state, fc_math_log_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SQ_C_C:
      _fc_calc_stack_push(state, fc_math_sq_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_POW_CC_C:
      _fc_calc_stack_push(state, fc_math_pow_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SQRT_C_C:
      _fc_calc_stack_push(state, fc_math_sqrt_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ROOT_CC_C:
      _fc_calc_stack_push(state, fc_math_root_c(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPLT_DD_I:
      _fc_calc_stack_push(state, fc_math_cmplt_d(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPGT_DD_I:
      _fc_calc_stack_push(state, fc_math_cmpgt_d(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SIGN_D_I:
      _fc_calc_stack_push(state, fc_math_sign_d(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MAX_DD_D:
      _fc_calc_stack_push(state, fc_math_max_d(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MIN_DD_D:
      _fc_calc_stack_push(state, fc_math_min_d(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_INC_I_I:
      _fc_calc_stack_push(state, fc_math_inc_i(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_DEC_I_I:
      _fc_calc_stack_push(state, fc_math_dec_i(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_ADD_II_I:
      _fc_calc_stack_push(state, fc_math_add_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SUB_II_I:
      _fc_calc_stack_push(state, fc_math_sub_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_NEG_I_I:
      _fc_calc_stack_push(state, fc_math_neg_i(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MUL_II_I:
      _fc_calc_stack_push(state, fc_math_mul_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_DIV_II_I:
      _fc_calc_stack_push(state, fc_math_div_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MOD_II_I:
      _fc_calc_stack_push(state, fc_math_mod_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_NOT_I_I:
      _fc_calc_stack_push(state, fc_math_not_i(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_OR_II_I:
      _fc_calc_stack_push(state, fc_math_or_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_AND_II_I:
      _fc_calc_stack_push(state, fc_math_and_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_NOR_II_I:
      _fc_calc_stack_push(state, fc_math_nor_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_NAND_II_I:
      _fc_calc_stack_push(state, fc_math_nand_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_XOR_II_I:
      _fc_calc_stack_push(state, fc_math_xor_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_XNOR_II_I:
      _fc_calc_stack_push(state, fc_math_xnor_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SRA_II_I:
      _fc_calc_stack_push(state, fc_math_sra_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SLL_II_I:
      _fc_calc_stack_push(state, fc_math_sll_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_SRL_II_I:
      _fc_calc_stack_push(state, fc_math_srl_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPEQ_II_I:
      _fc_calc_stack_push(state, fc_math_cmpeq_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPLE_II_I:
      _fc_calc_stack_push(state, fc_math_cmple_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPLT_II_I:
      _fc_calc_stack_push(state, fc_math_cmplt_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPGE_II_I:
      _fc_calc_stack_push(state, fc_math_cmpge_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CMPGT_II_I:
      _fc_calc_stack_push(state, fc_math_cmpgt_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MAX_II_I:
      _fc_calc_stack_push(state, fc_math_max_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_MIN_II_I:
      _fc_calc_stack_push(state, fc_math_min_i(
        _fc_calc_stack_pop(state),
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_D_C:
      _fc_calc_stack_push(state, fc_math_cvt_d_to_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_I_C:
      _fc_calc_stack_push(state, fc_math_cvt_i_to_c(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_C_D:
      _fc_calc_stack_push(state, fc_math_cvt_c_to_d(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_I_D:
      _fc_calc_stack_push(state, fc_math_cvt_i_to_d(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_C_I:
      _fc_calc_stack_push(state, fc_math_cvt_c_to_i(
        _fc_calc_stack_pop(state)));
      break;
    case FC_CALC_OP_CVT_D_I:
      _fc_calc_stack_push(state, fc_math_cvt_d_to_i(
        _fc_calc_stack_pop(state)));
      break;
  }
}