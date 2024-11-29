#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "common.h"

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IH_BUF_LEN (8)
#define IH_OUTPUT_BUF_LEN (64)

enum ih_entry_state {
  IH_ENTRY_STATE_BASE_REAL,
  IH_ENTRY_STATE_EXP_REAL,
  IH_ENTRY_STATE_BASE_CMPLX,
  IH_ENTRY_STATE_EXP_CMPLX
} typedef ih_entry_state_t;

struct ih_state {
  cl_base_t base;

  uint8_t buf_base_real[IH_BUF_LEN];
  uint8_t base_len_real;
  bool base_sign_real;
  bool base_decimal_real;
  uint8_t base_decimal_pos_real;

  uint8_t buf_exp_real[IH_BUF_LEN];
  uint8_t exp_len_real;
  bool exp_sign_real;
  bool exp_real;

  uint8_t buf_base_cmplx[IH_BUF_LEN];
  uint8_t base_len_cmplx;
  bool base_sign_cmplx;
  bool base_decimal_cmplx;
  uint8_t base_decimal_pos_cmplx;

  uint8_t buf_exp_cmplx[IH_BUF_LEN];
  uint8_t exp_len_cmplx;
  bool exp_sign_cmplx;
  bool exp_cmplx;

  bool cmplx;

  ih_entry_state_t entry_state;

  char output_buf[IH_OUTPUT_BUF_LEN];

} typedef ih_state_t;


ih_state_t ih_init(void);
void ih_set_base(ih_state_t *state, cl_base_t base);
void ih_clear(ih_state_t *state);
void ih_add_digit(ih_state_t *state, uint8_t digit);
void ih_add_decimal(ih_state_t *state);
void ih_add_exp(ih_state_t *state);
void ih_neg(ih_state_t *state);
void ih_add_cmplx(ih_state_t *state);
char* ih_str(ih_state_t *state);
number_t ih_get_number(ih_state_t *state);
void ih_del(ih_state_t *state);

#ifdef __cplusplus
}
#endif

#endif