#include "fc_display.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>


#define _PIN_SCK  (18)
#define _PIN_MOSI (19)
#define _PIN_CS   (17)
#define _PIN_CD   (20)
#define _PIN_RST  (21)

static U8G2_UC1611_EA_DOGXL240_F_4W_SW_SPI _u8g2(U8G2_R2, 
                                                 _PIN_SCK,
                                                 _PIN_MOSI, 
                                                 _PIN_CS, 
                                                 _PIN_CD, 
                                                 _PIN_RST);

auto_init_mutex(disp_mutex);
static disp_data_t disp_data_draw_buf;
static disp_data_t disp_data_pend_buf;
static volatile bool disp_update_pend = false;

static uint8_t _disp_w;
static uint8_t _disp_h;

void fc_dp_init(void) {
  _u8g2.begin();
  _u8g2.clearDisplay();
  _disp_w = _u8g2.getDisplayWidth();
  _disp_h = _u8g2.getDisplayHeight();
}

void _draw_menu(menu_labels_t labels) {
  uint8_t box_h = 11;
  uint8_t box_w = (_disp_w / 5) - 2;
  uint8_t box_y = _disp_h - box_h;
 
  _u8g2.setFont(u8g2_font_profont15_mr);
  _u8g2.setFontMode(true);
  for (int i = 0; i < MENU_LABEL_NUM; ++i) {
    uint8_t box_x = (i * (_disp_w / 5)) + 1;
    
    _u8g2.setDrawColor(1);
    _u8g2.drawBox(box_x, box_y, box_w, box_h);
    _u8g2.setDrawColor(0);
    for (int j = 0; j < MENU_LABEL_SIZE - 1; ++j) {
      if (!labels[i][0]) break;
      _u8g2.drawGlyph(box_x + 4 + j * 8, _disp_h - 1, labels[i][j]);
    }
  }
}

void _draw_lines(line_buf_t lines[4]) {
  _u8g2.setFont(u8g2_font_profont29_mr);
  _u8g2.setDrawColor(1);
  for (int i = 0; i < 4; ++i) {
    _u8g2.drawStr(0, _disp_h - 15 - (i * 23), lines[i]);
  }
}

void _draw_flags(flags_t flags) {
  _u8g2.setDrawColor(1);
  _u8g2.drawBox(0, 0, _disp_w, 11);
  _u8g2.setDrawColor(0);

  if (flags.mod_shift_l) {
    _u8g2.drawLine(2, 6, 8, 6);
    _u8g2.drawLine(8, 6, 8, 2);
    _u8g2.drawLine(2, 6, 5, 4);
    _u8g2.drawLine(2, 6, 5, 8);
  }

  if (flags.mod_shift_r) {
    _u8g2.drawLine(11 + 8, 6, 11 + 2, 6);
    _u8g2.drawLine(11 + 2, 6, 11 + 2, 2);
    _u8g2.drawLine(11 + 8, 6, 11 + 5, 4);
    _u8g2.drawLine(11 + 8, 6, 11 + 5, 8);
  }

  if (flags.mod_alt) {
    _u8g2.drawLine(22 + 2, 3, 22 + 3, 3);
    _u8g2.drawLine(22 + 6, 3, 22 + 8, 3);
    _u8g2.drawLine(22 + 3, 3, 22 + 6, 7);
    _u8g2.drawLine(22 + 6, 7, 22 + 8, 7);
  }

  if (flags.alpha) {
    _u8g2.drawLine(33 + 2, 8, 33 + 4, 8);
    _u8g2.drawLine(33 + 6, 8, 33 + 8, 8);
    _u8g2.drawLine(33 + 3, 8, 33 + 5, 2);
    _u8g2.drawLine(33 + 7, 8, 33 + 5, 2);
    _u8g2.drawLine(33 + 3, 6, 33 + 7, 6);
  }

  if (flags.hyp) {
    _u8g2.drawLine(44 + 3, 2, 44 + 3, 8);
    _u8g2.drawLine(44 + 7, 2, 44 + 7, 8);
    _u8g2.drawLine(44 + 3, 5, 44 + 7, 5);
  }
}

void _draw(disp_data_t *disp_data) {
  _u8g2.clearBuffer();
  _draw_flags(disp_data->flags);
  _draw_lines(disp_data->lines);
  _draw_menu(disp_data->menu_labels);
  _u8g2.sendBuffer();
}

void fc_dp_update(disp_data_t *disp_data) {
  mutex_enter_blocking(&disp_mutex);
  memcpy(&disp_data_pend_buf, disp_data, sizeof(disp_data_t));
  disp_update_pend = true;
  mutex_exit(&disp_mutex);
}

void fc_dp_draw(void) {
  mutex_enter_blocking(&disp_mutex);
  bool redraw = false;
  if (disp_update_pend) {
    memcpy(&disp_data_draw_buf, &disp_data_pend_buf, sizeof(disp_data_t));
    redraw = true;
    disp_update_pend = false;
  }
  mutex_exit(&disp_mutex);

  if (!redraw) return;

  _draw(&disp_data_draw_buf);
}