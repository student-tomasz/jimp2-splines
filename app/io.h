#ifndef _IO_H
#define _IO_H

#include "list.h"

list_t *io_read();
int io_write(list_t *nodes, list_t *splines);
int io_gnuplot(list_t *nodes, list_t *splines);

#endif

