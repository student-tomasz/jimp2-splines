#include <stdlib.h>
#include "minunit.h"
#include "spline.h"
#include "../point.h"
#include "../spline.h"

static int basic_spline()
{
  int m = 2;
  point_t **nodes = malloc(sizeof(*nodes) * (m+1));
  nodes[0] = point_new(1, 2);
  nodes[1] = point_new(3, 3.5);
  nodes[2] = point_new(5, 3.7);

  polynomial_t **splines = spline_interpolate(nodes, m+1);

  polynomial_t **should_be_splines = malloc(sizeof(*should_be_splines) * m);
  double c0[] = { 1.128125, 0.790625, 0.121875, -0.040625 };
  should_be_splines[0] = polynomial_new(c0, 3);
  double c1[] = { -1.065625, 2.984375, -0.609375, 0.040625 };
  should_be_splines[1] = polynomial_new(c1, 3);

  int result = 1;
  int i;
  for (i = 0; i < m; ++i) {
    if (!polynomial_is_equal(splines[i], should_be_splines[i]))
      result = 0;
  }

  mu_assert(result);
  return 0;
}

int all_spline_tests()
{
  int (*tests[])() = {
    basic_spline
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}

