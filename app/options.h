#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "flag.h"

struct {
  const char *in_filename;
  const char *out_filename;
  int gnuplot;
  int force;
  int quiet;
} *options;

void options_init();
int options_set(const flag_t *flag);
int options_set_with_arg(const flag_t *flag, const char *arg);

#endif

