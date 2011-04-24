#ifndef _POINT_H
#define _POINT_H

typedef struct point_s {
  double x;
  double y;
} point_t;

point_t *point_new(double x, double y);
void point_free(point_t *p);
char *point_to_str(point_t *p);
int point_is_equal(point_t *lp, point_t *rp);

#endif /* _POINT_H */
