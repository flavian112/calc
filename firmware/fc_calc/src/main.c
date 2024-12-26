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
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
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


void fc_kb_handler(uint8_t keycode, fc_kb_action_t action) {
  if (action != FC_KB_ACTION_PRESSED) return;
  uint8_t row = keycode & 0x0F;
  uint8_t col = (keycode >> 4) & 0x0F;

  fc_key_action_t key_action = keymap[row][col][0];
  if (disp_data.flags.mod_alt) key_action = keymap[row][col][5];
  if (disp_data.flags.mod_shift_r) key_action = keymap[row][col][1];
  if (disp_data.flags.mod_shift_l) key_action = keymap[row][col][2];
  if (disp_data.flags.alpha) key_action = keymap[row][col][3];
  if (disp_data.flags.nav) key_action = keymap[row][col][4];

  if (!key_action.on_press) return;
  key_action.on_press(key_action.arg);
  update_display();
}

void key_func(void *arg) {
}

void key_op(void *arg) {
}

void key_digit(void *arg) {
  if (disp_data.disp_state == FC_DISP_STATE_ENTRY) {
    fc_input_add_digit(&input_state, (unsigned char)arg);
  } else {
    fc_input_clear(&input_state);
    fc_input_add_digit(&input_state, (unsigned char)arg);
    disp_data.disp_state = FC_DISP_STATE_ENTRY;
  }
}

void key_alpha(void *arg) {
}

void key_charset(void *arg) {
}

void key_enter(void *arg) {  
}

void key_mod(void *arg) {

}

void key_neg(void *arg) {
}

void key_exp(void *arg) {
}

void key_decimal(void *arg) {
}

void key_bksp(void *arg) {

}

void key_clear(void *arg) {

}

void key_del(void *arg) {

}

void key_nav(void *arg) {

}

void key_exit(void *arg) {

}



void setup() {
  fc_log_init();
  fc_kb_init();

  disp_data.flags.mod_shift_r = false;
  disp_data.flags.mod_shift_l = false;
  disp_data.flags.mod_alt = false;
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