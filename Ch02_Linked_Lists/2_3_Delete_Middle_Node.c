/*
 * 2_3_Delete_Middle_Node.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement an algorithm to delete a node in the middle of a singly linked
 * list, given only access to that node.
 *
 */
#include <stdio.h>
#include <stdlib.h>


struct node 
{
  int value;
  struct node *next;
};
typedef struct node node_t;

struct list
{
  node_t *head;
  node_t *tail;
};
typedef struct list list_t;

list_t *alloc_list()
{
  return calloc(1, sizeof(list_t));
}

void free_list(list_t *list)
{
  node_t *cur, *tmp;

  cur = list->head;
  while (cur) {
    tmp = cur;
    cur = cur->next;

    free(tmp);
  }

  free(list);
}

void append_to_list(list_t *list, int value)
{
  node_t *new = calloc(1, sizeof(node_t));
  new->value = value;

  if (list->tail == NULL) {
    list->tail = new;
    list->head = new;
  }
  else {
    list->tail->next = new;
    list->tail = new;
  }
}

void print_list(list_t *list)
{
  node_t *cur = list->head;

  printf("[head: %p, tail: %p]\n", list->head, list->tail);

  while (cur) {
    printf("[%p] (value: %d, next: %p)\n", cur, cur->value, cur->next);
    cur = cur->next;
  }

}

void delete_mid_element(node_t *n)
{
  node_t **cur = &n;
  node_t *tmp;

  if (n == NULL) return;

  printf("Deleting [%p] (value: %d, next: %p)\n", n, n->value, n->next);

  if (*cur != NULL && (*cur)->next == NULL) {
    (*cur)->value = -1;
    return;
  }

  while (*cur != NULL && (*cur)->next != NULL) {
    (*cur)->value = (*cur)->next->value;
    cur = &(*cur)->next;
  }
  tmp = *cur;
  free(tmp);
  *cur = NULL;
  

}

int main()
{
  list_t *list = alloc_list();

  append_to_list(list, 1);
  append_to_list(list, 2);
  append_to_list(list, 3);
  append_to_list(list, 4);
  append_to_list(list, 5);
  append_to_list(list, 6);
  append_to_list(list, 7);
  append_to_list(list, 8);
  append_to_list(list, 9);
  append_to_list(list, 10);
  print_list(list);

  delete_mid_element(list->tail);

  print_list(list);

  free_list(list);
  return 0;
}





