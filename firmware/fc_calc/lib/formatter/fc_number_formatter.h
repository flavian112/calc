#ifndef FC_NUMBER_FORMATTER_H
#define FC_NUMBER_FORMATTER_H

#include "fc_math.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum fc_number_format_t {
  FC_NUMBER_FORMAT_SCI,
  FC_NUMBER_FORMAT_ENG,
  FC_NUMBER_FORMAT_ALL
} typedef fc_number_format_t;

struct fc_number_formatter_config_t {
  bool sep;
  fc_base_t base;
  fc_number_format_t format;
  uint8_t sig;
  uint8_t lim;
} typedef fc_number_formatter_config_t;

void fc_format(fc_number_formatter_config_t config, fc_scalar_t number, char *buf, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif