#include "fc_math.h"
#include <complex.h>
#include <math.h>

fc_scalar_t fc_math_add(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u + b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i + b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f + b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c + b.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_subtract(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u - b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i - b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f - b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c - b.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_negate(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = -a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = -a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = -a.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = -a.data.val_c; break;
  }
  return r;
}


fc_scalar_t fc_math_multiply(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u * b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i * b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f * b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c * b.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_divide(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u / b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i / b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f / b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c / b.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_inverse(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = 1 / a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = 1 / a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = 1 / a.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = 1 / a.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_modulo(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u % b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i % b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = fc_math_cvt(a, FC_SCALAR_TYPE_I).data.val_i % fc_math_cvt(b, FC_SCALAR_TYPE_I).data.val_i; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = fc_math_cvt(a, FC_SCALAR_TYPE_I).data.val_i % fc_math_cvt(b, FC_SCALAR_TYPE_I).data.val_i; break;
  }
  return r;
}


fc_scalar_t fc_math_square(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u * a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i * a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f * a.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c * a.data.val_c; break;
  }
  return r;
}

fc_scalar_t fc_math_squareroot(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = sqrt(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = sqrt(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = sqrt(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = csqrt(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_exp(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = exp(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = exp(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = exp(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cexp(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_exp2(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = exp2(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = exp2(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = exp2(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cpow(2, a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_exp10(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = pow(10, a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = pow(10, a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = pow(10, a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cpow(10, a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_ln(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = log(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = log(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = log(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = clog(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_log2(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = log2(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = log2(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = log2(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = clog(a.data.val_c) / log(2); break;
  }
  return r;
}

fc_scalar_t fc_math_log10(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = log10(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = log10(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = log10(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = clog(a.data.val_c) / log(10); break;
  }
  return r;
}

fc_scalar_t fc_math_log(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = log(a.data.val_u) / log(b.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = log(a.data.val_i) / log(b.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = log(a.data.val_f) / log(b.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = clog(a.data.val_c) / clog(b.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_power(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = pow(a.data.val_u, b.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = pow(a.data.val_i, b.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = pow(a.data.val_f, b.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cpow(a.data.val_c, b.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_root(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, r.type);
  b = fc_math_cvt(b, r.type);
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = pow(a.data.val_u, 1.0 / b.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = pow(a.data.val_i, 1.0 / b.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = pow(a.data.val_f, 1 / b.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cpow(a.data.val_c, 1 / b.data.val_c); break;
  }
  return r;
}


fc_scalar_t fc_math_sin(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = sin(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = sin(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = sin(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = csin(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_cos(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = cos(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = cos(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = cos(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = ccos(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_tan(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = tan(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = tan(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = tan(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = ctan(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_asin(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = asin(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = asin(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = asin(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = casin(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_acos(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = acos(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = acos(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = acos(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cacos(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_atan(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = atan(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = atan(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = atan(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = catan(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_sinh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = sinh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = sinh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = sinh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = csinh(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_cosh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = cosh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = cosh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = cosh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = ccosh(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_tanh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = tanh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = tanh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = tanh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = ctanh(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_asinh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = asinh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = asinh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = asinh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = casinh(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_acosh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = acosh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = acosh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = acosh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cacosh(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_atanh(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = atanh(a.data.val_u); break;
    case FC_SCALAR_TYPE_I: r.data.val_i = atanh(a.data.val_i); break;
    case FC_SCALAR_TYPE_F: r.data.val_f = atanh(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = catanh(a.data.val_c); break;
  }
  return r;
}


fc_scalar_t fc_math_not(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = ~fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_and(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u & fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_or(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u | fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_xor(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u ^ fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_nand(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = ~(fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u & fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u);
  return r;
}

fc_scalar_t fc_math_nor(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = ~(fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u | fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u);
  return r;
}

fc_scalar_t fc_math_xnor(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = ~(fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u ^ fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u);
  return r;
}

fc_scalar_t fc_math_sll(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u << fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_srl(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u >> fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_sra(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_I;
  r.data.val_i = fc_math_cvt(a, FC_SCALAR_TYPE_I).data.val_i >> fc_math_cvt(b, FC_SCALAR_TYPE_I).data.val_i;
  return r;
}

fc_scalar_t fc_math_lnot(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = !fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_land(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u && fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}

fc_scalar_t fc_math_lor(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_U).data.val_u || fc_math_cvt(b, FC_SCALAR_TYPE_U).data.val_u;
  return r;
}


fc_scalar_t fc_math_lt(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u < b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i < b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f < b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_F).data.val_f < fc_math_cvt(b, FC_SCALAR_TYPE_F).data.val_f; break;
  }
  return r;
}

fc_scalar_t fc_math_le(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u <= b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i <= b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f <= b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_F).data.val_f <= fc_math_cvt(b, FC_SCALAR_TYPE_F).data.val_f; break;
  }
  return r;
}

fc_scalar_t fc_math_eq(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u == b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i == b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f == b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = a.data.val_f == b.data.val_f; break;
  }
  return r;
}

fc_scalar_t fc_math_ne(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u != b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i != b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f != b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = a.data.val_f != b.data.val_f; break;
  }
  return r;
}

fc_scalar_t fc_math_ge(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u >= b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i >= b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f >= b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_F).data.val_f >= fc_math_cvt(b, FC_SCALAR_TYPE_F).data.val_f; break;
  }
  return r;
}

fc_scalar_t fc_math_gt(fc_scalar_t a, fc_scalar_t b) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  fc_scalar_type_t type = fc_scalar_cast_type(a.type, b.type);
  a = fc_math_cvt(a, type);
  b = fc_math_cvt(b, type);
  switch (type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u > b.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i > b.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f > b.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_u = fc_math_cvt(a, FC_SCALAR_TYPE_F).data.val_f > fc_math_cvt(b, FC_SCALAR_TYPE_F).data.val_f; break;
  }
  return r;
}


fc_scalar_t fc_math_abs(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i < 0 ? -a.data.val_i : a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = fabs(a.data.val_f); break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cabs(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_arg(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = 0; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = 0; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = 0; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = carg(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_conj(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = conj(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_real(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = creal(a.data.val_c); break;
  }
  return r;
}

fc_scalar_t fc_math_imag(fc_scalar_t a) {
  fc_scalar_t r;
  r.type = a.type;
  switch (r.type) {
    case FC_SCALAR_TYPE_U: r.data.val_u = 0; break;
    case FC_SCALAR_TYPE_I: r.data.val_i = 0; break;
    case FC_SCALAR_TYPE_F: r.data.val_f = 0; break;
    case FC_SCALAR_TYPE_C: r.data.val_c = cimag(a.data.val_c); break;
  }
  return r;
}


fc_scalar_t fc_math_cvt(fc_scalar_t a, fc_scalar_type_t type) {
  fc_scalar_t r;
  r.type = type;
  switch (type) {
    case FC_SCALAR_TYPE_U:
      switch (a.type) {
        case FC_SCALAR_TYPE_U: r.data.val_u = a.data.val_u; break;
        case FC_SCALAR_TYPE_I: r.data.val_u = a.data.val_i; break;
        case FC_SCALAR_TYPE_F: r.data.val_u = a.data.val_f; break;
        case FC_SCALAR_TYPE_C: r.data.val_u = creal(a.data.val_c); break;
      } break;
    case FC_SCALAR_TYPE_I:
      switch (a.type) {
        case FC_SCALAR_TYPE_U: r.data.val_i = a.data.val_u; break;
        case FC_SCALAR_TYPE_I: r.data.val_i = a.data.val_i; break;
        case FC_SCALAR_TYPE_F: r.data.val_i = a.data.val_f; break;
        case FC_SCALAR_TYPE_C: r.data.val_i = creal(a.data.val_c); break;
      } break;
    case FC_SCALAR_TYPE_F:
      switch (a.type) {
        case FC_SCALAR_TYPE_U: r.data.val_f = a.data.val_u; break;
        case FC_SCALAR_TYPE_I: r.data.val_f = a.data.val_i; break;
        case FC_SCALAR_TYPE_F: r.data.val_f = a.data.val_f; break;
        case FC_SCALAR_TYPE_C: r.data.val_f = creal(a.data.val_c); break;
      } break;
    case FC_SCALAR_TYPE_C:
      switch (a.type) {
        case FC_SCALAR_TYPE_U: r.data.val_c = a.data.val_u; break;
        case FC_SCALAR_TYPE_I: r.data.val_c = a.data.val_i; break;
        case FC_SCALAR_TYPE_F: r.data.val_c = a.data.val_f; break;
        case FC_SCALAR_TYPE_C: r.data.val_c = a.data.val_c; break;
      } break;
  }
  return r;
}
