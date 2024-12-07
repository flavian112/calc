#ifndef FC_CALC_H
#define FC_CALC_H

#include "fc_math.h"

#define FC_CALC_STACK_SIZE (32)
#define FC_CALC_REGFILE_SIZE (26)

#ifdef __cplusplus
extern "C" {
#endif

enum fc_calc_op_t {
  FC_CALC_OP_INC,
  FC_CALC_OP_DEC,
  FC_CALC_OP_ADD,
  FC_CALC_OP_SUB,
  FC_CALC_OP_NEG,
  FC_CALC_OP_MUL,
  FC_CALC_OP_DIV,
  FC_CALC_OP_MOD,
  FC_CALC_OP_INV,
  FC_CALC_OP_SQ,
  FC_CALC_OP_SQRT,
  FC_CALC_OP_EXP,
  FC_CALC_OP_EXP2,
  FC_CALC_OP_EXP10,
  FC_CALC_OP_POW,
  FC_CALC_OP_ROOT,
  FC_CALC_OP_LN,
  FC_CALC_OP_LOG2,
  FC_CALC_OP_LOG10,
  FC_CALC_OP_LOG,
  FC_CALC_OP_SIN,
  FC_CALC_OP_COS,
  FC_CALC_OP_TAN,
  FC_CALC_OP_ASIN,
  FC_CALC_OP_ACOS,
  FC_CALC_OP_ATAN,
  FC_CALC_OP_SINH,
  FC_CALC_OP_COSH,
  FC_CALC_OP_TANH,
  FC_CALC_OP_ASINH,
  FC_CALC_OP_ACOSH,
  FC_CALC_OP_ATANH,
  FC_CALC_OP_CMPEQ,
  FC_CALC_OP_CMPLT,
  FC_CALC_OP_CMPLE,
  FC_CALC_OP_CMPGT,
  FC_CALC_OP_CMPGE,
  FC_CALC_OP_ABS,
  FC_CALC_OP_ARG,
  FC_CALC_OP_REAL,
  FC_CALC_OP_IMAG,
  FC_CALC_OP_CONJ,
  FC_CALC_OP_MIN,
  FC_CALC_OP_MAX,
  FC_CALC_OP_NOT,
  FC_CALC_OP_OR,
  FC_CALC_OP_AND,
  FC_CALC_OP_XOR,
  FC_CALC_OP_NOR,
  FC_CALC_OP_NAND,
  FC_CALC_OP_XNOR,
  FC_CALC_OP_SRA,
  FC_CALC_OP_SRL,
  FC_CALC_OP_SLL,
  FC_CALC_OP_SWAP,
  FC_CALC_OP_ROLLD,
  FC_CALC_OP_ROOLU,
  FC_CALC_OP_LASTX
} typedef fc_calc_op_t;

struct fc_calc_state_t {
  fc_scalar_t stack[FC_CALC_STACK_SIZE];
  uint8_t stack_top;
  fc_scalar_t regfile[FC_CALC_REGFILE_SIZE];
  fc_scalar_t last_x;
  fc_scalar_type_t type;
} typedef fc_calc_state_t;

fc_calc_state_t fc_calc_init(void);
void fc_calc_stack_push(fc_calc_state_t *state, fc_scalar_t s);
fc_scalar_t fc_calc_stack_get(fc_calc_state_t *state, uint8_t index);
void fc_calc_op(fc_calc_state_t *state, fc_calc_op_t op, fc_scalar_type_t type);


#ifdef __cplusplus
}
#endif

#endif