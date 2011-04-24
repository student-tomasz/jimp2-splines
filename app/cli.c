#include <stdlib.h>
#include "cli.h"
#include "options.h"
#include "io.h"

int cli_parse(const int argc, const char **argv)
{
  options_init();

  flag_t *flag;
  const char *arg;
  int i;
  for (arg = argv[i=1]; i < argc; arg = argv[++i]) {
    flag = NULL;

    if (flag_is_long_flag(arg)) {
      flag = flag_find_by_name(arg+2);
    }
    else if (flag_is_short_flag(arg)) {
      flag = flag_find(arg[1]);
    }
    else if (flag_is_filename(arg)) {
      flag = flag_find_by_name("in");
      options_set_with_arg(flag, arg);
      continue;
    }

    if (!flag) {
      return 0;
    }
    else if (flag->args > 0) {
      if (i+1 < argc)
        options_set_with_arg(flag, argv[++i]);
      else {
        return 0;
      }
    }
    else {
      options_set(flag);
    }
  }

  if (options->out_filename == NULL && options->in_filename == NULL) {
    fprintf(stderr, "[error] %s:%d:%s(): at least one filename (input or output) has to declared\n", __FILE__, __LINE__, __func__);
    return 0;
  }

  io_log("parsed arguments from command line");
  return 1;
}
