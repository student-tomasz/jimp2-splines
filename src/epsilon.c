#include <math.h>
#include "epsilon.h"

int is_equal(double l, double r)
{
  return fabs(l-r) < EPSILON;
}

int is_zero(double l)
{
  return is_equal(l, 0.0);
}

