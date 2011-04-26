#include <math.h>
#include "epsilon.h"

int is_equal(const double l, const double r)
{
  return fabs(l-r) < EPSILON;
}

int is_zero(const double l)
{
  return is_equal(l, 0.0);
}

