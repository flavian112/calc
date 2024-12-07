#ifndef FC_COMMON_H
#define FC_COMMON_H

#include <stdbool.h>

#define MENU_LABEL_SIZE (6)
#define MENU_LABEL_NUM (5)
#define LINE_BUF_SIZE (128)

#ifdef __cplusplus
extern "C" {
#endif

typedef char menu_label_t[MENU_LABEL_SIZE];
typedef menu_label_t menu_labels_t[MENU_LABEL_NUM];
typedef char line_buf_t[LINE_BUF_SIZE];

struct flags_t {
  bool mod_shift_r;
  bool mod_shift_l;
  bool mod_alt;
  bool hyp;
  bool alpha;
  bool nav;
} typedef flags_t;

struct disp_data_t {
  flags_t flags;
  menu_labels_t menu_labels;
  line_buf_t lines[4];
} typedef disp_data_t;



#ifdef __cplusplus
}
#endif

#endif