#include <stdlib.h>
#include "minunit.h"
#include "spline.h"
#include "../list.h"
#include "../point.h"
#include "../spline.h"

static int basic_spline()
{
  int m = 2;
  list_t *nodes = list_add(NULL, point_new(1, 2));
  list_add(nodes, point_new(3, 3.5));
  list_add(nodes, point_new(5, 3.7));

  list_t *splines = spline_interpolate(nodes);

  polynomial_t **should_be_splines = malloc(sizeof(*should_be_splines) * m);
  double c0[] = { 1.128125, 0.790625, 0.121875, -0.040625 };
  should_be_splines[0] = polynomial_new(c0, 3);
  double c1[] = { -1.065625, 2.984375, -0.609375, 0.040625 };
  should_be_splines[1] = polynomial_new(c1, 3);

  int i;
  list_t *spline = NULL;
  for (i = 0, spline = splines; i < m; ++i, spline = spline->next) {
    if (!polynomial_is_equal((polynomial_t *)spline->data, should_be_splines[i]))
      mu_assert(0);
  }

  mu_assert(1);
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

