#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "point.h"
#include "list.h"
#include "point_list.h"
#include "polynomial.h"
#include "options.h"

static char *io_change_filename_extension(char *filename, char *extension)
{
  char *new_filename = malloc(sizeof(*new_filename) * (strlen(filename)+strlen(extension)+2));
  strcpy(new_filename, filename);

  if (strlen(extension) == 0) {
    return new_filename;
  }

  char *dot = strrchr(new_filename, '.');
  if (dot)
    strcpy(dot, extension);
  else
    strcat(new_filename, extension);
  return new_filename;
}

list_t *io_read()
{
  FILE *source = NULL;
  if (options->in_filename)
    source = fopen(options->in_filename, "r");
  else
    source = stdin;

  if (!source) {
    return NULL; // TODO: error
  }

  int points_array_size = 8;
  int points_count = 0;
  point_t **points_array = malloc(sizeof(*points_array) * points_array_size);

  while (1) {
    double x, y;
    int read_count = fscanf(source, "%lg %lg", &x, &y);
    if (read_count == 2) {
      points_array[points_count++] = point_new(x, y);
      if (points_count == points_array_size-1) {
        points_array_size *= 2;
        points_array = realloc(points_array, sizeof(*points_array) * points_array_size);
      }
    }
    else if (read_count == EOF) {
      break; // TODO: log
    }
    else {
      if (source != stdin) fclose(source);
      return NULL; // TODO: error
    }
  }

  list_t *points = point_list_cleanup(points_array, points_count);

  int i;
  for (i = 0; i < points_count; ++i) {
    point_free(points_array[i]);
  }
  free(points_array);
  if (source != stdin) fclose(source);

  return points; // TODO: log
}

int io_write(list_t *nodes, list_t *splines)
{
  char *output_filename = NULL;
  if (options->out_filename) {
    output_filename = io_change_filename_extension(options->out_filename, "");
  }
  else {
    output_filename = io_change_filename_extension(options->in_filename, ".out");
  }

  FILE *output = fopen(output_filename, "r");
  if (output != NULL && options->force == 0) {
    free(output_filename);
    return 0; // TODO: error
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

  fclose(output);
  free(output_filename);
  return 1;
}

int io_gnuplot(list_t *nodes, list_t *splines)
{
  if (!options->gnuplot) {
    return 1; // TODO: log
  }

  char *output_filename = options->out_filename ? options->out_filename : options->in_filename;
  char *gnuplot_filename = io_change_filename_extension(output_filename, ".plt");
  char *plot_filename = io_change_filename_extension(output_filename, ".png");

  FILE *gnuplot = fopen(gnuplot_filename, "w");

  time_t rawtime;
  time(&rawtime);
  fprintf(gnuplot, "# created at: %s", ctime(&rawtime));
  fprintf(gnuplot, "#       file: %s\n", gnuplot_filename);
  fprintf(gnuplot, "set term png size 800, 600\n");
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
 
  fclose(gnuplot);
  free(plot_filename);
  free(gnuplot_filename);
  return 1;
}

