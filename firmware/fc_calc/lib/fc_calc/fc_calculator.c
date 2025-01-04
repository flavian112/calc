#include "fc_calculator.h"
#include "fc_math.h"
#include "string.h"
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
  const char *name;
  unsigned argc;
  unsigned stackc;
  bool stackp;
  void *op;
} _op_info_t;

typedef struct {
  const char *name;
  fc_scalar_t val;
} _const_info_t;

static const _op_info_t _op_info[_FC_CALCULATOR_OPERATION_COUNT];
static const _const_info_t _const_info[_FC_CALCULATOR_CONSTANT_COUNT];


static inline void _stack_push(fc_calculator_state_t *state, fc_scalar_t scalar) {
  state->stack_top = (state->stack_top + FC_CALCULATOR_STACK_SIZE - 1) % FC_CALCULATOR_STACK_SIZE;
  state->stack[state->stack_top] = scalar;
}

static inline fc_scalar_t _stack_pop(fc_calculator_state_t *state) {
  fc_scalar_t scalar = state->stack[state->stack_top];
  state->stack[state->stack_top] = state->stack[(state->stack_top + FC_CALCULATOR_STACK_SIZE - 1) % FC_CALCULATOR_STACK_SIZE];
  state->stack_top = (state->stack_top + 1) % FC_CALCULATOR_STACK_SIZE;
  return scalar;
}

static inline fc_scalar_t _stack_get(fc_calculator_state_t *state, unsigned index) {
  fc_scalar_t scalar = state->stack[(state->stack_top + index) % FC_CALCULATOR_STACK_SIZE];
  return scalar;
}

static inline void _stack_set(fc_calculator_state_t *state, unsigned index, fc_scalar_t scalar) {
  state->stack[(state->stack_top + index) % FC_CALCULATOR_STACK_SIZE] = scalar;
}

static inline void _register_file_store(fc_calculator_state_t *state, unsigned char address) {
  if (address >= FC_CALCULATOR_REGISTER_FILE_SIZE) return;
  state->register_file[address] = _stack_get(state, 0);
}

static inline void _register_file_recall(fc_calculator_state_t *state, unsigned char address) {
  if (address >= FC_CALCULATOR_REGISTER_FILE_SIZE) return;
  _stack_push(state, state->register_file[address]);
}

static void _op_push(fc_calculator_state_t *state, void *scalar) {
  _stack_push(state, *(fc_scalar_t *)scalar);
}

static void _op_pop(fc_calculator_state_t *state) {
  _stack_pop(state);
}

static void _op_swap(fc_calculator_state_t *state) {
  fc_scalar_t x = _stack_get(state, 0);
  fc_scalar_t y = _stack_get(state, 1);
  _stack_set(state, 0, y);
  _stack_set(state, 1, x);
}

static void _op_last_x(fc_calculator_state_t *state) {
  _stack_push(state, state->last_x);
}

static void _op_roll_down(fc_calculator_state_t *state) {
  state->stack_top = (state->stack_top + 1) % FC_CALCULATOR_STACK_SIZE;
}

static void _op_roll_up(fc_calculator_state_t *state) {
  state->stack_top = (state->stack_top + FC_CALCULATOR_STACK_SIZE - 1) % FC_CALCULATOR_STACK_SIZE;
}

static void _op_constant(fc_calculator_state_t *state, void *constant) {
  const _const_info_t *const_info = &_const_info[*(fc_calculator_constant_t *)constant];
  _stack_push(state, const_info->val);
}

static void _op_store(fc_calculator_state_t *state, void *index) {
  _register_file_store(state, *(unsigned char *)index);
}

static void _op_recall(fc_calculator_state_t *state, void *index) {
  _register_file_recall(state, *(unsigned char *)index);
}

static void _op_set_type(fc_calculator_state_t *state, void *type) {
  state->scalar_type = *(fc_scalar_type_t *)type;
}

void fc_calculator_init(fc_calculator_state_t *state) {
  memset(state, 0, sizeof(fc_calculator_state_t));
  state->scalar_type = FC_SCALAR_TYPE_F;
}

fc_scalar_t fc_calculator_stack_get(fc_calculator_state_t *state, unsigned index) {
  return _stack_get(state, index);
}

int fc_calculator_perform_operation(fc_calculator_state_t *state, fc_calculator_operation_t operation, ...) {
  fc_scalar_t last_x = _stack_get(state, 0);
  
  const _op_info_t *op_info = &_op_info[operation];
  
  if (op_info->stackp) {
    fc_scalar_t r;
    
    if (op_info->stackc == 1) {
      fc_scalar_t (*op)(fc_scalar_t) = op_info->op;
      fc_scalar_t x = _stack_pop(state);
      r = op(x);
    } else if (op_info->stackc == 2) {
      fc_scalar_t (*op)(fc_scalar_t, fc_scalar_t) = op_info->op;
      fc_scalar_t x = _stack_pop(state);
      fc_scalar_t y = _stack_pop(state);
      r = op(y, x);
    } else {
      fc_scalar_t (*op)(void) = op_info->op;
      r = op();
    }
    
    _stack_push(state, fc_math_cvt(r, state->scalar_type));
  } else {
    void *args[op_info->argc];
    va_list arg_list;
    
    va_start(arg_list, operation);
    for (int i = 0; i < op_info->argc; i++) {
      args[i] = va_arg(arg_list, void*);
    }
    va_end(arg_list);
    
    if (op_info->argc == 0) {
      void (*op)(fc_calculator_state_t*) = op_info->op;
      op(state);
    } else if (op_info->argc == 1) {
      void (*op)(fc_calculator_state_t*, void*) = op_info->op;
      op(state, args[0]);
    } else if (op_info->argc == 2) {
      void (*op)(fc_calculator_state_t*, void*, void*) = op_info->op;
      op(state, args[0], args[1]);
    }
  }
  
  state->last_x = last_x;
  return 0;
}

