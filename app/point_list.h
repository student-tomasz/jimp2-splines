#ifndef _POINT_LIST_H
#define _POINT_LIST_H

#include "list.h"

list_t *point_list_cleanup(point_t **points_array, int points_count);
char *point_list_to_str(list_t *head);

#endif

