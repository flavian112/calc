#ifndef FC_COMMON_H
#define FC_COMMON_H

#include <stdbool.h>

#define FC_MENU_LABEL_SIZE (6)
#define FC_MENU_LABEL_NUM (5)
#define FC_LINE_BUF_SIZE (128)

#ifdef __cplusplus
extern "C" {
#endif

typedef char fc_menu_label_t[FC_MENU_LABEL_SIZE];
typedef fc_menu_label_t fc_menu_labels_t[FC_MENU_LABEL_NUM];
typedef char fc_line_buf_t[FC_LINE_BUF_SIZE];

typedef struct {
  bool mod_shift_r;
  bool mod_shift_l;
  bool mod_alt;
  bool hyp;
  bool alpha;
  bool nav;
} fc_flags_t;

typedef enum {
  FC_DISP_STATE_NORMAL,
  FC_DISP_STATE_ENTRY,
  FC_DISP_STATE_RESULT
} fc_disp_state_t;

typedef struct {
  fc_flags_t flags;
  fc_menu_labels_t menu_labels;
  fc_line_buf_t lines[4];
  fc_disp_state_t disp_state;
} fc_disp_data_t;

#ifdef __cplusplus
}
#endif

#endif