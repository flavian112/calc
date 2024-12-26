#ifndef FC_KEYBOARD_H
#define FC_KEYBOARD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FC_KB_ACTION_PRESSED,
  FC_KB_ACTION_RELEASED
} fc_kb_action_t;

void fc_kb_init(void);
void fc_kb_scan(void);
void fc_kb_handler(uint8_t keycode, fc_kb_action_t action) __attribute__((weak));

#ifdef __cplusplus
}
#endif

#endif