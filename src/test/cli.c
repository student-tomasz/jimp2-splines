#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"
#include "cli.h"
#include "../cli.h"
#include "../options.h"
#include "../flag.h"

static int empty_flags()
{
  char *argv[] = {"exec_filename"};
  int argc = 1;

  mu_assert(!cli_parse(argc, argv));
}

static int valid_simple_flags()
{
  char *argv[] = {"exec_filename", "-f", "-q", "--out", "out_filename"};
  int argc = 5;
  cli_parse(argc, argv);

  mu_assert(
    options->in_filename == NULL &&
    strcmp(options->out_filename, "out_filename") == 0 &&
    options->gnuplot == 0 &&
    options->force == 1 &&
    options->quiet == 1
  );
}

static int valid_mixed_flags()
{
  char *argv[] = {"exec_filename", "--force", "in_filename", "-g"};
  int argc = 4;
  cli_parse(argc, argv);

  mu_assert(
    strcmp(options->in_filename, "in_filename") == 0 &&
    options->out_filename == NULL &&
    options->gnuplot == 1 &&
    options->force == 1 &&
    options->quiet == 0
  );
}

static int invalid_flags()
{
  char *argv[] = {"exec_filename", "--force", "in_filename", "-invalid_flag"};
  int argc = 4;
  
  mu_assert(!cli_parse(argc, argv));
}

static int invalid_out_flags()
{
  char *argv[] = {"exec_filename", "--force", "in_filename", "-o"};
  int argc = 4;
  
  mu_assert(!cli_parse(argc, argv));
}

static int multiple_in_flags()
{
  char *argv[] = {"exec_filename", "--force", "in_filename", "-o", "out_filename", "other_in_filename"};
  int argc = 6;
  cli_parse(argc, argv);

  mu_assert(
    strcmp(options->in_filename, "other_in_filename") == 0 &&
    strcmp(options->out_filename, "out_filename") == 0 &&
    options->gnuplot == 0 &&
    options->force == 1 &&
    options->quiet == 0
  );
}

int all_cli_tests()
{
  int (*tests[])() = {
    empty_flags,
    valid_simple_flags,
    valid_mixed_flags,
    invalid_flags,
    invalid_out_flags,
    multiple_in_flags
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}

