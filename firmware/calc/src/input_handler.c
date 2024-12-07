#include "input_handler.h"

#include <strings.h>
#include <stdbool.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include "number_formatter.h"

bool ih_valid_digit(fc_base_t base, uint8_t digit) {
  return digit < base;
}

ih_state_t ih_init(void) {
  ih_state_t state;
  memset(&state, 0, sizeof(ih_state_t));
  state.base = FC_BASE_DEC;
  state.entry_state = IH_ENTRY_STATE_BASE_REAL;
  return state;
}

void ih_set_base(ih_state_t *state, fc_base_t base) {
  state->base = base;
}

void ih_clear(ih_state_t *state) {
  fc_base_t base = state->base;
  memset(state, 0, sizeof(ih_state_t));
  state->base = base;
  state->entry_state = IH_ENTRY_STATE_BASE_REAL;
}

void ih_add_digit(ih_state_t *state, uint8_t digit) {
  if (!ih_valid_digit(state->base, digit)) return;

  uint8_t *number_buf;
  uint8_t *number_len;

  switch (state->entry_state) {
    case IH_ENTRY_STATE_BASE_REAL:
      number_buf = state->buf_base_real;
      number_len = &state->base_len_real;
      break;
    case IH_ENTRY_STATE_EXP_REAL:
      number_buf = state->buf_exp_real;
      number_len = &state->exp_len_real;
      break;
    case IH_ENTRY_STATE_BASE_CMPLX:
      number_buf = state->buf_base_cmplx;
      number_len = &state->base_len_cmplx;
      break;
    case IH_ENTRY_STATE_EXP_CMPLX:
      number_buf = state->buf_exp_cmplx;
      number_len = &state->exp_len_cmplx;
      break;
    default: return;
  }

  if (*number_len >= IH_BUF_LEN) return;

  number_buf[(*number_len)++] = digit;
}

void ih_add_decimal(ih_state_t *state) {
  uint8_t *number_buf;
  uint8_t *number_len;
  bool *decimal;
  uint8_t *decimal_pos;

  if (state->entry_state == IH_ENTRY_STATE_BASE_REAL) {
    number_buf = state->buf_base_real;
    number_len = &state->base_len_real;
    decimal = &state->base_decimal_real;
    decimal_pos = &state->base_decimal_pos_real;
  } else if (state->entry_state == IH_ENTRY_STATE_BASE_CMPLX) {
    number_buf = state->buf_base_cmplx;
    number_len = &state->base_len_cmplx;
    decimal = &state->base_decimal_cmplx;
    decimal_pos = &state->base_decimal_pos_cmplx;
  } else return;

  if (*decimal) return;

  *decimal = true;

  if (*number_len == 0) {
    ++(*number_len);
    number_buf[0] = 0;
    *decimal_pos = 0;
    return;
  }

  *decimal_pos = *number_len - 1;
}

void ih_add_exp(ih_state_t *state) {
  if (state->entry_state == IH_ENTRY_STATE_BASE_REAL) {
    if (!state->exp_real) {
      state->exp_real = true;
      state->entry_state = IH_ENTRY_STATE_EXP_REAL;
      return;
    }
  } else if (state->entry_state == IH_ENTRY_STATE_BASE_CMPLX) {
    if (!state->exp_cmplx) {
      state->exp_cmplx = true;
      state->entry_state = IH_ENTRY_STATE_EXP_CMPLX;
      return;
    }
  }
}

void ih_neg(ih_state_t *state) {
  switch (state->entry_state) {
    case IH_ENTRY_STATE_BASE_REAL:
      state->base_sign_real = !state->base_sign_real;
      break;
    case IH_ENTRY_STATE_EXP_REAL:
      state->exp_sign_real = !state->exp_sign_real;
      break;
    case IH_ENTRY_STATE_BASE_CMPLX:
      state->base_sign_cmplx = !state->base_sign_cmplx;
      break;
    case IH_ENTRY_STATE_EXP_CMPLX:
      state->exp_sign_cmplx = !state->exp_sign_cmplx;
      break;
    default: return;
  }
}

void ih_add_cmplx(ih_state_t *state) {
  if (!state->cmplx) {
    state->cmplx = true;
    state->entry_state = IH_ENTRY_STATE_BASE_CMPLX;
  }
}

char ih_char(uint8_t digit) {
  if (digit < 10) return '0' + digit;
  if (digit < 16) return 'a' + digit - 10;
  return '\0';
}

char* ih_str(ih_state_t *state) {
  uint8_t idx = 0;

  if (state->base_sign_real) state->output_buf[idx++] = '-';
  for (int i = 0; i < state->base_len_real; ++i) {
    state->output_buf[idx++] = ih_char(state->buf_base_real[i]);
    if (state->base_decimal_real && state->base_decimal_pos_real == i) state->output_buf[idx++] = '.';
  }
  if(!state->exp_real) {
    if (state->base_len_real == 0) state->output_buf[idx++] = '0'; 
    state->output_buf[idx] = '\0'; 
  return state->output_buf; }

  state->output_buf[idx++] = 'E';
  if (state->exp_sign_real) state->output_buf[idx++] = '-';
  for (int i = 0; i < state->exp_len_real; ++i) {
    state->output_buf[idx++] = ih_char(state->buf_exp_real[i]);
  }
  if(!state->cmplx) { state->output_buf[idx] = '\0'; return state->output_buf; }

  state->output_buf[idx++] = 'i';
  if (state->base_sign_cmplx) state->output_buf[idx++] = '-';
  for (int i = 0; i < state->base_len_cmplx; ++i) {
    state->output_buf[idx++] = ih_char(state->buf_base_cmplx[i]);
    if (state->base_decimal_cmplx && state->base_decimal_pos_cmplx == i) state->output_buf[idx++] = '.';
  }
  if(!state->exp_cmplx) { state->output_buf[idx] = '\0'; return state->output_buf; }

  state->output_buf[idx++] = 'E';
  if (state->exp_sign_cmplx) state->output_buf[idx++] = '-';
  for (int i = 0; i < state->exp_len_cmplx; ++i) {
    state->output_buf[idx++] = ih_char(state->buf_exp_cmplx[i]);
  }
  
  state->output_buf[idx] = '\0'; 
  return state->output_buf;
}

