#include "calc.h"

/* stack */

static number_t stack[STACK_SIZE] = {0};
static size_t stack_top = 0;

/* regs */

static number_t regs[REG_SIZE] = {0};

/* stack manipulation */

number_t stack_pop(void) {
    number_t number = stack[stack_top];
    stack[stack_top] = stack[(stack_top + STACK_SIZE - 1) % STACK_SIZE];
    stack_top = (stack_top + 1) % STACK_SIZE;
    return number;
}

void stack_push(number_t number) {
    stack_top = (stack_top + STACK_SIZE - 1) % STACK_SIZE;
    stack[stack_top] = number;
}

number_t stack_get(size_t index) {
    number_t number = stack[(stack_top + index) % STACK_SIZE];
    return number;
}

void stack_set(size_t index, number_t number) {
    stack[(stack_top + index) % STACK_SIZE] = number;
}

void stack_roll_down(void) {
    stack_top = (stack_top + 1) % STACK_SIZE;
}

void stack_roll_up(void) {
    stack_top = (stack_top + STACK_SIZE - 1) % STACK_SIZE;
}

void stack_swap(void) {
    number_t tmp_number;
    tmp_number = stack_get(0);
    stack_set(0, stack_get(1));
    stack_set(1, tmp_number);
}

/* register manipulation */

void reg_sto(size_t index) {
    number_t number = stack_get(0);
    regs[index % REG_SIZE] = number;
}

void reg_rcl(size_t index) {
    stack_push(regs[index % REG_SIZE]);
}

/* ops */

void op_add(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = y.cdval + x.cdval;
    stack_push(r);
}

void op_sub(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = y.cdval - x.cdval;
    stack_push(r);
}

void op_neg(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = -x.cdval;
    stack_push(r);
}

void op_mul(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = y.cdval * x.cdval;
    stack_push(r);
}

void op_div(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = y.cdval / x.cdval;
    stack_push(r);
}

void op_inv(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = 1.0 / x.cdval;
    stack_push(r);
}

void op_sq(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = 2.0 * x.cdval;
    stack_push(r);
}

void op_exp(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = cexp(x.cdval);
    stack_push(r);
}

void op_pow(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = cpow(y.cdval, x.cdval);
    stack_push(r);
}

void op_sqrt(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = csqrt(x.cdval);
    stack_push(r);
}

void op_root(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = cpow(y.cdval, 1.0 / x.cdval);
    stack_push(r);
}

void op_ln(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = clog(x.cdval);
    stack_push(r);
}

void op_log(void) {
    number_t x = stack_pop();
    number_t y = stack_pop();
    number_t r;
    r.cdval = clog(y.cdval) / clog(x.cdval);
    stack_push(r);
}

void op_abs(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = cabs(x.cdval);
    stack_push(r);
}

void op_arg(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = carg(x.cdval);
    stack_push(r);
}

void op_real(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = creal(x.cdval);
    stack_push(r);
}

void op_imag(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = cimag(x.cdval);
    stack_push(r);
}

void op_sin(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = csin(x.cdval);
    stack_push(r);
}

void op_cos(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = ccos(x.cdval);
    stack_push(r);
}

void op_tan(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = ctan(x.cdval);
    stack_push(r);
}

void op_asin(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = casin(x.cdval);
    stack_push(r);
}

void op_acos(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = cacos(x.cdval);
    stack_push(r);
}

void op_atan(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = catan(x.cdval);
    stack_push(r);
}

void op_sinh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = csinh(x.cdval);
    stack_push(r);
}

void op_cosh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = ccosh(x.cdval);
    stack_push(r);
}

void op_tanh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = casin(x.cdval);
    stack_push(r);
}

void op_asinh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = casinh(x.cdval);
    stack_push(r);
}

void op_acosh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = cacosh(x.cdval);
    stack_push(r);
}

void op_atanh(void) {
    number_t x = stack_pop();
    number_t r;
    r.cdval = catanh(x.cdval);
    stack_push(r);
}
