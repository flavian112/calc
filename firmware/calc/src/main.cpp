#include <Arduino.h>

#include "fc_calc.h"
#include "keyboard.h"
#include "display.h"
#include "input_handler.h"

#define TEXT_BUF_SIZE (64)

enum disp_state_t {
  DISP_STATE_NORMAL,
  DISP_STATE_INPUT,
  DISP_STATE_RESULT,
} typedef disp_state_t;

enum nav_dir_t {
  NAV_DIR_R,
  NAV_DIR_U,
  NAV_DIR_D,
  NAV_DIR_L
} typedef nav_dir_t;

struct flags_t {
  bool shl;
  bool shr;
  bool alt;
  bool alph;
  bool hyp;
  bool nav;
} typedef flags_t;

struct screen_data {
  char labels[5][6];
  disp_state_t disp_state;
  char line0[TEXT_BUF_SIZE];
  char line1[TEXT_BUF_SIZE];
  char line2[TEXT_BUF_SIZE];
  char line3[TEXT_BUF_SIZE];
  flags_t flags;
} typedef screen_data_t;

static char text_buf[TEXT_BUF_SIZE] = {0};
static fc_calc_state_t calc_state;
static flags_t flags = { 0 };
static char labels[5][6] = {"F1", "F2", "F3", "F4", "F5"};
static disp_state_t disp_state = DISP_STATE_NORMAL;
static ih_state_t input_handler_state;

auto_init_mutex(global_mutex);
static screen_data_t screen_data_core0;
static screen_data_t screen_data_core1;
static volatile bool screen_update_available = false;

void update_screen(void) {
  mutex_enter_blocking(&global_mutex);
  if (disp_state == DISP_STATE_NORMAL || disp_state == DISP_STATE_INPUT) {
    strcpy(screen_data_core0.line0, ih_str(&input_handler_state));
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state, 0), 5, screen_data_core0.line1);
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,1), 5, screen_data_core0.line2);
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,2), 5, screen_data_core0.line3);
  }
  if (disp_state == DISP_STATE_RESULT) {
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,0), 5, screen_data_core0.line0);
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,1), 5, screen_data_core0.line1);
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,2), 5, screen_data_core0.line2);
    //nf_format_complex(NF_NUMBER_FORMAT_ALL, fc_calc_stack_get(&calc_state,3), 5, screen_data_core0.line3);
  }
  memcpy(&screen_data_core0.disp_state, &disp_state, sizeof(disp_state_t));
  memcpy(screen_data_core0.labels, labels, sizeof(labels));
  memcpy(&screen_data_core0.flags, &flags, sizeof(flags_t));
  screen_update_available = true;
  mutex_exit(&global_mutex);
}

void draw_screen(void) {
  mutex_enter_blocking(&global_mutex);
  bool redraw_screen = false;
  if (screen_update_available) {
    memcpy(&screen_data_core1, &screen_data_core0, sizeof(screen_data_t));
    redraw_screen = true;
    screen_update_available = false;
  }
  mutex_exit(&global_mutex);

  if (!redraw_screen) return;

  dp_clear_buf();
  dp_draw_menu(screen_data_core1.labels);

  if (screen_data_core1.disp_state == DISP_STATE_INPUT) {
    size_t len = strlen(screen_data_core1.line0);
    screen_data_core1.line0[len++] = '_';
    screen_data_core1.line0[len] = '\0';
  }
  
  dp_draw_text(screen_data_core1.line0, 0);
  dp_draw_text(screen_data_core1.line1, 1);
  dp_draw_text(screen_data_core1.line2, 2);
  dp_draw_text(screen_data_core1.line3, 3);
  
  dp_draw_flags(screen_data_core1.flags.shl, 
                screen_data_core1.flags.shr, 
                screen_data_core1.flags.alt, 
                screen_data_core1.flags.alph, 
                screen_data_core1.flags.hyp, 
                screen_data_core1.flags.nav);
  dp_send_buf();
}

void key_digit(uint8_t digit) {
  if (disp_state == DISP_STATE_NORMAL || disp_state == DISP_STATE_RESULT) {
    ih_clear(&input_handler_state);
    disp_state = DISP_STATE_INPUT;
  }
  if (disp_state == DISP_STATE_INPUT) {
    ih_add_digit(&input_handler_state, digit);
  }
}

void key_alpha(char character) {
}

void key_dot(void) {
  if (disp_state == DISP_STATE_NORMAL || disp_state == DISP_STATE_RESULT) {
    ih_clear(&input_handler_state);
    disp_state = DISP_STATE_INPUT;
  }
  if (disp_state == DISP_STATE_INPUT) {
    ih_add_decimal(&input_handler_state);
  }
}

void key_scn(void) {
  if (disp_state == DISP_STATE_INPUT) {
    ih_add_exp(&input_handler_state);
  }
}

void key_bspc(void) {
  if (disp_state == DISP_STATE_INPUT) {
    ih_del(&input_handler_state);
  }
}

void key_clr(void) {
  if (disp_state == DISP_STATE_INPUT) {
    ih_clear(&input_handler_state);
  }
  flags.shl = false;
  flags.shr = false;
}

void key_enter(void) {
  if (disp_state == DISP_STATE_INPUT || disp_state == DISP_STATE_NORMAL) {
    fc_calc_stack_push(&calc_state, ih_get_number(&input_handler_state));
  }
  if (disp_state == DISP_STATE_RESULT) {
    fc_calc_stack_push(&calc_state, fc_calc_stack_get(&calc_state, 0));
  }
  disp_state = DISP_STATE_NORMAL;
}

