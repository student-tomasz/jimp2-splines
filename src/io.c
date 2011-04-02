#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "point.h"
#include "point_list.h"

point_list_t *io_read(const char *source_file)
{
  FILE *source = fopen(source_file, "r");
  if (!source) {
    return NULL; // TODO: error
  }

  point_list_t *nodes = NULL;
  double x, y;
  while (1) {
    int read_count = fscanf(source, "%lg %lg", &x, &y);
    if (read_count == 2) {
      nodes = point_list_add(nodes, point_new(x, y));
    }
    else if (read_count == EOF) {
      break; // TODO: log
    }
    else {
      fclose(source);
      return NULL; // TODO: error
    }
  }

  fclose(source);
  return nodes; // TODO: log
}

