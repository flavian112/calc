#include <Arduino.h>
#include "fc_log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define _LOG_BUF_SIZE (256)

static char _log_buf[_LOG_BUF_SIZE];

void fc_log_init(void) {
  Serial.begin(115200);
}


int fc_log(const char *format, ...) {
  va_list args;
  int ret;

  va_start(args, format);
  ret = vsnprintf(_log_buf, _LOG_BUF_SIZE, format, args);
  Serial.printf("%s", _log_buf);
  va_end(args);

  return ret;
}