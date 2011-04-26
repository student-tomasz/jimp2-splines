#include <stdlib.h>
#include "options.h"
#include "flag.h"

void options_init()
{
  options = malloc(sizeof(*options));
  options->in_filename = NULL;
  options->out_filename = NULL;
  options->gnuplot = 0;
  options->force = 0;
  options->quiet = 0;
}

int options_set(const flag_t *flag)
{
  char f = flag->flag;

  if (f == 'g')
      options->gnuplot = 1;
  else if (f == 'f')
      options->force = 1;
  else if (f == 'q')
      options->quiet = 1;
  else
      return 0;

  return 1;
}

int options_set_with_arg(const flag_t *flag, const char *arg)
{
  if (flag->flag == 'o')
    options->out_filename = arg;
  else if (flag->flag == 'i')
    options->in_filename = arg;
  else
    return 0;

  return 1;
}