void key_on(void) {
}

void key_off(void) {
}

void key_exit(void) {
}

void key_nav(nav_dir_t dir) {
}

void dm_op(uint8_t index) {
}

void execute_operation(fc_calc_op_t) {
  
  flags.shl = false;
  flags.shr = false;
  disp_state = DISP_STATE_RESULT;
}

void key_neg(void) {
  if (disp_state == DISP_STATE_INPUT) {
    ih_neg(&input_handler_state);
  } else {
    execute_operation(FC_CALC_OP_NEG_C_C);
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
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_INV_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_POW_CC_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_EXP2_C_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('X');
      break;
    case 0x11: // sqrt(x)
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_SQRT_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_SQ_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_ROOT_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('Y');
      break;
    case 0x21: // log
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_LOG10_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_EXP10_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_LOG2_C_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('Z');
      break;
    case 0x31: // ln
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_LN_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_EXP_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_LOG_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph); // flags.alph menu
      break;
    case 0x41: // xeq
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph); // XEQ
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // GTO
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // TYPE
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha(' ');
      break;

    case 0x02: // rcl
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph); // RCL
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // STO
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // MEM
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('T');
      break;
    case 0x12: // roll down
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph); // RD
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // RU
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // LSTx
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('U');
      break;
    case 0x22: // sin
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_SIN_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_ASIN_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) flags.hyp = !flags.hyp;
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('V');
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_SINH_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_ASINH_C_C);
      break;
    case 0x32: // cos
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_COS_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_ACOS_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // const pi
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('W');
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_COSH_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_ACOSH_C_C);
      break;
    case 0x42: // tan
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_TAN_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && !flags.hyp) execute_operation(FC_CALC_OP_ATAN_C_C);
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // const e
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_TANH_C_C);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph && flags.hyp) execute_operation(FC_CALC_OP_ATANH_C_C);
      break;

    case 0x03: // enter
      if (state) key_enter();
      break;
    case 0x13: // swap
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph); // SWAP
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // STAT PUSH
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // STAT POP
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('Q');
      break;
    case 0x23: // negate
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_neg();
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // MODE
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // SYM
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('R');
      break;
    case 0x33: // E
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_scn();
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // UNIT
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // DISP
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('S');
      break;
    case 0x43: // backspace
      if (state && !flags.shl && !flags.shr && !flags.alt) key_bspc();
      if (state && !flags.shl && flags.shr && !flags.alt) key_clr();
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // DEL
      break;

    case 0x04: // alt
      if (state) flags.alt = !flags.alt;
      break;
    case 0x14: // 7
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(7);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // GRAF
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_ABS_C_D);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('M');
      break;
    case 0x24: // 8
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(8);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // LOGI
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph) execute_operation(FC_CALC_OP_ARG_C_D);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('N');
      break;
    case 0x34: // 9
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(9);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // TST
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // PRNT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('O');
      break;
    case 0x44: // div
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.nav) execute_operation(FC_CALC_OP_DIV_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph && !flags.nav) key_alpha('P');
      if (state && !flags.alt && flags.nav) key_nav(NAV_DIR_R);
      break;

    case 0x05: // shift left
      if (state) { flags.shl = !flags.shl; flags.shr = false; }
      break;
    case 0x15: // 4
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(4);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // BASE
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // SOLV
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('I');
      break;
    case 0x25: // 5
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(5);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // CNVT
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // INT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('J');
      break;
    case 0x35: // 6
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(6);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // FLAG
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // CAT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('K');
      break;
    case 0x45: // mult
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.nav) execute_operation(FC_CALC_OP_MUL_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph && !flags.nav) key_alpha('L');
      if (state && !flags.alt && flags.nav) key_nav(NAV_DIR_U);
      break;

    case 0x06: // shift right
      if (state) { flags.shr = !flags.shr; flags.shl = false; }
      break;
    case 0x16: // 1
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(1);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // ASGN
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // PROB
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('E');
      break;
    case 0x26: // 2
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(2);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // CUST
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // STAT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('F');
      break;
    case 0x36: // 3
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(3);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // CNST
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // MAT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('G');
      break;
    case 0x46: // sub
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.nav) execute_operation(FC_CALC_OP_SUB_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph && !flags.nav) key_alpha('H');
      if (state && !flags.alt && flags.nav) key_nav(NAV_DIR_D);
      break;

    case 0x07: // exit
      if (state && !flags.shl && !flags.shr) key_exit();
      if (state && !flags.shl && flags.shr) key_on();
      if (state && flags.shl && !flags.shr) key_off();
      break;
    case 0x17: // 0
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_digit(0);
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // MENU
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // SET
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('A');
      break;
    case 0x27: // .
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph) key_dot();
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // SHOW
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // FACT
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('B');
      break;
    case 0x37: // R/S
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph); // R/S
      if (state && !flags.shl && flags.shr && !flags.alt && !flags.alph); // PRGM
      if (state && flags.shl && !flags.shr && !flags.alt && !flags.alph); // FCN
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph) key_alpha('C');
      break;
    case 0x47: // add
      if (state && !flags.shl && !flags.shr && !flags.alt && !flags.alph && !flags.nav) execute_operation(FC_CALC_OP_ADD_CC_C);
      if (state && !flags.shl && !flags.shr && !flags.alt && flags.alph && !flags.nav) key_alpha('C');
      if (state && !flags.alt && flags.nav) key_nav(NAV_DIR_L);
      break;
  }
  update_screen();
}

void setup() {
  Serial1.begin(115200);
  kb_init();

  calc_state = fc_calc_init();
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

