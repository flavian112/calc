#include "display.h"

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

#define PIN_D_SCK  (18)
#define PIN_D_MOSI (19)
#define PIN_D_CS   (17)
#define PIN_D_CD   (20)
#define PIN_D_RST  (21)

static U8G2_UC1611_EA_DOGXL240_F_4W_SW_SPI u8g2(U8G2_R2, 
                                                PIN_D_SCK,
                                                PIN_D_MOSI, 
                                                PIN_D_CS, 
                                                PIN_D_CD, 
                                                PIN_D_RST);

static uint8_t disp_w;
static uint8_t disp_h;

void dp_init(void) {
    u8g2.begin();
    u8g2.clearDisplay();
    disp_w = u8g2.getDisplayWidth();
    disp_h = u8g2.getDisplayHeight();
}

void dp_clear_buf() {
  u8g2.clearBuffer();
}

void dp_send_buf() {
  u8g2.sendBuffer();
}


void dp_draw_menu(const char labels[5][6]) {
  uint8_t box_h = 11;
  uint8_t box_w = (disp_w / 5) - 2;
  uint8_t box_y = disp_h - box_h;
 
  u8g2.setFont(u8g2_font_profont15_mr);
  u8g2.setFontMode(true);
  for (int i = 0; i < 5; ++i) {
    uint8_t box_x = (i * (disp_w / 5)) + 1;
    
    u8g2.setDrawColor(1);
    u8g2.drawBox(box_x, box_y, box_w, box_h);
    u8g2.setDrawColor(0);
    u8g2.drawGlyph(box_x + 4, disp_h - 1, labels[i][0]);
    u8g2.drawGlyph(box_x + 12, disp_h - 1, labels[i][1]);
    u8g2.drawGlyph(box_x + 20, disp_h - 1, labels[i][2]);
    u8g2.drawGlyph(box_x + 28, disp_h - 1, labels[i][3]);
    u8g2.drawGlyph(box_x + 36, disp_h - 1, labels[i][4]);

  }
}

void dp_draw_text(const char *text, uint8_t row) {
  u8g2.setFont(u8g2_font_profont29_mr);
  u8g2.setDrawColor(1);
  u8g2.drawStr(0, disp_h - 15 - (row * 23), text);
}

void dp_draw_flags(bool sl, bool sr, bool alt, bool alph, bool hyp, bool nav) {
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, disp_w, 11);
  u8g2.setDrawColor(0);

  if (sl) {
    u8g2.drawLine(2, 6, 8, 6);
    u8g2.drawLine(8, 6, 8, 2);
    u8g2.drawLine(2, 6, 5, 4);
    u8g2.drawLine(2, 6, 5, 8);
  }

  if (sr) {
    u8g2.drawLine(11 + 8, 6, 11 + 2, 6);
    u8g2.drawLine(11 + 2, 6, 11 + 2, 2);
    u8g2.drawLine(11 + 8, 6, 11 + 5, 4);
    u8g2.drawLine(11 + 8, 6, 11 + 5, 8);
  }

  if (alt) {
    u8g2.drawLine(22 + 2, 3, 22 + 3, 3);
    u8g2.drawLine(22 + 6, 3, 22 + 8, 3);
    u8g2.drawLine(22 + 3, 3, 22 + 6, 7);
    u8g2.drawLine(22 + 6, 7, 22 + 8, 7);
  }

  if (alph) {
    u8g2.drawLine(33 + 2, 8, 33 + 4, 8);
    u8g2.drawLine(33 + 6, 8, 33 + 8, 8);
    u8g2.drawLine(33 + 3, 8, 33 + 5, 2);
    u8g2.drawLine(33 + 7, 8, 33 + 5, 2);
    u8g2.drawLine(33 + 3, 6, 33 + 7, 6);
  }


}