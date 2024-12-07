#include <Arduino.h>
#include "fc_keyboard.h"
#include "fc_display.h"
#include "fc_math.h"
#include "fc_number_formatter.h"

disp_data_t disp_data;

void fc_kb_handler(uint8_t keycode, fc_kb_action_t action) {

}

void setup() {
  delay(10000);
  flags_t flags = {
    .mod_shift_r = true,
    .mod_shift_l = true,
    .mod_alt = true,
    .hyp = true,
    .alpha = true,
    .nav = true
  };
  disp_data.flags = flags;
  strcpy(disp_data.lines[0], "Hello 1");
  strcpy(disp_data.lines[1], "Hello 2");
  strcpy(disp_data.lines[2], "Hello 3");
  strcpy(disp_data.lines[3], "Hello 4");

  strcpy(disp_data.menu_labels[0], "MEN 1");
  strcpy(disp_data.menu_labels[1], "MEN 2");
  strcpy(disp_data.menu_labels[2], "MEN 3");
  strcpy(disp_data.menu_labels[3], "MEN 4");
  strcpy(disp_data.menu_labels[4], "MEN 5");
  fc_dp_update(&disp_data);
}

void loop() {

}

void setup1() {
  fc_dp_init();
}

void loop1() {
  fc_dp_draw();
}