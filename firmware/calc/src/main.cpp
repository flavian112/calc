#include <Arduino.h>

#include "calc.h"
#include "keyboard.h"
#include "display.h"
#include "input_handler.h"

#define TEXT_BUF_SIZE (64)

static char text_buf[TEXT_BUF_SIZE] = {0};

static ih_state_t input_handler_state;

enum State {
  STATE_NORMAL,
  STATE_INPUT,
  STATE_RESULT,
};

enum NAV_DIR {
  NAV_R,
  NAV_U,
  NAV_D,
  NAV_L
};

enum Operation {
  OP_INV_X,
  OP_PWR_YX,
  OP_PWR2_X,
  OP_SQRT_X,
  OP_SQ_X,
  OP_ROOT_YX,
  OP_LOG_X,
  OP_PWR10_X,
  OP_LOG2_X,
  OP_LN_X,
  OP_EXP_X,
  OP_LOG_YX,
  OP_RCL_X,
  OP_STO_X,
  OP_ROLD,
  OP_ROLU,
  OP_LST_X,
  OP_SIN_X,
  OP_ASIN_X,
  OP_SINH_X,
  OP_ASINH_X,
  OP_COS_X,
  OP_ACOS_X,
  OP_COSH_X,
  OP_ACOSH_X,
  OP_TAN_X,
  OP_ATAN_X,
  OP_TANH_X,
  OP_ATANH_X,
  OP_SWP_XY,
  OP_STAT_PUSH,
  OP_STAT_POP,
  OP_NEG_X,
  OP_ABS_X,
  OP_ARG_X,
  OP_DIV_YX,
  OP_MUL_YX,
  OP_SUB_YX,
  OP_FACT_X,
  OP_ADD_YX
};


char labels[5][6] = {"F1", "F2", "F3", "F4", "F5"};

static bool mod_shiftl = false;
static bool mod_shiftr = false;
static bool mod_alt = false;
static bool alpha = false;
static bool hyp = false;
static bool nav = false;

static State current_state = STATE_NORMAL;

struct screen_data {
  char labels[5][6];
  State state;
  char line0[TEXT_BUF_SIZE];
  char line1[TEXT_BUF_SIZE];
  char line2[TEXT_BUF_SIZE];
  char line3[TEXT_BUF_SIZE];
  bool flags[6];
} typedef screen_data_t;

auto_init_mutex(global_mutex);

static screen_data_t screen_data_core0;
static screen_data_t screen_data_core1;

void update_screen(void) {
  mutex_enter_blocking(&global_mutex);
  if (current_state == STATE_NORMAL || current_state == STATE_INPUT) {
    strcpy(screen_data_core0.line0, ih_str(&input_handler_state));
    sprintf(screen_data_core0.line1, "%g", creal(ca_stack_get(0).cdval));
    sprintf(screen_data_core0.line2, "%g", creal(ca_stack_get(1).cdval));
    sprintf(screen_data_core0.line3, "%g", creal(ca_stack_get(2).cdval));
  }
  if (current_state == STATE_RESULT) {
    sprintf(screen_data_core0.line0, "%g", creal(ca_stack_get(0).cdval));
    sprintf(screen_data_core0.line1, "%g", creal(ca_stack_get(1).cdval));
    sprintf(screen_data_core0.line2, "%g", creal(ca_stack_get(2).cdval));
    sprintf(screen_data_core0.line3, "%g", creal(ca_stack_get(3).cdval));
  }
  screen_data_core0.state = current_state;
  memcpy(screen_data_core0.labels, labels, sizeof(labels));
  screen_data_core0.flags[0] = mod_shiftl; 
  screen_data_core0.flags[0] = mod_shiftr; 
  screen_data_core0.flags[0] = mod_alt;
  screen_data_core0.flags[0] = alpha;
  screen_data_core0.flags[0] = hyp;
  screen_data_core0.flags[0] = nav;
  mutex_exit(&global_mutex);
}


void draw_screen(void) {
  mutex_enter_blocking(&global_mutex);
  memcpy(&screen_data_core1, &screen_data_core0, sizeof(screen_data_t));
  mutex_exit(&global_mutex);

  dp_clear_buf();
  dp_draw_menu(screen_data_core1.labels);
  
  dp_draw_text(screen_data_core1.line0, 0);
  dp_draw_text(screen_data_core1.line1, 1);
  dp_draw_text(screen_data_core1.line2, 2);
  dp_draw_text(screen_data_core1.line3, 3);
  
  dp_draw_flags(screen_data_core1.flags[0], 
                screen_data_core1.flags[1], 
                screen_data_core1.flags[2], 
                screen_data_core1.flags[3], 
                screen_data_core1.flags[4], 
                screen_data_core1.flags[5]);
  dp_send_buf();
}