double ih_mantissa(uint8_t *buf, uint8_t len, bool decimal, uint8_t decimal_pos, uint8_t base) {
  double mantissa = 0.0;
  int i;

  if (decimal) {
    for (i = 0; i < decimal_pos + 1; ++i) {
      mantissa = mantissa * base + buf[i];
    }
    double factor = 1.0 / base;
    for (i = decimal_pos + 1; i < len; i++) {
      mantissa += buf[i] * factor;
      factor /= base;
    }
  } else {
    for (i = 0; i < len; i++) {
      mantissa = mantissa * base + buf[i];
    }
  }
  return mantissa;
}

int ih_exp(uint8_t *buf, uint8_t len, bool exp_sign, fc_base_t base) {
  int exponent = 0;
  int i;

  for (i = 0; i < len; i++) {
    exponent = exponent * base + buf[i];
  }

  if (exp_sign) exponent = -exponent;

  return exponent;
}

fc_scalar_t ih_get_number(ih_state_t *state) {
  double real_part = 0.0;
  double imag_part = 0.0;

  fc_scalar_t number;
  double complex cmplx_number = 0;
  number.val_c = cmplx_number;

  if (state->base_len_real > 0) {
    double mantissa_real = ih_mantissa(
      state->buf_base_real,
      state->base_len_real,
      state->base_decimal_real,
      state->base_decimal_pos_real,
      state->base
    );

    int exponent_real = 0;
    if (state->exp_real && state->exp_len_real > 0) {
      exponent_real = ih_exp(
        state->buf_exp_real,
        state->exp_len_real,
        state->exp_sign_real,
        state->base
      );
    }

    double value_real = mantissa_real * pow(state->base, exponent_real);
    if (state->base_sign_real) {
      value_real = -value_real;
    }
    real_part = value_real;
  }

    if (state->cmplx && state->base_len_cmplx > 0) {
      double mantissa_imag = ih_mantissa(
        state->buf_base_cmplx,
        state->base_len_cmplx,
        state->base_decimal_cmplx,
        state->base_decimal_pos_cmplx,
        state->base
      );

    int exponent_imag = 0;
    if (state->exp_cmplx && state->exp_len_cmplx > 0) {
      exponent_imag = ih_exp(
        state->buf_exp_cmplx,
        state->exp_len_cmplx,
        state->exp_sign_cmplx,
        state->base
      );
    }

    double value_imag = mantissa_imag * pow(state->base, exponent_imag);
    if (state->base_sign_cmplx) {
      value_imag = -value_imag;
    }
    imag_part = value_imag;
  }

  cmplx_number = real_part + imag_part * I;
  number.val_c = cmplx_number;
  return number;
}

void ih_del(ih_state_t *state) {
  if (state->entry_state == IH_ENTRY_STATE_BASE_REAL) {
    if (state->base_len_real == 0) {
      if (state->base_sign_real) {
        state->base_sign_real = false;
      }
    } else if (state->base_decimal_real && state->base_len_real == state->base_decimal_pos_real + 1) {
      state->base_decimal_real = false;
    } else {
      state->buf_base_real[--state->base_len_real] = '\0';
    }
    return;
  }
  if (state->entry_state == IH_ENTRY_STATE_EXP_REAL) {
    if (state->exp_len_real == 0) {
      if (state->exp_sign_real) {
        state->exp_sign_real = false;
      } else {
        state->exp_real = false;
        state->entry_state = IH_ENTRY_STATE_BASE_REAL;
      }
    } else {
      state->buf_exp_real[--state->exp_len_real] = '\0';
    }
    return;
  }
  if (state->entry_state == IH_ENTRY_STATE_BASE_CMPLX) {
    if (state->base_len_real == 0) {
      if (state->base_sign_real) {
        state->base_sign_real = false;
      }
    } else if (state->base_decimal_real && state->base_len_real == state->base_decimal_pos_real + 1) {
      state->base_decimal_real = false;
    } else {
      state->buf_base_real[--state->base_len_real] = '\0';
    }
    return;
  }
  if (state->entry_state == IH_ENTRY_STATE_EXP_REAL) {
    if (state->exp_len_real == 0) {
      if (state->exp_sign_real) {
        state->exp_sign_real = false;
      } else {
        state->exp_real = false;
        state->entry_state = IH_ENTRY_STATE_BASE_REAL;
      }
    } else {
      state->buf_exp_real[--state->exp_len_real] = '\0';
    }
    return;
  }
}

void ih_set(ih_state_t *state, fc_scalar_t number, nf_number_format_t format, int prec) {
  char buf[100];
  nf_format_complex(format, number, prec, buf);
  char* cmplx_i = strchr(buf, 'i'); 
} 