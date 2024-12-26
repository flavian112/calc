#include "fc_keyboard.h"
#include <Arduino.h>

#define _NUM_ROWS (8)
#define _NUM_COLS (5)

static const uint8_t _row_pins[_NUM_ROWS] = {2, 3, 4, 5, 6, 7, 8, 9};
static const uint8_t _col_pins[_NUM_COLS] = {10, 11, 12, 13, 14};

static uint8_t _key_state_prev[_NUM_ROWS][_NUM_COLS] = {0};
static uint8_t _key_state_curr[_NUM_ROWS][_NUM_COLS] = {0};

void fc_kb_init(void) {
  for (int i = 0; i < _NUM_ROWS; ++i) {
    pinMode(_row_pins[i], INPUT_PULLDOWN);
  }
  for (int i = 0; i < _NUM_COLS; ++i) {
    pinMode(_col_pins[i], OUTPUT);
    digitalWrite(_col_pins[i], LOW);
  }
}

void fc_kb_scan(void) {
  memcpy(_key_state_prev, _key_state_curr, sizeof(_key_state_curr));
  for(int i = 0; i < _NUM_COLS; ++i) {
    digitalWrite(_col_pins[i], HIGH);
    for(int j = 0; j < _NUM_ROWS; ++j) {
      delayMicroseconds(50);
      _key_state_curr[j][i] = digitalRead(_row_pins[j]) == HIGH ? 1 : 0;
      delayMicroseconds(50);
    }
    digitalWrite(_col_pins[i], LOW);
  }
  for (int i = 0; i < _NUM_ROWS; ++i) {
    for (int j = 0; j < _NUM_COLS; ++j) {
      if (_key_state_curr[i][j] != _key_state_prev[i][j]) {
        uint8_t keycode = i | (j << 4);
        fc_kb_handler(keycode, _key_state_curr[i][j] ? FC_KB_ACTION_PRESSED : FC_KB_ACTION_RELEASED);
      }
    }
  }
}