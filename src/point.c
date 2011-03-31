#include <stdlib.h>
#include "point.h"

point_t *point_new(double x, double y)
{
  point_t *p = malloc(sizeof(*p));
  p->x = x;
  p->y = y;
  return p;
}

void point_free(point_t *p)
{
  if (p) {
    free(p);
  }
}
