#ifndef _LIST_H
#define _LIST_H

typedef struct list_s {
  struct list_s *next;
  void *data;
} list_t;

list_t *list_add(list_t *head, void *data);
int list_length(list_t *head);

#endif

