#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "point.h"
#include "list.h"
#include "point_list.h"

list_t *io_read(const char *source_file)
{
  FILE *source = fopen(source_file, "r");
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
      fclose(source);
      return NULL; // TODO: error
    }
  }

  list_t *points = point_list_cleanup(points_array, points_count);

  int i;
  for (i = 0; i < points_count; ++i) {
    point_free(points_array[i]);
  }
  free(points_array);
  fclose(source);

  return points; // TODO: log
}

