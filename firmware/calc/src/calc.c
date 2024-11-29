#include "calc.h"

/* stack */

static number_t stack[STACK_SIZE] = {0};
static size_t stack_top = 0;

/* regs */

static number_t regs[REG_SIZE] = {0};

/* stack manipulation */

number_t ca_stack_pop_x(void) {
    number_t number = stack[stack_top];
    stack[stack_top] = stack[(stack_top + STACK_SIZE - 1) % STACK_SIZE];
    stack_top = (stack_top + 1) % STACK_SIZE;
    return number;
}

void ca_stack_push_x(number_t number) {
    stack_top = (stack_top + STACK_SIZE - 1) % STACK_SIZE;
    stack[stack_top] = number;
}

number_t ca_stack_get(size_t index) {
    number_t number = stack[(stack_top + index) % STACK_SIZE];
    return number;
}

void ca_stack_set(size_t index, number_t number) {
    stack[(stack_top + index) % STACK_SIZE] = number;
}

void ca_stack_roll_down(void) {
    stack_top = (stack_top + 1) % STACK_SIZE;
}

void ca_stack_roll_up(void) {
    stack_top = (stack_top + STACK_SIZE - 1) % STACK_SIZE;
}

void ca_stack_swap_yx(void) {
    number_t tmp_number;
    tmp_number = ca_stack_get(0);
    ca_stack_set(0, ca_stack_get(1));
    ca_stack_set(1, tmp_number);
}

/* register manipulation */

void ca_reg_sto_x(size_t index) {
    number_t number = ca_stack_get(0);
    regs[index % REG_SIZE] = number;
}

void ca_reg_rcl_x(size_t index) {
    ca_stack_push_x(regs[index % REG_SIZE]);
}

/* ops */

void ca_op_add_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = y.cdval + x.cdval;
    ca_stack_push_x(r);
}

void ca_op_sub_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = y.cdval - x.cdval;
    ca_stack_push_x(r);
}

void ca_op_neg_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = -x.cdval;
    ca_stack_push_x(r);
}

void ca_op_mul_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = y.cdval * x.cdval;
    ca_stack_push_x(r);
}

void ca_op_div_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = y.cdval / x.cdval;
    ca_stack_push_x(r);
}

void ca_op_inv_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = 1.0 / x.cdval;
    ca_stack_push_x(r);
}

void ca_op_sq_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = 2.0 * x.cdval;
    ca_stack_push_x(r);
}

void ca_op_expe_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = cexp(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_pow_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = cpow(y.cdval, x.cdval);
    ca_stack_push_x(r);
}

void ca_op_sqrt_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = csqrt(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_root_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = cpow(y.cdval, 1.0 / x.cdval);
    ca_stack_push_x(r);
}

void ca_op_ln(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = clog(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_log_yx(void) {
    number_t x = ca_stack_pop_x();
    number_t y = ca_stack_pop_x();
    number_t r;
    r.cdval = clog(y.cdval) / clog(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_abs_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = cabs(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_arg_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = carg(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_real_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = creal(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_imag_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = cimag(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_sin_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = csin(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_cos_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = ccos(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_tan_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = ctan(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_asin_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = casin(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_acos_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = cacos(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_atan_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = catan(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_sinh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = csinh(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_cosh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = ccosh(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_tanh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = casin(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_asinh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = casinh(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_acosh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = cacosh(x.cdval);
    ca_stack_push_x(r);
}

void ca_op_atanh_x(void) {
    number_t x = ca_stack_pop_x();
    number_t r;
    r.cdval = catanh(x.cdval);
    ca_stack_push_x(r);
}