void key_digit(uint8_t digit) {
  if (current_state == STATE_NORMAL || current_state == STATE_RESULT) {
    ih_clear(&input_handler_state);
    current_state = STATE_INPUT;
  }
  if (current_state == STATE_INPUT) {
    ih_add_digit(&input_handler_state, digit);
  }
}

void key_alpha(char character) {
}

void key_dot(void) {
  if (current_state == STATE_NORMAL || current_state == STATE_RESULT) {
    ih_clear(&input_handler_state);
    current_state = STATE_INPUT;
  }
  if (current_state == STATE_INPUT) {
    ih_add_decimal(&input_handler_state);
  }
}

void key_scn(void) {
  if (current_state == STATE_INPUT) {
    ih_add_exp(&input_handler_state);
  }
}

void key_bspc(void) {
}

void key_clr(void) {
  if (current_state == STATE_INPUT) {
    ih_clear(&input_handler_state);
  }
}

void key_enter(void) {
  if (current_state == STATE_INPUT || current_state == STATE_NORMAL) {
    ca_stack_push_x(ih_get_number(&input_handler_state));
  }
  if (current_state == STATE_RESULT) {
    ca_stack_push_x(ca_stack_get(0));
  }
  current_state = STATE_NORMAL;
}

void key_on(void) {
}

void key_off(void) {
}

void key_exit(void) {
}

void key_nav(NAV_DIR dir) {
}

void dm_op(uint8_t index) {
}

void ex_op(Operation op) {
  if (current_state == STATE_NORMAL || current_state == STATE_INPUT) {
    ca_stack_push_x(ih_get_number(&input_handler_state));
  }
  switch (op) {
    case OP_INV_X:
      ca_op_inv_x();
      break;
    case OP_PWR_YX:
      ca_op_pow_yx();
      break;
    case OP_PWR2_X:
      break;
    case OP_SQRT_X:
      ca_op_sqrt_x();
      break;
    case OP_SQ_X:
      ca_op_sq_x();
      break;
    case OP_ROOT_YX:
      ca_op_root_yx();
      break;
    case OP_LOG_X:
      break;
    case OP_PWR10_X:
      break;
    case OP_LOG2_X:
      break;
    case OP_LN_X:
      ca_op_ln();
      break;
    case OP_EXP_X:
      ca_op_expe_x();
      break;
    case OP_LOG_YX:
      ca_op_log_yx;
      break;
    case OP_RCL_X:
      break;
    case OP_STO_X:
      break;
    case OP_ROLD:
      ca_stack_roll_down();
      break;
    case OP_ROLU:
      ca_stack_roll_up();
      break;
    case OP_LST_X:
      break;
    case OP_SIN_X:
      ca_op_sin_x();
      break;
    case OP_ASIN_X:
      ca_op_asin_x();
      break;
    case OP_SINH_X:
      ca_op_sinh_x();
      break;
    case OP_ASINH_X:
      ca_op_asinh_x();
      break;
    case OP_COS_X:
      ca_op_cos_x();
      break;
    case OP_ACOS_X:
      ca_op_acos_x();
      break;
    case OP_COSH_X:
      ca_op_cosh_x();
      break;
    case OP_ACOSH_X:
      ca_op_acosh_x();
      break;
    case OP_TAN_X:
      ca_op_tan_x();
      break;
    case OP_ATAN_X:
      ca_op_atan_x();
      break;
    case OP_TANH_X:
      ca_op_tanh_x();
      break;
    case OP_ATANH_X:
      ca_op_atanh_x();
      break;
    case OP_SWP_XY:
      ca_stack_swap_yx();
      break;
    case OP_STAT_PUSH:
      break;
    case OP_STAT_POP:
      break;
    case OP_NEG_X:
      ca_op_neg_x();
      break;
    case OP_ABS_X:
      ca_op_abs_x();
      break;
    case OP_ARG_X:
      ca_op_arg_x();
      break;
    case OP_DIV_YX:
      ca_op_div_yx();
      break;
    case OP_MUL_YX:
      ca_op_mul_yx();
      break;
    case OP_SUB_YX:
      ca_op_sub_yx();
      break;
    case OP_FACT_X:
      break;
    case OP_ADD_YX:
      ca_op_add_yx();
      break;
  }

  current_state = STATE_RESULT;
}

void key_neg(void) {
  if (current_state == STATE_INPUT) {
    ih_neg(&input_handler_state);
  } else {
    ex_op(OP_NEG_X);
  }
}

