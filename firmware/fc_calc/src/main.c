#include <Arduino.h>
#include "fc_keyboard.h"
#include "fc_display.h"
#include "fc_math.h"
#include "fc_calculator.h"
#include "fc_format.h"
#include "fc_keymap.h"
#include "fc_log.h"
#include "fc_input.h"

fc_disp_data_t disp_data;
fc_calculator_state_t calculator_state;
fc_input_state_t input_state;


void update_display(void) {
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY || disp_data.disp_state == FC_DISP_STATE_NORMAL) {
    fc_input_get_str(&input_state, disp_data.lines[0], FC_LINE_BUF_SIZE);
    for (int i = 0; i < 3; ++i) {
      fc_format(fc_calculator_stack_get(&calculator_state, i), FC_BASE_DEC, disp_data.lines[i + 1], FC_LINE_BUF_SIZE);
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      fc_format(fc_calculator_stack_get(&calculator_state, i), FC_BASE_DEC, disp_data.lines[i], FC_LINE_BUF_SIZE);
    }
  }
  fc_dp_update(&disp_data);
}

void mod_toggle_lock() {
  disp_data.flags.mod_lock = !disp_data.flags.mod_lock;
}

void mod_clear() {
  if (!disp_data.flags.mod_lock) {
    disp_data.flags.mod_shift_r = false;
    disp_data.flags.mod_shift_l = false;
    disp_data.flags.mod_alt = false;  
  }
  disp_data.flags.hyp = false;
}

void mod_toggle(fc_kb_action_t action, fc_key_mod_t mod) {
  if (action == FC_KB_ACTION_PRESSED) {
    if (disp_data.flags.mod_lock) {
      if (mod == FC_KEY_MOD_HYP) {
        disp_data.flags.hyp = !disp_data.flags.hyp;
        return;
      }
      disp_data.flags.mod_shift_r = false;
      disp_data.flags.mod_shift_l = false;
      disp_data.flags.mod_alt = false;
      switch (mod) {
        case FC_KEY_MOD_SHIFT_R: disp_data.flags.mod_shift_r = true; break;
        case FC_KEY_MOD_SHIFT_L: disp_data.flags.mod_shift_l = true; break;
        case FC_KEY_MOD_ALT: disp_data.flags.mod_alt = true; break;
        default: break;
      }
    } else {
      switch (mod) {
        case FC_KEY_MOD_SHIFT_R: 
          disp_data.flags.mod_shift_r = !disp_data.flags.mod_shift_r;
          disp_data.flags.mod_shift_l = false;
          disp_data.flags.mod_alt = false; 
          break;
        case FC_KEY_MOD_SHIFT_L: 
          disp_data.flags.mod_shift_l = !disp_data.flags.mod_shift_l;
          disp_data.flags.mod_shift_r = false;
          disp_data.flags.mod_alt = false;
          break;
        case FC_KEY_MOD_ALT: 
          disp_data.flags.mod_alt = !disp_data.flags.mod_alt;
          disp_data.flags.mod_shift_r = false;
          disp_data.flags.mod_shift_l = false;
          break;
        case FC_KEY_MOD_HYP: 
          bool flag = !disp_data.flags.hyp;
          mod_clear();
          disp_data.flags.hyp = flag;
          break;
      }
    }
  } else {
    if (!disp_data.flags.mod_lock) return;
    disp_data.flags.mod_shift_r = false;
    disp_data.flags.mod_shift_l = false;
    disp_data.flags.mod_alt = false;
  }
}

void fc_kb_handler(uint8_t keycode, fc_kb_action_t action) {
  uint8_t row = keycode & 0x0F;
  uint8_t col = (keycode >> 4) & 0x0F;

  fc_key_action_t key_action = keymap[row][col][0];
  if (disp_data.flags.mod_alt) key_action = keymap[row][col][5];
  if (disp_data.flags.mod_shift_r) key_action = keymap[row][col][1];
  if (disp_data.flags.mod_shift_l) key_action = keymap[row][col][2];
  if (disp_data.flags.alpha) key_action = keymap[row][col][3];
  if (disp_data.flags.nav) key_action = keymap[row][col][4];

  if (!key_action.on_press) return;
  key_action.on_press(action, key_action.arg);
  update_display();
}

