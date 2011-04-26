#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "polynomial.h"
#include "epsilon.h"

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

int polynomial_is_equal(polynomial_t *lp, polynomial_t *rp) {
  if (lp->d != rp->d) {
    return 0;
  }

  int i;
  for (i = 0; i < lp->d; ++i) {
    if (!is_equal(lp->c[i], rp->c[i])) {
      return 0;
    }
  }

  return 1;
}

char *polynomial_to_str(polynomial_t *p)
{
  char *str = "";
  int i;
  for (i = 0; i <= p->d; ++i) {
    asprintf(&str, "%s %+g", str, p->c[i]);
    if (i == 0)
      ;
    else if (i == 1) {
      asprintf(&str, "%s*x", str);
    }
    else {
      asprintf(&str, "%s*x**%d", str, i);
    }
  }
  return str;
}

