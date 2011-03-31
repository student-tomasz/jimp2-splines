#include <math.h>
#include "minunit.h"
#include "../epsilon.h"
#include "../polynomial.h"

static int polynomial_is_equal(polynomial_t *lh, polynomial_t *rh) {
  if (lh->d != rh->d) {
    return 0;
  }
  int i;
  for (i = 0; i < lh->d; ++i) {
    if (fabs(lh->c[i] - rh->c[i]) > EPSILON) {
      return 0;
    }
  }

  return 1;
}

static void polynomial_print(polynomial_t *p)
{
  int i;
  for (i = p->d; i >= 0; --i) {
    printf("%g", p->c[i]);
    printf("*x**%d", i);
    if (i != 0) {
      printf(" + ");
    }
  }
  printf("\n");
}

static int derivate_simple_polynomial()
{
  double c[] = {3, 2, 1, -1};
  polynomial_t *p = polynomial_new(c, 3);

  double should_be_dc[] = {2, 2, -3};
  polynomial_t *should_be_dp = polynomial_new(should_be_dc, 2);

  polynomial_t *dp = polynomial_derivate(p);
  mu_assert(polynomial_is_equal(dp, should_be_dp));

  polynomial_free(dp);
  polynomial_free(should_be_dp);
  polynomial_free(p);
  return 0;
}

int all_polynomial_tests()
{
  int (*tests[])() = {
    derivate_simple_polynomial
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}