void key_op(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state == FC_DISP_STATE_RESULT) {
  } else if (disp_data.disp_state == FC_DISP_STATE_NORMAL) {
    fc_scalar_t x = fc_input_get(&input_state);
    fc_calculator_perform_operation(&calculator_state, FC_CALCULATOR_OPERATION_PUSH, FC_SCALAR_TYPE_C, &x);
  } else if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
    fc_scalar_t x = fc_input_get(&input_state);
    fc_calculator_perform_operation(&calculator_state, FC_CALCULATOR_OPERATION_PUSH, FC_SCALAR_TYPE_C, &x);
  }
  if (disp_data.flags.hyp) {
    switch ((fc_calculator_operation_t)arg) {
      case FC_CALCULATOR_OPERATION_SIN: arg = (void*)FC_CALCULATOR_OPERATION_SINH; break;
      case FC_CALCULATOR_OPERATION_COS: arg = (void*)FC_CALCULATOR_OPERATION_COSH; break;
      case FC_CALCULATOR_OPERATION_TAN: arg = (void*)FC_CALCULATOR_OPERATION_TANH; break;
      case FC_CALCULATOR_OPERATION_ASIN: arg = (void*)FC_CALCULATOR_OPERATION_ASINH; break;
      case FC_CALCULATOR_OPERATION_ACOS: arg = (void*)FC_CALCULATOR_OPERATION_ACOSH; break;
      case FC_CALCULATOR_OPERATION_ATAN: arg = (void*)FC_CALCULATOR_OPERATION_ATANH; break;
      default: break;
    }
  }
  fc_calculator_perform_operation(&calculator_state, (fc_calculator_operation_t)arg, FC_SCALAR_TYPE_C);
  fc_scalar_t x = fc_calculator_stack_get(&calculator_state, 0);
  fc_input_set(&input_state, x);
  disp_data.disp_state = FC_DISP_STATE_RESULT;
  mod_clear();
}

void key_enter(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
    fc_input_set(&input_state, fc_input_get(&input_state));
  }
  fc_scalar_t x = fc_input_get(&input_state);
  fc_calculator_perform_operation(&calculator_state, FC_CALCULATOR_OPERATION_PUSH, FC_SCALAR_TYPE_C, &x);
  disp_data.disp_state = FC_DISP_STATE_NORMAL;
}

void key_digit(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state != FC_DISP_STATE_ENTRY) {
    fc_input_clear(&input_state);
  }
  fc_input_add_digit(&input_state, (unsigned char)arg);
  disp_data.disp_state = FC_DISP_STATE_ENTRY;
}
void key_neg(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
    fc_input_toggle_sign(&input_state);
  } else {
    key_op(FC_KB_ACTION_PRESSED, (void*)FC_CALCULATOR_OPERATION_NEGATE);
  }
}

void key_decimal(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state != FC_DISP_STATE_ENTRY) {
    fc_input_clear(&input_state);
  }
  fc_input_add_decimal(&input_state);
  disp_data.disp_state = FC_DISP_STATE_ENTRY;
}

void key_exp(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
    fc_input_add_exponent(&input_state);
  }
}

void key_backspace(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  if (disp_data.disp_state != FC_DISP_STATE_ENTRY) {
    fc_input_clear(&input_state);
  }
  fc_input_delete(&input_state);
  disp_data.disp_state = FC_DISP_STATE_ENTRY;
}

void key_clear(fc_kb_action_t kb_action, void *arg) {
  if (kb_action != FC_KB_ACTION_PRESSED) return;
  fc_input_clear(&input_state);
  disp_data.disp_state = FC_DISP_STATE_ENTRY;
}

void key_del(fc_kb_action_t kb_action, void *arg) {}

void key_alpha(fc_kb_action_t kb_action, void *arg) {}

void key_charset(fc_kb_action_t kb_action, void *arg) {}

void key_func(fc_kb_action_t kb_action, void *arg) {}

void key_mod(fc_kb_action_t kb_action, void *arg) {
  if (kb_action == FC_KB_ACTION_PRESSED && arg == FC_KEY_MOD_ALT && disp_data.flags.mod_shift_r) {
    mod_toggle_lock();
    return;
  }
  mod_toggle(kb_action, (fc_key_mod_t)arg);
}

void key_exit(fc_kb_action_t kb_action, void *arg) {}

void key_nav(fc_kb_action_t kb_action, void *arg) {}

void setup() {
  fc_log_init();
  fc_kb_init();

  disp_data.flags.mod_shift_r = false;
  disp_data.flags.mod_shift_l = false;
  disp_data.flags.mod_alt = false;
  disp_data.flags.mod_lock = false;
  disp_data.flags.hyp = false;
  disp_data.flags.alpha = false;
  disp_data.flags.nav = false;
  
  disp_data.disp_state = FC_DISP_STATE_NORMAL;

  for (int i = 0; i < FC_MENU_LABEL_NUM; ++i) {
    disp_data.menu_labels[i][0] = '\0';
  }

  fc_calculator_init(&calculator_state);
  fc_input_init(&input_state);

  update_display();
}

void loop() {
  fc_kb_scan();
}

void setup1() {
  fc_dp_init();
}

void loop1() {
  fc_dp_draw();
}