#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "epsilon.h"
#include "logger.h"

static matrix_t *matrix_copy(const matrix_t *m);
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

static matrix_t *matrix_copy(const matrix_t *m)
{
  return matrix_new(m->t, m->r, m->c);
}

void matrix_free(matrix_t *m)
{
  if (m) {
    free(m->t);
    free(m);
  }
}

matrix_t *matrix_gauss(const matrix_t *_A, const matrix_t *_b)
{
  if (!matrix_is_square(_A)) {
    log_error("matrix isn't square");
    return NULL;
  }

  matrix_t *A = matrix_copy(_A);
  matrix_t *b = matrix_copy(_b);

  int i, j, n = A->c;
  for (i = 0; i < n; ++i) {
    int max_i = matrix_find_max_in_column(A, i);
    if (is_zero(A->t[max_i*n+i])) {
      log_error("matrix has an empty column, which gives more than one solution");
      return NULL;
    }
    matrix_swap_rows(A, i, max_i);
    matrix_swap_rows(b, i, max_i);

    for (j = i+1; j < n; ++j) {
      double coeff = A->t[j*n+i]/A->t[i*n+i];
      matrix_subtract_rows(A, j, coeff, i);
      matrix_subtract_rows(b, j, coeff, i);
    }
  }

  matrix_t *x = matrix_solve_upper_diagonal(A, b);
  matrix_free(b);
  matrix_free(A);
  return x;
}

char *matrix_to_str(const matrix_t *m)
{
  char *str = NULL;

  asprintf(&str, "\n[");
  int i, j;
  for (i = 0; i < m->r; ++i) {
    asprintf(&str, "%s[", str);
    for (j = 0; j < m->c; ++j) {
      double v = m->t[i*m->c+j];
      asprintf(&str, "%s%g%s", str, v, j == m->c-1 ? "" : ", ");
    }
    asprintf(&str, "%s]%s", str, i == m->r-1 ? "" : ",\n");
  }
  asprintf(&str, "%s]\n", str);

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

