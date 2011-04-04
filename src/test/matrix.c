#include <math.h>
#include "minunit.h"
#include "../epsilon.h"
#include "../matrix.h"
#include "../options.h"

static int matrix_is_equal(matrix_t *lh, matrix_t *rh) {
  if (lh->r != rh->r || lh->c != rh->c) {
    return 0;
  }
  int i;
  for (i = 0; i < lh->r * lh->c; ++i) {
    if (fabs(lh->t[i] - rh->t[i]) > EPSILON) {
      return 0;
    }
  }

  return 1;
}

static int gauss_with_no_gotchas()
{
  double ta[] = {2, 1, 3, -2};
  matrix_t *A = matrix_new(ta, 2, 2);
  double tb[] = {4, 13};
  matrix_t *b = matrix_new(tb, 2, 1);
  double tx[] = {3, -2};
  matrix_t *should_be_x = matrix_new(tx, 2, 1);

  matrix_t *x = matrix_gauss(A, b);
  mu_assert(matrix_is_equal(x, should_be_x));
}

static int bigger_gauss_with_no_gotchas()
{
  double ta[] = {2, 1, -1, -3, -1, 2, -2, 1, 2};
  matrix_t *A = matrix_new(ta, 3, 3);
  double tb[] = {8, -11, -3};
  matrix_t *b = matrix_new(tb, 3, 1);
  double tx[] = {2, 3, -1};
  matrix_t *should_be_x = matrix_new(tx, 3, 1);

  matrix_t *x = matrix_gauss(A, b);
  mu_assert(matrix_is_equal(x, should_be_x));
}

static int gauss_with_gotchas()
{
  double ta[] = {
    6, -3, 2, 1, -1, 1,
    -3, -7, 0, 4, -2, 1,
    4, -3, 6, -1, 2, 1,
    2, 4, 5, -7, -3, 2,
    -1, 5, -4, 0, 8, -2,
    3, 0, 4, -2, 5, -6
  };
  matrix_t *A = matrix_new(ta, 6, 6);
  double tb[] = {11, -5, 28, -6, 25, -4};
  matrix_t *b = matrix_new(tb, 6, 1);
  double tx[] = {1, 2, 3, 4, 5, 6};
  matrix_t *should_be_x = matrix_new(tx, 6, 1);

  matrix_t *x = matrix_gauss(A, b);
  mu_assert(matrix_is_equal(x, should_be_x));
}

int all_matrix_tests()
{
  options_init();
  options->quiet = 1;

  int (*tests[])() = {
    gauss_with_no_gotchas,
    bigger_gauss_with_no_gotchas,
    gauss_with_gotchas
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}
