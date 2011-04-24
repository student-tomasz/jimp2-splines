#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "point_list.h"
#include "list.h"
#include "point.h"
#include "epsilon.h"
#include "io.h"

static int point_list_compare(const list_t *lp, const list_t *rp);

list_t *point_list_add(list_t *head, double x, double y)
{
  list_t *new_node = malloc(sizeof(*new_node));
  new_node->data = point_new(x, y);
  new_node->next = NULL;

  if (!head) {
    return new_node;
  }

  list_t *prev, *node;
  for (prev = NULL, node = head; node != NULL; prev = node, node = node->next) {
    int cmp = point_list_compare(new_node, node);
    if (cmp == 1)
      continue;
    else if (cmp == 0)
      return head;
    else if (cmp == -1) {
      new_node->next = node;
      if (prev) prev->next = new_node;
      return head;
    }
  }
  prev->next = new_node;
  return head;
}

void point_list_free(list_t *head)
{
  while (head) {
    list_t *next = head->next;
    point_free((point_t *)head->data);
    free(head);
    head = next;
  }
}

char *point_list_to_str(const list_t *head)
{
  char *str = "";
  const list_t *node;
  for (node = head; node; node = node->next) {
    asprintf(&str, "%s%g,%g ", str, ((point_t *)node->data)->x, ((point_t *)node->data)->y);
  }
  return str;
}

static int point_list_compare(const list_t *lp, const list_t *rp)
{
  point_t *l = (point_t *)lp->data;
  point_t *r = (point_t *)rp->data;

  if (is_equal(l->x, r->x))
    return 0;
  else if (l->x > r->x)
    return 1;
  else
    return -1;
}

