#include <stdlib.h>
#include "point.h"
#include "point_list.h"

point_list_t *point_list_add(point_list_t *head, point_t *point)
{
  point_list_t *new_node = malloc(sizeof(*new_node));
  new_node->point = point;
  new_node->next = NULL;
  
  point_list_t *last_node = head;
  if (last_node == NULL) {
    return new_node;
  }
  while (last_node->next != NULL) {
    last_node = last_node->next;
  }
  last_node->next = new_node;

  return head;
}

int point_list_length(point_list_t *head)
{
  point_list_t *node = head;
  int length = 0;

  for (node = head; node != NULL; node = node->next) {
    ++length;
  }

  return length;
}

