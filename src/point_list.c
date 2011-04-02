#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "epsilon.h"
#include "io.h"
#include "list.h"
#include "point.h"
#include "point_list.h"

static int point_list_compare(const void *lp, const void *rp)
{
  point_t *l = *((point_t **)lp);
  point_t *r = *((point_t **)rp);

  if (is_equal(l->x, r->x))
    return 0;
  else if (l->x - r->x > 0)
    return 1;
  else
    return -1;
}

list_t *point_list_cleanup(point_t **points_array, int points_count)
{
  qsort(points_array, points_count, sizeof(*points_array), point_list_compare);

  list_t *points = NULL;
  point_t *curr_p = NULL;
  point_t *last_p = NULL;
  int i;
  for (i = 0; i < points_count; ++i) {
    curr_p = points_array[i];
    if (curr_p && last_p && is_equal(curr_p->x, last_p->x))
      continue;
    points = list_add(points, point_new(curr_p->x, curr_p->y));
    last_p = curr_p;
  }

  return points;
}

char *point_list_to_str(list_t *head)
{
  char *str = malloc(sizeof(*str) * (MAX_STR_LENGTH * 10 + 1));
  str[0] = '\0';
  char *tmp = malloc(sizeof(*tmp) * (MAX_STR_LENGTH + 1));

  list_t *node = NULL;
  for (node = head; node != NULL; node = node->next) {
    sprintf(tmp, "%s", point_to_str((point_t *)node->data));
    strcat(str, tmp);
  }

  free(tmp);
  return str;
}

