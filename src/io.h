#ifndef _IO_H
#define _IO_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define MAX_STR_LENGTH 1024

list_t *io_read();
int io_write(list_t *nodes, list_t *splines);
int io_gnuplot(list_t *nodes, list_t *splines);

char *_msg;

#define io_msg(_msg_type, _msg_bare)\
  _msg = malloc(sizeof(*_msg) * (strlen(_msg_bare)+MAX_STR_LENGTH+1));\
  sprintf(_msg, "%s:%d:%s(): %s", __FILE__, __LINE__, __func__, _msg_bare);\
  io_bare_log(_msg_type, _msg);\
  free(_msg);

#define io_log(_msg_bare)\
  io_msg("log", _msg_bare);

#define io_error(_msg_bare)\
  io_msg("error", _msg_bare);

void io_bare_log(const char *type, const char *msg);

#endif /* _IO_H */

