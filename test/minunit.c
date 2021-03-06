#include "minunit.h"
#include "matrix.h"
#include "spline.h"
#include "io.h"
#include "cli.h"
#include "../app/options.h"

int tests_run = 0;

int main(int argc, char **argv)
{
  options_init();
  options->quiet = 1;

  int (*test_suites[])() = {
    all_matrix_tests,
    all_spline_tests,
    all_io_tests,
    all_cli_tests
  };

  int i;
  for(i = 0; i < sizeof(test_suites)/sizeof(test_suites[0]); ++i) {
    if (test_suites[i]()) {
      printf("\nfail: some tests failed\n\n");
      return 1;
    }
  }
  printf("\nsuccess: all %d tests passed\n\n", tests_run);
  return 0;
}

