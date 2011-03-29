#include <stdlib.h>
#include "matrix.h"

matrix_t *matrix_new(double *t, int r, int c)
{
  matrix_t *m = malloc(sizeof(*m));
  m->t = malloc(sizeof(*(m->t)) * r * c);
  if (!m || !(m->t)) {
    return NULL;
  }

  int i, j;
  for (i = 0; i < r; ++i) {
    for (j = 0; j < c; ++j) {
      m->t[i*c + j] = t[i*c + j];
    }
  }

  return m;
}

void matrix_free(matrix_t *m)
{
  free(m->t);
  free(m);
}

