#ifndef FC_DISPLAY_H
#define FC_DISPLAY_H

#include "fc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void fc_dp_init(void);
void fc_dp_update(fc_disp_data_t *disp_data);
void fc_dp_draw(void);


#ifdef __cplusplus
}
#endif

#endif