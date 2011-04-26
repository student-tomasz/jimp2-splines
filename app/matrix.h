#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct matrix_s {
  double *t;
  int r;
  int c;
} matrix_t;

matrix_t *matrix_new(const double *t, int r, int c);
void matrix_free(matrix_t *m);
matrix_t *matrix_gauss(const matrix_t *A, const matrix_t *b);
char *matrix_to_str(const matrix_t *m);

#endif // _MATRIX_H

