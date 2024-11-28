#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

void dp_init(void);

void dp_clear_buf(void);
void dp_send_buf(void);

void dp_draw_menu(const char labels[5][6]);
void dp_draw_text(const char * text, uint8_t row);

void dp_draw_flags(bool sl, bool sr, bool alt, bool alph, bool hyp, bool nav);

#endif