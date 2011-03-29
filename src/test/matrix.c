#include "minunit.h"
#include "../matrix.h"

static int new_square()
{
  double t[] = {1.1, 2.2, 3.3, 4.4};
  int r = 2;
  int c = 2;
  matrix_t *m = matrix_new(t, r, c);

  printf("%s:%d: test %s says: ", __FILE__, __LINE__, __func__);
  int i;
  for (i = 0; i < 4; ++i) {
    printf("%g ", m->t[i]);
  }
  printf("\n");

  matrix_free(m);

  mu_assert(1);
  return 0;
}

int all_matrix_tests()
{
  int (*tests[])() = {
    new_square
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}
