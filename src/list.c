#include <stdlib.h>
#include "list.h"

list_t *list_add(list_t *head, void *data)
{
  list_t *new_node = malloc(sizeof(*new_node));
  new_node->data = data;
  new_node->next = NULL;
  
  list_t *last_node = head;
  if (last_node == NULL) {
    return new_node;
  }
  while (last_node->next != NULL) {
    last_node = last_node->next;
  }
  last_node->next = new_node;

  return head;
}

int list_length(list_t *head)
{
  list_t *node = head;
  int length = 0;

  for (node = head; node != NULL; node = node->next) {
    ++length;
  }

  return length;
}

