#include <math.h>
#include "minunit.h"
#include "../epsilon.h"
#include "../polynomial.h"

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

