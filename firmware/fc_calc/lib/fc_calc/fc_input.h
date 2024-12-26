#ifndef FC_INPUT_H
#define FC_INPUT_H

#include "fc_scalar.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FC_INPUT_BUF_SIZE (64)

typedef struct {
  char real[FC_INPUT_BUF_SIZE];
  char imag[FC_INPUT_BUF_SIZE];
  char tmp[FC_INPUT_BUF_SIZE];
  bool has_imag;
} fc_input_state_t;

void fc_input_init(fc_input_state_t *state);
void fc_input_clear(fc_input_state_t *state);
void fc_input_delete(fc_input_state_t *state);
void fc_input_add_digit(fc_input_state_t *state, unsigned char digit);
void fc_input_toggle_sign(fc_input_state_t *state);
void fc_input_add_decimal(fc_input_state_t *state);
void fc_input_add_exponent(fc_input_state_t *state);
void fc_input_add_imaginary(fc_input_state_t *state);
fc_scalar_t fc_input_get(fc_input_state_t *state);
void fc_input_set(fc_input_state_t *state, fc_scalar_t scalar);
void fc_input_get_str(fc_input_state_t *state, char *buf, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif
