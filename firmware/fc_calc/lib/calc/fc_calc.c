#include "fc_calc.h"

void _stack_push(fc_calc_state_t *state, fc_scalar_t s) {
  state->stack_top = (state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE;
  state->stack[state->stack_top] = s;
}

fc_scalar_t _stack_pop(fc_calc_state_t *state) {
  fc_scalar_t s = state->stack[state->stack_top];
  state->stack[state->stack_top] = state->stack[(state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE];
  state->stack_top = (state->stack_top + 1) % FC_CALC_STACK_SIZE;
  return s;
}

fc_scalar_t _stack_get(fc_calc_state_t *state, uint8_t index) {
  fc_scalar_t s = state->stack[(state->stack_top + index) % FC_CALC_STACK_SIZE];
  return s;
}

void _stack_set(fc_calc_state_t *state, uint8_t index, fc_scalar_t s) {
  state->stack[(state->stack_top + index) % FC_CALC_STACK_SIZE] = s;
}

void _stack_roll_down(fc_calc_state_t *state) {
  state->stack_top = (state->stack_top + 1) % FC_CALC_STACK_SIZE;
}

void _stack_roll_up(fc_calc_state_t *state) {
  state->stack_top = (state->stack_top + FC_CALC_STACK_SIZE - 1) % FC_CALC_STACK_SIZE;
}

void _stack_swap(fc_calc_state_t *state) {
  fc_scalar_t tmp = _stack_get(state, 0);
  _stack_set(state, 0, _stack_get(state, 1));
  _stack_set(state, 1, tmp);
}

fc_calc_state_t fc_calc_init(void) {
  fc_calc_state_t state;
  memset(&state, 0, sizeof(fc_calc_state_t));
  return state;
}

void fc_calc_stack_push(fc_calc_state_t *state, fc_scalar_t s) {
  state->last_x = _stack_get(state, 0);
  _stack_push(state, s);
}

fc_scalar_t fc_calc_stack_get(fc_calc_state_t *state, uint8_t index) {
  return _stack_get(state, index);
}

void fc_calc_op(fc_calc_state_t *state, fc_calc_op_t op, fc_scalar_type_t type) {
  state->last_x = _stack_get(state, 0);
  switch (op) {
    case FC_CALC_OP_INC:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_inc_i_i(x), type));
      break;
    case FC_CALC_OP_DEC:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_dec_i_i(x), type));
      break;
    case FC_CALC_OP_ADD:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_add_cc_c(y, x), type));
      break;
    case FC_CALC_OP_SUB:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sub_cc_c(y, x), type));
      break;
    case FC_CALC_OP_NEG:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_neg_c_c(x), type));
      break;
    case FC_CALC_OP_MUL:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_mul_cc_c(y, x), type));
      break;
    case FC_CALC_OP_DIV:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_div_cc_c(y, x), type));
      break;
    case FC_CALC_OP_MOD:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_mod_ii_i(y, x), type));
      break;
    case FC_CALC_OP_INV:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_add_cc_c(y, x), type));
      break;
    case FC_CALC_OP_SQ:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sq_c_c(x), type));
      break;
    case FC_CALC_OP_SQRT:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sqrt_c_c(x), type));
      break;
    case FC_CALC_OP_EXP:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_exp_c_c(x), type));
      break;
    case FC_CALC_OP_EXP2:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_exp2_c_c(x), type));
      break;
    case FC_CALC_OP_EXP10:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_exp10_c_c(x), type));
      break;
    case FC_CALC_OP_POW:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_pow_cc_c(y, x), type));
      break;
    case FC_CALC_OP_ROOT:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_root_cc_c(y, x), type));
      break;
    case FC_CALC_OP_LN:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_ln_c_c(x), type));
      break;
    case FC_CALC_OP_LOG2:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_log2_c_c(x), type));
      break;
    case FC_CALC_OP_LOG10:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_log10_c_c(x), type));
      break;
    case FC_CALC_OP_LOG:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_log_cc_c(y, x), type));
      break;
    case FC_CALC_OP_SIN:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sin_c_c(x), type));
      break;
    case FC_CALC_OP_COS:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cos_c_c(x), type));
      break;
    case FC_CALC_OP_TAN:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_tan_c_c(x), type));
      break;
    case FC_CALC_OP_ASIN:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_asin_c_c(x), type));
      break;
    case FC_CALC_OP_ACOS:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_acos_c_c(x), type));
      break;
    case FC_CALC_OP_ATAN:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_atan_c_c(x), type));
      break;
    case FC_CALC_OP_SINH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sinh_c_c(x), type));
      break;
    case FC_CALC_OP_COSH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cosh_c_c(x), type));
      break;
    case FC_CALC_OP_TANH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_tanh_c_c(x), type));
      break;
    case FC_CALC_OP_ASINH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_asinh_c_c(x), type));
      break;
    case FC_CALC_OP_ACOSH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_acosh_c_c(x), type));
      break;
    case FC_CALC_OP_ATANH:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_atanh_c_c(x), type));
      break;
    case FC_CALC_OP_CMPEQ:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cmpeq_ii_i(y, x), type));
      break;
    case FC_CALC_OP_CMPLT:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cmplt_ff_i(y, x), type));
      break;
    case FC_CALC_OP_CMPLE:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cmple_ii_i(y, x), type));
      break;
    case FC_CALC_OP_CMPGT:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cmpgt_ff_i(y, x), type));
      break;
    case FC_CALC_OP_CMPGE:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_cmpge_ii_i(y, x), type));
      break;
    case FC_CALC_OP_ABS:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_abs_c_f(x), type));
      break;
    case FC_CALC_OP_ARG:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_arg_c_f(x), type));
      break;
    case FC_CALC_OP_REAL:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_real_c_f(x), type));
      break;
    case FC_CALC_OP_IMAG:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_imag_c_f(x), type));
      break;
    case FC_CALC_OP_CONJ:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_conj_c_c(x), type));
      break;
    case FC_CALC_OP_MIN:  
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_min_ff_f(y, x), type));
      break;
    case FC_CALC_OP_MAX:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_max_ff_f(y, x), type));
      break;
    case FC_CALC_OP_NOT:
      fc_scalar_t x = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_not_i_i(x), type));
      break;
    case FC_CALC_OP_OR:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_or_ii_i(y, x), type));
      break;
    case FC_CALC_OP_AND:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_and_ii_i(y, x), type));
      break;
    case FC_CALC_OP_XOR:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_xor_ii_i(y, x), type));
      break;
    case FC_CALC_OP_NOR:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_nor_ii_i(y, x), type));
      break;
    case FC_CALC_OP_NAND:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_nand_ii_i(y, x), type));
      break;
    case FC_CALC_OP_XNOR:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_xnor_ii_i(y, x), type));
      break;
    case FC_CALC_OP_SRA:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sra_ii_i(y, x), type));
      break;
    case FC_CALC_OP_SRL:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_srl_ii_i(y, x), type));
      break;
    case FC_CALC_OP_SLL:
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      _stack_push(state, fc_math_cvt(fc_math_sll_ii_i(y, x), type));
      break;
    case FC_CALC_OP_SWAP:
      _stack_swap(state);
      break;
    case FC_CALC_OP_ROLLD:
      _stack_roll_down(state);
      break;
    case FC_CALC_OP_ROOLU:
      _stack_roll_up(state);
      break;
    case FC_CALC_OP_LASTX:
      _stack_push(state, state->last_x);
      break;
  }
}