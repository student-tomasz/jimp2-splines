#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"
#include "io.h"
#include "../io.h"
#include "../point.h"
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
  
  point_list_t *nodes = io_read(file);
  point_list_t *node;
  if (!nodes) {
    return 1;
  }
  for (node = nodes, i = 0; i < m+1; node = node->next, ++i) {
    /* printf("lol: %s == %s\n", point_to_str(node->point), point_to_str(should_be_nodes[i]));*/
    if (!point_is_equal(node->point, should_be_nodes[i]))
      return 1;
  }

  mu_assert(1);
  return 0;
}

int all_io_tests()
{
  int (*tests[])() = {
    read_correct_file
  };

  int i;
  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    mu_run_test(tests[i]);
  }

  return 0;
}