void kb_handler(uint8_t row, uint8_t col, bool state) {
  uint8_t keycode = row | (col << 4);
  switch (keycode) {
    case 0x00: // F1
      if (state) dm_op(0);
      break;
    case 0x10: // F2
      if (state) dm_op(1);
      break;
    case 0x20: // F3
      if (state) dm_op(2);
      break;
    case 0x30: // F4
      if (state) dm_op(3);
      break;
    case 0x40: // F5
      if (state) dm_op(4);
      break;

    case 0x01: // 1/x
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_INV_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_PWR_YX);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_PWR2_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('X');
      break;
    case 0x11: // sqrt(x)
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_SQRT_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_SQ_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_ROOT_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('Y');
      break;
    case 0x21: // log
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_LOG_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_PWR10_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_LOG2_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('Z');
      break;
    case 0x31: // ln
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_LN_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_EXP_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_LOG_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha); // alpha menu
      break;
    case 0x41: // xeq
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // XEQ
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // GTO
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // TYPE
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha(' ');
      break;

    case 0x02: // rcl
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_RCL_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_STO_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) // MEM;
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('T');
      break;
    case 0x12: // roll down
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_ROLD);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_ROLU);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_LST_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('U');
      break;
    case 0x22: // sin
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_SIN_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_ASIN_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) hyp != hyp;
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('V');
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_SINH_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_ASINH_X);

      break;
    case 0x32: // cos
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_COS_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_ACOS_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // const pi
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('W');
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_COSH_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_ACOSH_X);
      break;
    case 0x42: // tan
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_TAN_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && !hyp) ex_op(OP_ATAN_X);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // const e
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_TANH_X);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha && hyp) ex_op(OP_ATANH_X);
      break;

    case 0x03: // enter
      if (state) key_enter();
      break;
    case 0x13: // swap
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_SWP_XY);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha) ex_op(OP_STAT_PUSH);
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_STAT_POP);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('Q');
      break;
    case 0x23: // negate
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_neg();
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // MODE
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // SYM
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('R');
      break;
    case 0x33: // E
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_scn();
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // UNIT
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // DISP
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('S');
      break;
    case 0x43: // backspace
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt) key_bspc();
      if (state && !mod_shiftl && mod_shiftr && !mod_alt) key_clr();
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // DEL
      break;

    case 0x04: // alt
      if (state) mod_alt = !mod_alt;
      break;
    case 0x14: // 7
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(7);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // GRAF
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_ABS_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('M');
      break;
    case 0x24: // 8
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(8);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // LOGI
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_ARG_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('N');
      break;
    case 0x34: // 9
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(9);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // TST
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // PRNT
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('O');
      break;
    case 0x44: // div
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !nav) ex_op(OP_DIV_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha && !nav) key_alpha('P');
      if (state && !mod_alt && nav) key_nav(NAV_R);
      break;

    case 0x05: // shift left
      if (state) { mod_shiftl = !mod_shiftl; mod_shiftr = false; }
      break;
    case 0x15: // 4
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(4);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // BASE
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // SOLV
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('I');
      break;
    case 0x25: // 5
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(5);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // CNVT
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // INT
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('J');
      break;
    case 0x35: // 6
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(6);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // FLAG
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // CAT
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('K');
      break;
    case 0x45: // mult
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !nav) ex_op(OP_MUL_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha && !nav) key_alpha('L');
      if (state && !mod_alt && nav) key_nav(NAV_U);
      break;

    case 0x06: // shift right
      if (state) { mod_shiftr = !mod_shiftr; mod_shiftl = false; }
      break;
    case 0x16: // 1
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(1);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // ASGN
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // PROB
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('E');
      break;
    case 0x26: // 2
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(2);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // CUST
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // STAT
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('F');
      break;
    case 0x36: // 3
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(3);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // CNST
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // MAT
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('G');
      break;
    case 0x46: // sub
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !nav) ex_op(OP_SUB_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha && !nav) key_alpha('H');
      if (state && !mod_alt && nav) key_nav(NAV_D);
      break;

    case 0x07: // exit
      if (state && !mod_shiftl && !mod_shiftr) key_exit();
      if (state && !mod_shiftl && mod_shiftr) key_on();
      if (state && mod_shiftl && !mod_shiftr) key_off();
      break;
    case 0x17: // 0
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_digit(0);
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // MENU
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // SET
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('A');
      break;
    case 0x27: // .
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha) key_dot();
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // SHOW
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha) ex_op(OP_FACT_X);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('B');
      break;
    case 0x37: // R/S
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // R/S
      if (state && !mod_shiftl && mod_shiftr && !mod_alt && !alpha); // PRGM
      if (state && mod_shiftl && !mod_shiftr && !mod_alt && !alpha); // FCN
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha) key_alpha('C');
      break;
    case 0x47: // add
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && !alpha && !nav) ex_op(OP_ADD_YX);
      if (state && !mod_shiftl && !mod_shiftr && !mod_alt && alpha && !nav) key_alpha('C');
      if (state && !mod_alt && nav) key_nav(NAV_L);
      break;
  }
  update_screen();
}

void setup() {
  Serial1.begin(115200);
  kb_init();

  input_handler_state = ih_init();

  update_screen();
}

void loop() {
  kb_scan();
}

void setup1() {
  dp_init();
}

void loop1() {
  draw_screen();
}

