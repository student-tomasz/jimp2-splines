#include <math.h>
#include "epsilon.h"

int is_equal(double l, double r)
{
  return fabs(l-r) < EPSILON;
}

