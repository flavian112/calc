#ifndef FC_FORMAT_H
#define FC_FORMAT_H

#include "fc_scalar.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void fc_format(fc_scalar_t scalar, fc_base_t base, char *buf, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif
