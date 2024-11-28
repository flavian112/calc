#ifndef CALC_H
#define CALC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <complex.h>

#define STACK_SIZE 8
#define REG_SIZE 24

union number {
    uint8_t data[16];
    double _Complex cdval;
} typedef number_t;

number_t stack_pop(void);
void stack_push(number_t number);
number_t stack_get(size_t index);
void stack_set(size_t index, number_t number);
void stack_roll_down(void);
void stack_roll_up(void);
void stack_swap(void);

/*
 registers
 */

void reg_sto(size_t index);
void reg_rcl(size_t index);

/*
 operations
*/

// basic arithmetic
void op_add(void);
void op_sub(void);
void op_neg(void);
void op_mul(void);
void op_div(void);
void op_inv(void);


void op_sq(void);
void op_exp(void);
void op_pow(void);
void op_sqrt(void);
void op_root(void);
void op_ln(void);
void op_log(void);

// other
void op_abs(void);
void op_arg(void);
void op_real(void);
void op_imag(void);

// trigonometry
void op_sin(void);
void op_cos(void);
void op_tan(void);
void op_asin(void);
void op_acos(void);
void op_atan(void);
void op_sinh(void);
void op_cosh(void);
void op_tanh(void);
void op_asinh(void);
void op_acosh(void);
void op_atanh(void);

#ifdef __cplusplus
}
#endif

#endif
