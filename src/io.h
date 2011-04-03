#ifndef _IO_H
#define _IO_H

#include "list.h"

#define MAX_STR_LENGTH 1024

list_t *io_read(const char *source_file);
int io_write(const char* output_file, list_t *nodes, list_t *splines);
int io_gnuplot(const char* gnuplot_file, list_t *nodes, list_t *splines);

#endif /* _IO_H */

