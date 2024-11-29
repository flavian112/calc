#include "calc.h"

#include <math.h>

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

void ca_op_pow2_x(void) {
  number_t x = ca_stack_pop_x();
  number_t r;
  r.cdval = cpow(2.0, x.cdval);
  ca_stack_push_x(r);
}

void ca_op_pow10_x(void) {
  number_t x = ca_stack_pop_x();
  number_t r;
  r.cdval = cpow(10.0, x.cdval);
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

void ca_op_log10_x(void) {
  number_t x = ca_stack_pop_x();
  number_t r;
  r.cdval = clog(x.cdval) / clog(10.0);
  ca_stack_push_x(r);
}

void ca_op_log2_x(void) {
  number_t x = ca_stack_pop_x();
  number_t r;
  r.cdval = clog(x.cdval) / clog(2.0);
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

static const double lanczos_coeffs[] = {
    676.5203681218851, -1259.1392167224028, 771.32342877765313,
    -176.61502916214059, 12.507343278686905, -0.13857109526572012,
    9.9843695780195716e-6, 1.5056327351493116e-7
};

#define LANCZOS_G 7.0

double complex gamma_cmplx(double complex z) {
    if (creal(z) < 0.5) {
        return M_PI / (csin(M_PI * z) * gamma_cmplx(1.0 - z));
    }

    z -= 1.0;
    double complex x = 0.99999999999980993;

    for (int i = 0; i < sizeof(lanczos_coeffs) / sizeof(lanczos_coeffs[0]); i++) {
        x += lanczos_coeffs[i] / (z + (i + 1));
    }

    double complex t = z + LANCZOS_G + 0.5;
    return sqrt(2.0 * M_PI) * cpow(t, z + 0.5) * cexp(-t) * x;
}

void ca_op_fact_x(void) {
  number_t x = ca_stack_pop_x();
  number_t r;
  r.cdval = gamma_cmplx(x.cdval + 1.0);
  ca_stack_push_x(r);
}
