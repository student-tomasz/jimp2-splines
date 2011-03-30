#include "minunit.h"
#include "../matrix.h"

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

static void matrix_print(matrix_t *A)
{
  printf("[");
  int i, j;
  for (i = 0; i < A->r; ++i) {
    printf("[");
    for (j = 0; j < A->c; ++j) {
      double a = A->t[i*A->c+j];
      if (j != A->c-1)
        printf("%g, ", a);
      else
        printf("%g", a);
    }
    if (i != A->r-1)
      printf("],");
    else
     printf("]");
  }
  printf("]\n");
}

static int create_the_simplest_matrix()
{
  double t[] = {1.1, 2.2, 3.3, 4.4};
  matrix_t *m = matrix_new(t, 2, 2);

  printf("%s:%d: test %s says:\n", __FILE__, __LINE__, __func__);
  matrix_print(m);

  matrix_free(m);
  mu_assert(1);
  return 0;
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

  matrix_free(x);
  matrix_free(should_be_x);
  matrix_free(b);
  matrix_free(A);
  return 0;
}

static int bigger_gauss_with_no_gotchas()
{
  double ta[] = {2, 1, -1, -3, -1, 2, -2, 1, 2};
  matrix_t *A = matrix_new(ta, 3, 3);
  double tb[] = {8, -11, -3};
  matrix_t *b = matrix_new(tb, 3, 1);
  double tx[] = {2, 3, -1};
  matrix_t *should_be_x = matrix_new(tx, 3, 1);

  /* printf("%s:%d: test %s says:\n", __FILE__, __LINE__, __func__);*/
  matrix_t *x = matrix_gauss(A, b);
  mu_assert(matrix_is_equal(x, should_be_x));

  matrix_free(x);
  matrix_free(should_be_x);
  matrix_free(b);
  matrix_free(A);
  return 0;
}

int all_matrix_tests()
{
  int (*tests[])() = {
    create_the_simplest_matrix,
    gauss_with_no_gotchas,
    bigger_gauss_with_no_gotchas
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}
