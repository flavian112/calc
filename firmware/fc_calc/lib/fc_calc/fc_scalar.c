#include "fc_scalar.h"

fc_scalar_t fc_scalar_u(fc_scalar_u_t val) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_U;
  r.data.val_u = val;
  return r;
}

fc_scalar_t fc_scalar_i(fc_scalar_i_t val) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_I;
  r.data.val_i = val;
  return r;
}

fc_scalar_t fc_scalar_f(fc_scalar_f_t val) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_F;
  r.data.val_f = val;
  return r;
}

fc_scalar_t fc_scalar_c(fc_scalar_c_t val) {
  fc_scalar_t r;
  r.type = FC_SCALAR_TYPE_C;
  r.data.val_c = val;
  return r;
}

fc_scalar_type_t fc_scalar_cast_type(fc_scalar_type_t a, fc_scalar_type_t b) {
  return a > b ? a : b;
}
