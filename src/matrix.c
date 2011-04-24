#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include "epsilon.h"
#include "matrix.h"

static int matrix_find_max_in_column(const matrix_t *A, int i);
static void matrix_swap_rows(matrix_t *A, int lh, int rh);
static void matrix_add_rows(matrix_t *A, int lh, double coeff, int rh);
static void matrix_subtract_rows(matrix_t *A, int lh, double coeff, int rh);
static int matrix_is_square(const matrix_t *A);
static matrix_t *matrix_solve_upper_diagonal(const matrix_t *A, const matrix_t *b);

matrix_t *matrix_new(const double *t, int r, int c)
{
  matrix_t *m = malloc(sizeof(*m));
  m->t = malloc(sizeof(*(m->t)) * r*c);
  m->r = r;
  m->c = c;

  int i, j;
  for (i = 0; i < r; ++i) {
    for (j = 0; j < c; ++j) {
      m->t[i*c+j] = t ? t[i*c+j] : 0;
    }
  }
  return m;
}

void matrix_free(matrix_t *m)
{
  if (m) {
    free(m->t);
    free(m);
  }
}

matrix_t *matrix_gauss(const matrix_t *A, const matrix_t *b)
{
  if (!matrix_is_square(A)) {
    return NULL; // TODO: error
  }
  matrix_t *Q = matrix_new(A->t, A->r, A->c);
  matrix_t *r = matrix_new(b->t, b->r, b->c);

  int n = Q->c;
  int i, j;
  for (i = 0; i < n; ++i) {
    int max_i = matrix_find_max_in_column(Q, i);
    if (is_zero(Q->t[max_i*n+i])) {
      return NULL; // TODO: error
    }
    matrix_swap_rows(Q, i, max_i);
    matrix_swap_rows(r, i, max_i);

    for (j = i+1; j < n; ++j) {
      double coeff = Q->t[j*n+i]/Q->t[i*n+i];
      matrix_subtract_rows(Q, j, coeff, i);
      matrix_subtract_rows(r, j, coeff, i);
    }
  }

  matrix_t *x = matrix_solve_upper_diagonal(Q, r);
  matrix_free(r);
  matrix_free(Q);
  return x;
}

char *matrix_to_str(const matrix_t *m)
{
  char *str = malloc(sizeof(*str) * (MAX_STR_LENGTH * 10 + 1));
  str[0] = '\0';
  char *tmp = malloc(sizeof(*tmp) * (MAX_STR_LENGTH + 1));

  sprintf(tmp, "[");
  strcat(str, tmp);
  int i, j;
  for (i = 0; i < m->r; ++i) {
    sprintf(tmp, "[");
    strcat(str, tmp);
    for (j = 0; j < m->c; ++j) {
      double v = m->t[i*m->c+j];
      if (j != m->c-1)
        sprintf(tmp, "%g, ", v);
      else
        sprintf(tmp, "%g", v);
      strcat(str, tmp);
    }
    sprintf(tmp, "]%s", i == m->r-1 ? "" : ",\n");
    strcat(str, tmp);
  }
  sprintf(tmp, "]\n");
  strcat(str, tmp);

  free(tmp);
  return str;
}

static int matrix_find_max_in_column(const matrix_t *A, int i)
{
  int max_i = i;
  int n = A->r;
  int k;
  for (k = i; k < n; ++k) {
    if (fabs(A->t[k*n + i]) > fabs(A->t[max_i*n + i])) {
      max_i = k;
    }
  }
  return max_i;
}

static void matrix_swap_rows(matrix_t *A, int lh, int rh)
{
  if (lh == rh) {
    return;
  }

  int n = A->c;
  int k;
  for (k = 0; k < n; ++k) {
    double tmp = A->t[lh*n+k];
    A->t[lh*n+k] = A->t[rh*n+k];
    A->t[rh*n+k] = tmp;
  }
}

static void matrix_add_rows(matrix_t *A, int lh, double coeff, int rh)
{
  int n = A->c;
  int k;
  for (k = 0; k < n; ++k) {
    A->t[lh*n+k] += coeff * A->t[rh*n+k];
  }
}

static void matrix_subtract_rows(matrix_t *A, int lh, double coeff, int rh)
{
  matrix_add_rows(A, lh, (-1.0)*coeff, rh);
}

static int matrix_is_square(const matrix_t *A)
{
  return (A->r == A->c) && (A->c > 0);
}

static matrix_t *matrix_solve_upper_diagonal(const matrix_t *A, const matrix_t *b)
{
  matrix_t *x = matrix_new(NULL, b->r, b->c);

  int n = b->r, i, j;
  for (i = n-1; i >= 0; --i) {
    double s = 0.0;
    for (j = i+1; j < n; ++j) {
      s += A->t[i*n+j] * x->t[j];
    }
    x->t[i] = (b->t[i]-s)/A->t[i*n+i];
  }

  return x;
}

