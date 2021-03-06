#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

typedef struct polynomial_s {
  double *c;
  int d;
} polynomial_t;

polynomial_t *polynomial_new(double *coeffs, int degree);
void polynomial_free(polynomial_t *p);
int polynomial_is_equal(polynomial_t *lp, polynomial_t *rp);
char *polynomial_to_str(polynomial_t *p);

#endif /* _POLYNOMIAL_H */

