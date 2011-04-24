#include <string.h>
#include "flag.h"
#include "options.h"

flag_t known_flags[] = {
  {"out", 'o', 1},
  {"in", 'i', 1},
  {"gnuplot", 'g', 0},
  {"force", 'f', 0},
  {"quiet", 'q', 0}
};

int flag_is_long_flag(const char *arg)
{
  return strlen(arg) >= 3 && arg[0] == '-' && arg[1] == '-';
}

int flag_is_short_flag(const char *arg)
{
  return strlen(arg) == 2 && arg[0] == '-' && arg[1] != '-';
}

int flag_is_filename(const char *arg)
{
  return strlen(arg) >= 1 && arg[0] != '-';
}

flag_t *flag_find_by_name(const char *arg)
{
  int i;
  for (i = 0; i < sizeof(known_flags)/sizeof(known_flags[0]); ++i) {
    if (strcmp(arg, known_flags[i].name) == 0) {
      return known_flags+i;
    }
  }
  return NULL;
}

flag_t *flag_find(const char arg)
{
  int i;
  for (i = 0; i < sizeof(known_flags)/sizeof(known_flags[0]); ++i) {
    if (arg == known_flags[i].flag) {
      return known_flags+i;
    }
  }
  return NULL;
}

