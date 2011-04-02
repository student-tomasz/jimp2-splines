#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "list.h"
#include "polynomial.h"
#include "matrix.h"
#include "spline.h"

polynomial_t **spline_interpolate(list_t *nodes)
{
  int m = list_length(nodes)-1;
  int d = 4;
  int i, j, l;

  /* allocate helper arrays */
  double *x = malloc(sizeof(*x) * m+1);
  double *y = malloc(sizeof(*y) * m+1);

  /* allocate matrices Q[,] * k[] = d[] */
  matrix_t *A = matrix_new(NULL, d*m, d*m);
  matrix_t *k;
  matrix_t *b = matrix_new(NULL, d*m, 1);

  /* fill helpers */
  list_t *node;
  for (node = nodes, i = 0; node != NULL; node = node->next, ++i) {
    x[i] = ((point_t *)node->data)->x;
    y[i] = ((point_t *)node->data)->y;
  }

  /* fill matrix A with values of polynomials */
  for (i = 0; i < m; ++i) {       /* for each polynomial */
    for (j = 0; j < 2; ++j) {     /* we have two points */
      for (l = 0; l < d; ++l) {   /* and their values describe d coefficients */
        A->t[((2*i+j)*(A->c))+(i*d+l)] = pow(x[i+j], l);
      }
      b->t[2*i+j] = y[i+j];
    }
  }

  /* fill matrix A with values from first derivatives */
  int last_row = 2*i;
  for (i = 1; i <= m-1; ++i, ++last_row) { /* for each point in between */
    for (j = 0; j < 2; ++j) {              /* we have two polynomials */
      for (l = 0; l < d; ++l) {
        A->t[(last_row*(A->c))+(d*(i-1+j)+l)] = l*pow(x[i], l-1)*pow(-1, j);
      }
    }
    b->t[last_row] = 0;
  }

  /* fill matrix A with values from second derivatives */
  for (i = 1; i <= m-1; ++i, ++last_row) { /* for each point in between */
    for (j = 0; j < 2; ++j) {              /* we have two polynomials */
      for (l = 0; l < d; ++l) {
        A->t[(last_row*(A->c))+(d*(i-1+j)+l)] = l*(l-1)*pow(x[i], l-2)*pow(-1, j);
      }
    }
    b->t[last_row] = 0;
  }

  /* fill the rest of A with margin cases */
  for (j = 0; j < 2; ++j, ++last_row) {    /* two margin points: 0 - first & 1 - last */
    for (l = 0; l < d; ++l) {
      A->t[(last_row*(A->c))+(d*(j*(m-1))+l)] = l*(l-1)*pow(x[j*m], l-2);
    }
    b->t[last_row] = 0;
  }

  /* guass that frickin' matrix */
  k = matrix_gauss(A, b);

  /* get all the polynomials */
  polynomial_t **splines = malloc(sizeof(*splines) * m);
  for (i = 0; i < m; ++i) {
    double coeffs[] = { k->t[i*d + 0], k->t[i*d + 1], k->t[i*d + 2], k->t[i*d + 3] };
    splines[i] = polynomial_new(coeffs, 3);
  }

  return splines;
}
