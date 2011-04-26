#ifndef _FLAG_H
#define _FLAG_H

typedef struct flag_s {
  char *name;
  char flag;
  int args;
} flag_t;

int flag_is_long_flag(const char *arg);
int flag_is_short_flag(const char *arg);
int flag_is_filename(const char *arg);
flag_t *flag_find_by_name(const char *arg);
flag_t *flag_find(const char arg);

#endif