fc_scalar_type_t fc_calculator_scalar_type_get(fc_calculator_state_t *state) {
  return state->scalar_type;
}

const char *fc_calculator_const_name(fc_calculator_constant_t constant) {
  return _const_info[constant].name;
}

const char *fc_calculator_operation_name(fc_calculator_operation_t operation) {
  return _op_info[operation].name;
}

static const _op_info_t _op_info[_FC_CALCULATOR_OPERATION_COUNT] = {
  [FC_CALCULATOR_OPERATION_ADD] = {
    .name   = "ADD",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_add,
  },
  [FC_CALCULATOR_OPERATION_SUBTRACT] = {
    .name   = "SUB",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_subtract,
  },
  [FC_CALCULATOR_OPERATION_NEGATE] = {
    .name   = "NEG",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_negate,
  },
  [FC_CALCULATOR_OPERATION_MULTIPLY] = {
    .name   = "MUL",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_multiply,
  },
  [FC_CALCULATOR_OPERATION_DIVIDE] = {
    .name   = "DIV",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_divide,
  },
  [FC_CALCULATOR_OPERATION_INVERSE] = {
    .name   = "INV",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_inverse,
  },
  [FC_CALCULATOR_OPERATION_MODULO] = {
    .name   = "MOD",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_modulo,
  },
  [FC_CALCULATOR_OPERATION_SQUARE] = {
    .name   = "SQ",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_square,
  },
  [FC_CALCULATOR_OPERATION_SQUAREROOT] = {
    .name   = "SQRT",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_squareroot,
  },
  [FC_CALCULATOR_OPERATION_EXP] = {
    .name   = "EXP",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_exp,
  },
  [FC_CALCULATOR_OPERATION_EXP2] = {
    .name   = "EXP2",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_exp2,
  },
  [FC_CALCULATOR_OPERATION_EXP10] = {
    .name   = "EXP10",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_exp10,
  },
  [FC_CALCULATOR_OPERATION_LN] = {
    .name   = "LN",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_ln,
  },
  [FC_CALCULATOR_OPERATION_LOG2] = {
    .name   = "LOG2",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_log2,
  },
  [FC_CALCULATOR_OPERATION_LOG10] = {
    .name   = "LOG10",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_log10,
  },
  [FC_CALCULATOR_OPERATION_LOG] = {
    .name   = "LOG",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_log,
  },
  [FC_CALCULATOR_OPERATION_POWER] = {
    .name   = "POW",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_power,
  },
  [FC_CALCULATOR_OPERATION_ROOT] = {
    .name   = "ROOT",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_root,
  },
  [FC_CALCULATOR_OPERATION_SIN] = {
    .name   = "SIN",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_sin,
  },
  [FC_CALCULATOR_OPERATION_COS] = {
    .name   = "COS",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_cos,
  },
  [FC_CALCULATOR_OPERATION_TAN] = {
    .name   = "TAN",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_tan,
  },
  [FC_CALCULATOR_OPERATION_ASIN] = {
    .name   = "ASIN",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_asin,
  },
  [FC_CALCULATOR_OPERATION_ACOS] = {
    .name   = "ACOS",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_acos,
  },
  [FC_CALCULATOR_OPERATION_ATAN] = {
    .name   = "ATAN",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_atan,
  },
  [FC_CALCULATOR_OPERATION_SINH] = {
    .name   = "SINH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_sinh,
  },
  [FC_CALCULATOR_OPERATION_COSH] = {
    .name   = "COSH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_cosh,
  },
  [FC_CALCULATOR_OPERATION_TANH] = {
    .name   = "TANH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_tanh,
  },
  [FC_CALCULATOR_OPERATION_ASINH] = {
    .name   = "ASINH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_asinh,
  },
  [FC_CALCULATOR_OPERATION_ACOSH] = {
    .name   = "ACOSH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_acosh,
  },
  [FC_CALCULATOR_OPERATION_ATANH] = {
    .name   = "ATANH",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_atanh,
  },
  [FC_CALCULATOR_OPERATION_NOT] = {
    .name   = "NOT",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_not,
  },
  [FC_CALCULATOR_OPERATION_AND] = {
    .name   = "AND",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_and,
  },
  [FC_CALCULATOR_OPERATION_OR] = {
    .name   = "OR",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_or,
  },
  [FC_CALCULATOR_OPERATION_XOR] = {
    .name   = "XOR",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_xor,
  },
  [FC_CALCULATOR_OPERATION_NAND] = {
    .name   = "NAND",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_nand,
  },
  [FC_CALCULATOR_OPERATION_NOR] = {
    .name   = "NOR",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_nor,
  },
  [FC_CALCULATOR_OPERATION_XNOR] = {
    .name   = "XNOR",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_xnor,
  },
  [FC_CALCULATOR_OPERATION_SLL] = {
    .name   = "SLL",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_sll,
  },
  [FC_CALCULATOR_OPERATION_SRL] = {
    .name   = "SRL",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_srl,
  },
  [FC_CALCULATOR_OPERATION_SRA] = {
    .name   = "SRA",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_sra,
  },
  [FC_CALCULATOR_OPERATION_LNOT] = {
    .name   = "LNOT",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_lnot,
  },
  [FC_CALCULATOR_OPERATION_LAND] = {
    .name   = "LAND",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_land,
  },
  [FC_CALCULATOR_OPERATION_LOR] = {
    .name   = "LOR",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_lor,
  },
  [FC_CALCULATOR_OPERATION_LT] = {
    .name   = "LT",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_lt,
  },
  [FC_CALCULATOR_OPERATION_LE] = {
    .name   = "LE",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_le,
  },
  [FC_CALCULATOR_OPERATION_EQ] = {
    .name   = "EQ",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_eq,
  },
  [FC_CALCULATOR_OPERATION_NE] = {
    .name   = "NE",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_ne,
  },
  [FC_CALCULATOR_OPERATION_GE] = {
    .name   = "GE",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_ge,
  },
  [FC_CALCULATOR_OPERATION_GT] = {
    .name   = "GT",
    .argc   = 0,
    .stackc = 2,
    .stackp = true,
    .op     = fc_math_gt,
  },
  [FC_CALCULATOR_OPERATION_ABS] = {
    .name   = "ABS",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_abs,
  },
  [FC_CALCULATOR_OPERATION_ARG] = {
    .name   = "ARG",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_arg,
  },
  [FC_CALCULATOR_OPERATION_CONJ] = {
    .name   = "CONJ",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_conj,
  },
  [FC_CALCULATOR_OPERATION_REAL] = {
    .name   = "REAL",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_real,
  },
  [FC_CALCULATOR_OPERATION_IMAG] = {
    .name   = "IMAG",
    .argc   = 0,
    .stackc = 1,
    .stackp = true,
    .op     = fc_math_imag,
  },
  [FC_CALCULATOR_OPERATION_POP] = {
    .name   = "POP",
    .argc   = 0,
    .stackc = 0,
    .stackp = false,
    .op     = _op_pop,
  },
  [FC_CALCULATOR_OPERATION_SWAP] = {
    .name   = "SWAP",
    .argc   = 0,
    .stackc = 0,
    .stackp = false,
    .op     = _op_swap,
  },
  [FC_CALCULATOR_OPERATION_ROLLDOWN] = {
    .name   = "RLLD",
    .argc   = 0,
    .stackc = 0,
    .stackp = false,
    .op     = _op_roll_down,
  },
  [FC_CALCULATOR_OPERATION_ROLLUP] = {
    .name   = "RLLU",
    .argc   = 0,
    .stackc = 0,
    .stackp = false,
    .op     = _op_roll_up,
  },
  [FC_CALCULATOR_OPERATION_LASTX] = {
    .name   = "LSTX",
    .argc   = 0,
    .stackc = 0,
    .stackp = false,
    .op     = _op_last_x,
  },
  [FC_CALCULATOR_OPERATION_PUSH] = {
    .name   = "PUSH",
    .argc   = 1,
    .stackc = 0,
    .stackp = false,
    .op     = _op_push,
  },
  [FC_CALCULATOR_OPERATION_STORE] = {
    .name   = "STO",
    .argc   = 1,
    .stackc = 0,
    .stackp = false,
    .op     = _op_store,
  },
  [FC_CALCULATOR_OPERATION_RECALL] = {
    .name   = "RCL",
    .argc   = 1,
    .stackc = 0,
    .stackp = false,
    .op     = _op_recall,
  },
  [FC_CALCULATOR_OPERATION_CONSTANT] = {
    .name   = "CNST",
    .argc   = 1,
    .stackc = 0,
    .stackp = false,
    .op     = _op_constant,
  },
  [FC_CALCULATOR_OPERATION_TYPE] = {
    .name   = "TYPE",
    .argc   = 1,
    .stackc = 0,
    .stackp = false,
    .op     = _op_set_type,
  }
};

static const _const_info_t _const_info[_FC_CALCULATOR_CONSTANT_COUNT] = {
  [FC_CALCULATOR_CONSTANT_PI] = {
    .name   = "pi",
    .val = { .type = FC_SCALAR_TYPE_F, .data.val_f = M_PI }
  },
  [FC_CALCULATOR_CONSTANT_EULER] = {
    .name   = "e",
    .val = { .type = FC_SCALAR_TYPE_F, .data.val_f = M_E }
  }
};

