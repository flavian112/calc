#ifndef FC_LOG_H
#define FC_LOG_H



#ifdef __cplusplus
extern "C" {
#endif

void fc_log_init(void);
int fc_log(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif