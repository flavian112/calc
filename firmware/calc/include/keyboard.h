#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void kb_init(void);
void kb_scan(void);

__attribute__((weak)) void kb_handler(uint8_t row, uint8_t col, bool state);

#ifdef __cplusplus
}
#endif

#endif