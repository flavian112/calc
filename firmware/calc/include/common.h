#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum cl_base {
    CL_BASE_BIN,
    CL_BASE_OCT,
    CL_BASE_DEC,
    CL_BASE_HEX
} typedef cl_base_t;

union number {
    uint8_t data[16];
    double _Complex cdval;
} typedef number_t;

#ifdef __cplusplus
}
#endif

#endif