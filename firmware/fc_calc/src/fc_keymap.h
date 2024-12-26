#ifndef FC_KEYMAP_H
#define FC_KEYMAP_H

#include <stdlib.h>
#include "fc_calculator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FC_KEY_MOD_SHIFT_L,
  FC_KEY_MOD_SHIFT_R,
  FC_KEY_MOD_ALT,
  FC_KEY_MOD_HYP
} fc_key_mod_t;

typedef enum {
  FC_KEY_NAV_UP,
  FC_KEY_NAV_DOWN,
  FC_KEY_NAV_LEFT,
  FC_KEY_NAV_RIGHT,
  FC_KEY_NAV_ENTER,
  FC_KEY_NAV_EXIT,
} fc_key_nav_t;

void key_func(void *arg);
void key_op(void *arg);
void key_enter(void *arg);
void key_neg(void *arg);
void key_exp(void *arg);
void key_del(void *arg);
void key_mod(void *arg);
void key_digit(void *arg);
void key_exit(void *arg);
void key_decimal(void *arg);
void key_alpha(void *arg);
void key_charset(void *arg);
void key_nav(void *arg);
void key_clear(void *arg);
void key_bksp(void *arg);

typedef void (*fc_key_func_t)(void *arg);

typedef struct {
  fc_key_func_t on_press;
  void *arg;
} fc_key_action_t;

