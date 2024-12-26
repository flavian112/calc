#include "fc_input.h"
#include <string.h>
#include <stdio.h>
#include "fc_format.h"

static void _char_remove(char *str, size_t index) {
  size_t len = strnlen(str, FC_INPUT_BUF_SIZE);
  if (index >= len) return;
  memmove(&str[index], &str[index + 1], len - index);
}

static void _char_insert(char *str, char c, size_t index) {
  size_t len = strnlen(str, FC_INPUT_BUF_SIZE);
  if (len + 1 >= FC_INPUT_BUF_SIZE) return;
  if (index > len) return;
  memmove(&str[index + 1], &str[index], len - index + 1);
  str[index] = c;
}

static bool _has_exp(char *buf) {
  return strchr(buf, 'e');
}

static bool _has_decimal(char *buf) {
  return strchr(buf, '.');
}

static bool _is_neg(char *buf) {
  return *buf == '-';
}

static bool _is_exp_neg(char *buf) {
  char *chr_e = strchr(buf, 'e');
  if (!chr_e) return false;
  return *(chr_e + 1) == '-';
}

static void _add_decimal(char *buf) {
  if (_has_decimal(buf)) return;
  if (_has_exp(buf)) return;
  size_t len = strnlen(buf, FC_INPUT_BUF_SIZE);
  if (len + 1 >= FC_INPUT_BUF_SIZE) return;
  buf[len] = '.';
  buf[len + 1] = '\0';
}

static void _add_exp(char *buf) {
  size_t len = strnlen(buf, FC_INPUT_BUF_SIZE);
  if (len + 1 >= FC_INPUT_BUF_SIZE) return;
  if (_has_exp(buf)) return;
  buf[len] = 'e';
  buf[len + 1] = '\0';
}

static void _toggle_sign(char *buf) {
  if (_has_exp(buf)) {
    size_t idx = strchr(buf, 'e') - buf + 1;
    if (_is_exp_neg(buf)) {
      _char_remove(buf, idx);
    } else {
      _char_insert(buf, '-', idx);
    }
  } else {
    if (_is_neg(buf)) {
      _char_remove(buf, 0);
    } else {
      _char_insert(buf, '-', 0);
    }
  }
}


void fc_input_init(fc_input_state_t *state) {
  memset(state, 0, sizeof(fc_input_state_t));
}

void fc_input_clear(fc_input_state_t *state) {
  state->real[0] = '\0';
  state->imag[0] = '\0';
  state->has_imag = false;
}

void fc_input_delete(fc_input_state_t *state) {
  if (state->has_imag) {
    size_t len = strnlen(state->imag, FC_INPUT_BUF_SIZE);
    if (!len) { state->has_imag = false; return; }
    state->imag[len - 1] = '\0';
  } else {
    size_t len = strnlen(state->real, FC_INPUT_BUF_SIZE);
    if (!len) return;
    state->real[len - 1] = '\0';
  }
}

void fc_input_add_digit(fc_input_state_t *state, unsigned char digit) {
  if (state->has_imag) {
    size_t len = strnlen(state->imag, FC_INPUT_BUF_SIZE);
    if (len + 1 >= FC_INPUT_BUF_SIZE) return;
    state->imag[len] = digit < 10 ? '0' + digit : 'A' + digit;
    state->imag[len + 1] = '\0';
  } else {
    size_t len = strnlen(state->real, FC_INPUT_BUF_SIZE);
    if (len + 1 >= FC_INPUT_BUF_SIZE) return;
    state->real[len] = digit < 10 ? '0' + digit : 'A' + digit;
    state->real[len + 1] = '\0';
  }
}

void fc_input_toggle_sign(fc_input_state_t *state) {
  if (state->has_imag) {
    _toggle_sign(state->imag);
  } else {
    _toggle_sign(state->real);
  }
  
}

void fc_input_add_decimal(fc_input_state_t *state) {
  if (state->has_imag) {
    _add_decimal(state->imag);
  } else {
    _add_decimal(state->real);
  }
}

void fc_input_add_exponent(fc_input_state_t *state) {
  if (state->has_imag) {
    _add_exp(state->imag);
  } else {
    _add_exp(state->real);
  }
}

void fc_input_add_imaginary(fc_input_state_t *state) {
  if (state->has_imag) return;
  state->has_imag = true;
  state->imag[0] = '\0';
}

fc_scalar_t fc_input_get(fc_input_state_t *state) {
  fc_scalar_f_t real, imag;
  real = imag = 0;
  if (sscanf(state->real, "%lg", &real) != 1) real = 0;
  if (state->has_imag) {
    if (sscanf(state->imag, "%lg", &imag) != 1) imag = 0;
    return fc_scalar_c(real + I * imag);
  } else {
    return fc_scalar_f(real);
  }
}

void fc_input_set(fc_input_state_t *state, fc_scalar_t scalar) {
  fc_format(scalar, FC_BASE_DEC, state->tmp, FC_INPUT_BUF_SIZE);
  char *chr_i = strchr(state->tmp, 'i');
  char *chr_c = strchr(state->tmp, ',');
  
  if (chr_c) {
    strncpy(state->imag, chr_c + 1, chr_i - chr_c - 1);
    strncpy(state->real, state->tmp, chr_c - state->tmp);
    state->has_imag = true;
  } else if (chr_i) {
    strncpy(state->imag, state->tmp, chr_i - state->tmp);
    state->has_imag = true;
    state->real[0] = '\0';
  } else {
    strncpy(state->real, state->tmp, FC_INPUT_BUF_SIZE);
    state->has_imag = false;
    state->imag[0] = '\0';
  }
}

void fc_input_get_str(fc_input_state_t *state, char *buf, size_t buflen) {
  size_t len_real = strnlen(state->real, FC_INPUT_BUF_SIZE);
  size_t len_imag = strnlen(state->imag, FC_INPUT_BUF_SIZE);
  if (state->has_imag) {
    if (len_real) {
      snprintf(buf, buflen, "%s,%si", state->real, state->imag);
    } else {
      snprintf(buf, buflen, "%si", len_imag ? state->imag : "0");
    }
  } else {
    snprintf(buf, buflen, "%s", len_real ? state->real : "0");
  }
}
