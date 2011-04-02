#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"
#include "io.h"
#include "../io.h"
#include "../point.h"
#include "../list.h"
#include "../point_list.h"

static int read_correct_file()
{
  const char *file = "correct_file.dat";
  FILE *source = fopen(file, "w");

  int i, m = 2;
  point_t **should_be_nodes = malloc(sizeof(*should_be_nodes) * (m+1));
  should_be_nodes[0] = point_new(1, 2);
  should_be_nodes[1] = point_new(3, 3.5);
  should_be_nodes[2] = point_new(5, 3.7);
  for (i = 0; i < m+1; ++i) {
    fprintf(source, "%lg %lg\n", should_be_nodes[i]->x, should_be_nodes[i]->y);
  }
  fclose(source);
  
  list_t *nodes = io_read(file);
  list_t *node;
  if (!nodes) {
    return 1;
  }
  for (node = nodes, i = 0; i < m+1; node = node->next, ++i) {
    /* printf("lol: %s == %s\n", point_to_str((point_t *)node->data), point_to_str(should_be_nodes[i]));*/
    if (!point_is_equal((point_t *)node->data, should_be_nodes[i]))
      mu_assert(0);
  }

  mu_assert(1);
  return 0;
}

static int read_correct_file_with_poor_formating()
{
  const char *file = "correct_file_with_poor_formating.dat";
  FILE *source = fopen(file, "w");

  int i, m = 2;
  point_t **should_be_nodes = malloc(sizeof(*should_be_nodes) * (m+1));
  should_be_nodes[0] = point_new(1, 2);
  should_be_nodes[1] = point_new(3, 3.5);
  should_be_nodes[2] = point_new(5, 3.7);

  fprintf(source, " %lg %lg\n", should_be_nodes[0]->x, should_be_nodes[0]->y);
  fprintf(source, "%lg  %lg\t", should_be_nodes[2]->x, should_be_nodes[2]->y);
  fprintf(source, "\t%lg %lg", should_be_nodes[1]->x, should_be_nodes[1]->y);

  fclose(source);
  
  list_t *nodes = io_read(file);
  list_t *node;
  if (!nodes) {
    return 1;
  }
  for (node = nodes, i = 0; i < m+1; node = node->next, ++i) {
    /* printf("lol: %s == %s\n", point_to_str((point_t *)node->data), point_to_str(should_be_nodes[i]));*/
    if (!point_is_equal((point_t *)node->data, should_be_nodes[i]))
      mu_assert(0);
  }

  mu_assert(1);
  return 0;
}

static int read_correct_file_with_poor_formating_and_duplicate_points()
{
  const char *file = "correct_file_with_poor_formating_and_duplicate_points.dat";
  FILE *source = fopen(file, "w");

  int i, m = 2;
  point_t **should_be_nodes = malloc(sizeof(*should_be_nodes) * (m+2));
  should_be_nodes[0] = point_new(1, 2);
  should_be_nodes[3] = point_new(1, 1);
  should_be_nodes[1] = point_new(3, 3.5);
  should_be_nodes[2] = point_new(5, 3.7);

  fprintf(source, " %lg %lg\n", should_be_nodes[0]->x, should_be_nodes[0]->y);
  fprintf(source, "%lg  %lg\t", should_be_nodes[2]->x, should_be_nodes[2]->y);
  fprintf(source, " %lg %lg\n", should_be_nodes[3]->x, should_be_nodes[3]->y);
  fprintf(source, "\t%lg %lg", should_be_nodes[1]->x, should_be_nodes[1]->y);

  fclose(source);
  
  list_t *nodes = io_read(file);
  list_t *node;
  if (!nodes) {
    return 1;
  }
  for (node = nodes, i = 0; i < m+1; node = node->next, ++i) {
    if (!point_is_equal((point_t *)node->data, should_be_nodes[i]))
      mu_assert(0);
  }

  mu_assert(1);
  return 0;
}

int all_io_tests()
{
  int (*tests[])() = {
    read_correct_file,
    read_correct_file_with_poor_formating,
    read_correct_file_with_poor_formating_and_duplicate_points
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}

