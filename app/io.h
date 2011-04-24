#ifndef _IO_H
#define _IO_H

#include "list.h"

#define MAX_STR_LENGTH 1024

list_t *io_read();
int io_write(list_t *nodes, list_t *splines);
int io_gnuplot(list_t *nodes, list_t *splines);

#define io_log(msg_type, ...)\
  io_log_impl(__FILE__, __LINE__, msg_type, __VA_ARGS__)

#define io_info(...)\
  io_log("info", __VA_ARGS__)

#define io_error(...)\
  io_log("error", __VA_ARGS__)

#define io_debug(...)\
  io_log("debug", __VA_ARGS__)

void io_log_impl(const char *file, const int line, const char *type, const char *msg_format, ...);

#endif

