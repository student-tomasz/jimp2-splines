#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "io.h"
#include "logger.h"
#include "point.h"
#include "list.h"
#include "point_list.h"
#include "polynomial.h"
#include "options.h"
#include "file_helpers.h"



list_t *io_read()
{
  FILE *source = NULL;
  if (options->in_filename) {
    source = fopen(options->in_filename, "r");
    log_info("reading data from file: %s", options->in_filename);
  }
  else {
    source = stdin;
    log_info("reading data from standard input");
  }

  if (!source) {
    log_error("input stream is invalid");
    return NULL;
  }

  list_t *points = NULL;
  double x, y;
  while (1) {
    int read = fscanf(source, "%lg %lg", &x, &y);
    if (read == 2) {
      points = point_list_add(points, x, y);
    }
    else if (read == EOF) {
      log_info("read %d points", list_length(points));
      break;
    }
    else {
      if (source != stdin) fclose(source);
      log_error("input data is corrupted");
      return NULL;
    }
  }

  if (source != stdin) fclose(source);
  return points;
}



int io_write(list_t *nodes, list_t *splines)
{
  char *output_filename = NULL;
  if (options->out_filename) {
    output_filename = file_helpers_change_extension(options->out_filename, "");
  }
  else {
    output_filename = file_helpers_change_extension(options->in_filename, ".out");
  }

  FILE *output = fopen(output_filename, "r");
  if (output != NULL && options->force == 0) {
    log_error("couldn't write output to %s", output_filename);
    free(output_filename);
    return 0;
  }
  fclose(output);
  output = fopen(output_filename, "w");

  time_t rawtime;
  time(&rawtime);
  fprintf(output, "# created at: %s", ctime(&rawtime));
  fprintf(output, "#       file: %s\n", output_filename);
  fprintf(output, "# [x=x_{n1}:x_{n2}] fun_n(x) =  a_{n0} + a_{n1}*x + a_{n2}*x**2 + a_{n3}*x**3\n");

  list_t *spline = splines;
  list_t *node = nodes;
  int i = 0;
  for(spline = splines, node = nodes; spline && node; spline = spline->next, node = node->next) {
    char *poly_str = polynomial_to_str((polynomial_t *)spline->data);
    fprintf(output, "[x=%lg:%lg] fun%d(x) = %s\n",
        ((point_t *)node->data)->x,
        ((point_t *)node->next->data)->x,
        i++,
        poly_str);
    free(poly_str);
  }

  log_info("output written to %s", output_filename);
  fclose(output);
  free(output_filename);
  return 1;
}



int io_gnuplot(list_t *nodes, list_t *splines)
{
  if (!options->gnuplot) {
    return 1;
  }

  const char *output_filename = options->out_filename ? options->out_filename : options->in_filename;
  char *gnuplot_filename = file_helpers_change_extension(output_filename, ".plt");
  char *plot_filename = file_helpers_change_extension(output_filename, ".pdf");

  FILE *gnuplot = fopen(gnuplot_filename, "w");
  if (!gnuplot) {
    log_info("couldn't write gnuplot output to %s", gnuplot_filename);
    free(plot_filename);
    free(gnuplot_filename);
    return 0;
  }

  time_t rawtime;
  time(&rawtime);
  fprintf(gnuplot, "# created at: %s", ctime(&rawtime));
  fprintf(gnuplot, "#       file: %s\n", gnuplot_filename);
  fprintf(gnuplot, "set term pdf\n");
  fprintf(gnuplot, "set output \"%s\"\n", plot_filename);
  fprintf(gnuplot, "set nokey\n");
  fprintf(gnuplot, "set notitle\n");
  fprintf(gnuplot, "set grid\n");
  fprintf(gnuplot, "\n");
  fprintf(gnuplot, "set parametric\n");
  fprintf(gnuplot, "\n");

  list_t *spline = splines;
  list_t *node = nodes;
  
  int i;
  for (node = nodes, i = 0; node != NULL; node = node->next, ++i) {
    point_t *p = (point_t *)node->data;
    fprintf(gnuplot, "x%d = %lg; y%d = %lg;\n", i, p->x, i, p->y);
  }
  fprintf(gnuplot, "\n");

  for (i = 0; i < list_length(nodes); ++i) {
    fprintf(gnuplot, "x%d(t) = x%d+(x%d-x%d)*t;\n", i, i, i+1, i);
  }
  fprintf(gnuplot, "\n");

  for (spline = splines, i = 0; spline != NULL; spline = spline->next, ++i) {
    char *poly_str = polynomial_to_str((polynomial_t *)spline->data);
    fprintf(gnuplot, "fun%d(x) = %s\n", i, poly_str);
    free(poly_str);
  }
  fprintf(gnuplot, "\n");

  fprintf(gnuplot, "plot [t=0:1]\\\n");
  for (i = 0; i < list_length(splines); ++i) {
    fprintf(gnuplot, "\tx%d(t), fun%d(x%d(t)),\\\n", i, i, i);
  }
  fprintf(gnuplot, "\t\"-\" with points\n");
  for (node = nodes; node != NULL; node = node->next) {
    point_t *p = (point_t *)node->data;
    fprintf(gnuplot, "\t\t%lg %lg\n", p->x, p->y);
  }
  fprintf(gnuplot, "\te\n");

  log_info("gnuplot output written to %s", gnuplot_filename);
  fclose(gnuplot);
  free(plot_filename);
  free(gnuplot_filename);
  return 1;
}

