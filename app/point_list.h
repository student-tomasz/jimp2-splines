#ifndef _POINT_LIST_H
#define _POINT_LIST_H

#include "list.h"
#include "point.h"

list_t *point_list_add(list_t *head, double x, double y);
void point_list_free(list_t *head);
char *point_list_to_str(const list_t *head);

#endif

