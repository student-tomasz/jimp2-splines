#include <stdlib.h>
#include "polynomial.h"

polynomial_t *polynomial_new(double *coeffs, int degree)
{
  polynomial_t *p = malloc(sizeof(*p));
  p->c = malloc(sizeof(*(p->c)) * (degree+1));
  p->d = degree;

  if (coeffs) {
    int i;
    for (i = 0; i <= p->d; ++i) {
      p->c[i] = coeffs[i];
    }
  }

  return p;
}

void polynomial_free(polynomial_t *p) {
  if (p) {
    free(p->c);
    free(p);
  }
}

polynomial_t *polynomial_derivate(polynomial_t *p)
{
  int d = p->d-1;
  double *c = malloc(sizeof(*c) * d);

  int i;
  for (i = d; i >= 0; --i) {
    c[i] = p->c[i+1]*(i+1);
  }

  return polynomial_new(c, d);
}
