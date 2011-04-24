#ifndef _LOGGER_H
#define _LOGGER_H

#define log_log(msg_type, ...)\
  log_impl(__FILE__, __LINE__, msg_type, __VA_ARGS__)

#define log_info(...)\
  log_log("info", __VA_ARGS__)

#define log_error(...)\
  log_log("error", __VA_ARGS__)

#define log_debug(...)\
  log_log("debug", __VA_ARGS__)

void log_impl(const char *file, const int line, const char *type, const char *msg_format, ...);

#endif

