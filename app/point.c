#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "epsilon.h"

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

char *point_to_str(point_t *p)
{
  char *str = NULL;
  asprintf(&str, "%lg %lg", p->x, p->y);
  return str;
}

int point_is_equal(point_t *lp, point_t *rp)
{
  return is_equal(lp->x, rp->x) && is_equal(lp->y, rp->y);
}
