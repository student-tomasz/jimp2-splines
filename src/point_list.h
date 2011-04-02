#ifndef _POINT_LIST_H
#define _POINT_LIST_H

#include "point.h"

typedef struct point_list_s {
  struct point_list_s *next;
  point_t *point;
} point_list_t;

point_list_t *point_list_add(point_list_t *head, point_t *point);
int point_list_length(point_list_t *head);

#endif

