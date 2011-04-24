#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "epsilon.h"
#include "polynomial.h"
#include "io.h"

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
  char *str = malloc(sizeof(*str) * (MAX_STR_LENGTH + 1));
  char *tmp = malloc(sizeof(*tmp) * (MAX_STR_LENGTH + 1));

  str[0] = '\0';
  int i;
  for (i = 0; i <= p->d; ++i) {
    sprintf(tmp, "%10.10g", p->c[i]);
    strcat(str, tmp);

    if (i == 0)
      ;
    else if (i == 1) {
      sprintf(tmp, "*x");
      strcat(str, tmp);
    }
    else {
      sprintf(tmp, "*x**%d", i);
      strcat(str, tmp);
    }

    if (i != p->d) {
      sprintf(tmp, " + ");
      strcat(str, tmp);
    }
  }

  free(tmp);
  return str;
}