static fc_key_action_t keymap[8][5][6] = { // default, shift_r, shift_l, alpha, nav, alt
  { // row 0
    { // F1
      { key_func, (void*)1 },
      { key_func, (void*)6 },
      { key_func, (void*)11 },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }, { // F2
      { key_func, (void*)2 }, 
      { key_func, (void*)7 }, 
      { key_func, (void*)12 }, 
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }, { // F3
      { key_func, (void*)3 },
      { key_func, (void*)8 },
      { key_func, (void*)13 },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }, { // F4
      { key_func, (void*)4 },
      { key_func, (void*)9 },
      { key_func, (void*)14 },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }, { // F5
      { key_func, (void*)5 },
      { key_func, (void*)10 },
      { key_func, (void*)15 },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL } 
    }
  }, { // row 1
    { // INV, POW, EXP2, X
      { key_op, (void*)FC_CALCULATOR_OPERATION_INVERSE },
      { key_op, (void*)FC_CALCULATOR_OPERATION_POWER },
      { key_op, (void*)FC_CALCULATOR_OPERATION_EXP2 },
      { key_alpha, (void*)'X' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // SQRT, SQ, ROOT, Y
      { key_op, (void*)FC_CALCULATOR_OPERATION_SQUAREROOT },
      { key_op, (void*)FC_CALCULATOR_OPERATION_SQUARE },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ROOT },
      { key_alpha, (void*)'Y' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // LOG10, EXP10, LOG2, Z
      { key_op, (void*)FC_CALCULATOR_OPERATION_LOG10 },
      { key_op, (void*)FC_CALCULATOR_OPERATION_EXP10 },
      { key_op, (void*)FC_CALCULATOR_OPERATION_LOG2 },
      { key_alpha, (void*)'Z' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // LN, EXP, LOG, ...
      { key_op, (void*)FC_CALCULATOR_OPERATION_LN },
      { key_op, (void*)FC_CALCULATOR_OPERATION_EXP },
      { key_op, (void*)FC_CALCULATOR_OPERATION_LOG },
      { key_charset, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }, { // XEQ, GTO, TYPE, ' '
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void*)' ' },
      { NULL, NULL },
      { NULL, NULL }
    }
  }, { // row 2
    { // RCL, STO, MEM, T
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void*)'T' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // ROLLD, ROLLU, LASTX, U
      { key_op, (void*)FC_CALCULATOR_OPERATION_ROLLDOWN },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ROLLUP },
      { key_op, (void*)FC_CALCULATOR_OPERATION_LASTX },
      { key_alpha, (void*)'U' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // SIN, ASIN, HYP, V
      { key_op, (void*)FC_CALCULATOR_OPERATION_SIN },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ASIN },
      { key_mod, (void*)FC_KEY_MOD_HYP},
      { key_alpha, (void*)'V' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // COS, ACOS, PI, W
      { key_op, (void*)FC_CALCULATOR_OPERATION_COS },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ACOS },
      { NULL, NULL },
      { key_alpha, (void*)'W' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // TAN, ATAN, EULER
      { key_op, (void*)FC_CALCULATOR_OPERATION_TAN },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ATAN },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }
  }, { // row 3
    { // ENTER
      { key_enter, NULL },
      { key_enter, NULL },
      { key_enter, NULL },
      { key_enter, NULL },
      { key_nav, (void *)FC_KEY_NAV_ENTER },
      { key_enter, NULL }
    }, {  // SWAP, STATPUSH, STATTPOP, Q
      { key_op, (void*)FC_CALCULATOR_OPERATION_SWAP },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'Q' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // NEG, MODE, SYM, R
      { key_neg, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'R' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // E, DISP, UNIT, S
      { key_exp, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'S' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // BKSP, CLR, DEL
      { key_bksp, NULL },
      { key_clear, NULL },
      { key_del, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    }
  }, { // row 4
    { // ALT
      { key_mod, (void*)FC_KEY_MOD_ALT },
      { key_mod, (void*)FC_KEY_MOD_ALT },
      { key_mod, (void*)FC_KEY_MOD_ALT },
      { key_mod, (void*)FC_KEY_MOD_ALT },
      { key_mod, (void*)FC_KEY_MOD_ALT },
      { key_mod, (void*)FC_KEY_MOD_ALT }
    }, { // 7, ABS, GRAF, M
      { key_digit, (void*)7 },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ABS },
      { NULL, NULL },
      { key_alpha, (void *)'M' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 8, ARG, LOGI, N
      { key_digit, (void*)8 },
      { key_op, (void*)FC_CALCULATOR_OPERATION_ARG },
      { NULL, NULL },
      { key_alpha, (void *)'N' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 9, TST, PRNT, O
      { key_digit, (void*)9 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'O' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // DIV, P, RIGHT
      { key_op, (void*)FC_CALCULATOR_OPERATION_DIVIDE },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'P' },
      { key_nav, (void *)FC_KEY_NAV_RIGHT },
      { NULL, NULL }
    }
  }, { // row 5
    { // SHIFT_LEFT
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_L }
    }, { // 4, BASE, SOLV, I
      { key_digit, (void*)4 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'I' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 5, CNVT, IDX, J
      { key_digit, (void*)5 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'J' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 6, FLAG, CAT, K
      { key_digit, (void*)6 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'K' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // MUL, L, UP
      { key_op, (void*)FC_CALCULATOR_OPERATION_MULTIPLY },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'L' },
      { key_nav, (void *)FC_KEY_NAV_UP },
      { NULL, NULL }
    }
  }, { // row 6
    { // SHIFT_RIGHT
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R },
      { key_mod, (void*)FC_KEY_MOD_SHIFT_R }
    }, { // 1, ASGN, PROB, E
      { key_digit, (void*)1 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'E' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 2, CUST, STAT, F
      { key_digit, (void*)2 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'F' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // 3, CNST, MAT, G
      { key_digit, (void*)3 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'G' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // SUB, H, DOWN
      { key_op, (void*)FC_CALCULATOR_OPERATION_SUBTRACT },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'H' },
      { key_nav, (void *)FC_KEY_NAV_DOWN },
      { NULL, NULL }
    }
  }, { // row 7
    { // EXIT, ON, OFF
      { key_exit, (void*)NULL },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_nav, (void *)FC_KEY_NAV_EXIT },
      { NULL, NULL }
    }, { // 0, MENU, SET, A
      { key_digit, (void*)0 },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'A' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // ., SHOW, FAC, B
      { key_decimal, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'B' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // R/S, PRGM, FCN, C
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'C' },
      { NULL, NULL },
      { NULL, NULL }
    }, { // ADD, D, LEFT
      { key_op, (void*)FC_CALCULATOR_OPERATION_ADD },
      { NULL, NULL },
      { NULL, NULL },
      { key_alpha, (void *)'D' },
      { key_nav, (void *)FC_KEY_NAV_LEFT },
      { NULL, NULL }
    }
  }
};

#ifdef __cplusplus
}
#endif

#endif