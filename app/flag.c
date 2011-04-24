#include <string.h>
#include "flag.h"

flag_t flags_all[] = {
  {"out",     'o', 1},
  {"in",      'i', 1},
  {"gnuplot", 'g', 0},
  {"force",   'f', 0},
  {"quiet",   'q', 0}
};
const int flags_all_count = sizeof(flags_all)/sizeof(flags_all[0]);

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
  for (i = 0; i < flags_all_count; ++i) {
    if (strcmp(arg, flags_all[i].name) == 0) {
      return flags_all+i;
    }
  }
  return NULL;
}

flag_t *flag_find(const char arg)
{
  int i;
  for (i = 0; i < flags_all_count; ++i) {
    if (arg == flags_all[i].flag) {
      return flags_all+i;
    }
  }
  return NULL;
}

