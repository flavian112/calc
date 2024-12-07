#include "keyboard.h"
#include <Arduino.h>

#define KB_NUM_ROW (8)
#define KB_NUM_COL (5)

static const uint8_t kb_pin_row[KB_NUM_ROW] = {2, 3, 4, 5, 6, 7, 8, 9};
static const uint8_t kb_pin_col[KB_NUM_COL] = {10, 11, 12, 13, 14};

static bool kb_keys_prev[KB_NUM_ROW][KB_NUM_COL] = {0};
static bool kb_keys[KB_NUM_ROW][KB_NUM_COL] = {0};

void kb_init(void) {
  for (int i = 0; i < KB_NUM_ROW; ++i) {
    pinMode(kb_pin_row[i], INPUT_PULLDOWN);
  }
  for (int i = 0; i < KB_NUM_COL; ++i) {
    pinMode(kb_pin_col[i], OUTPUT);
    digitalWrite(kb_pin_col[i], LOW);
  }
}

void kb_scan(void) {
  memcpy(kb_keys_prev, kb_keys, sizeof(kb_keys));
  for(int i = 0; i < KB_NUM_COL; ++i) {
    digitalWrite(kb_pin_col[i], HIGH);
    for(int j = 0; j < KB_NUM_ROW; ++j) {
      delayMicroseconds(50);
      kb_keys[j][i] = digitalRead(kb_pin_row[j]) == HIGH ? true : false;
      delayMicroseconds(50);
    }
    digitalWrite(kb_pin_col[i], LOW);
  }
  for (int i = 0; i < KB_NUM_ROW; ++i) {
    for (int j = 0; j < KB_NUM_COL; ++j) {
      if (kb_keys[i][j] != kb_keys_prev[i][j]) {
        kb_handler(i, j, kb_keys[i][j]);
      }
    }
  }
}