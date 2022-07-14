/*
 * 2_4_Partition.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Write code to partition a linked list around a value k.
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

void append_list(list_t *list, node_t *node)
{
  if (list->head == NULL) {
    list->head = node;
  }
  else {
    list->tail->next = node;
  }

  list->tail = node;
  node->next = NULL;

  return;
}

void prepend_list(list_t *list, node_t *node)
{
  if (list->head == NULL) {
    list->tail = node;
  }
  else {
    node->next = list->head;
  }

  list->head = node;

  return;
}


void init_list(list_t *list, int *values, node_t *nodes, int num_nodes)
{
  int i;

  list->head = &nodes[0];
  list->tail = &nodes[num_nodes - 1];

  for (i = 0; i < num_nodes; i++) {
    nodes[i].value = values[i];
    nodes[i].next = i < num_nodes - 1 ? &nodes[i+1] : NULL;
  }

  return;
}

void print_list(node_t *head)
{
  node_t *tmp;

  for (tmp = head; tmp; tmp = tmp->next) {
    printf("%p : [%d, %p]\n", tmp, tmp->value, tmp->next);
  }

  return;
}

/* Move elements greater than the pivot to the tail;
 * move elementes smaller than the pivot to the head
 */
void partition(list_t *list, node_t *partition_node)
{
  int before = 1;
  node_t **tmp = &list->head;
  node_t *aux;

  /* Move elements greater than the pivot to the tail */
  while (*tmp && *tmp != partition_node) {
    if ((*tmp)->value > partition_node->value) {
      aux = *tmp;
      *tmp = aux->next;

      append_list(list, aux);
    }
    else {
      tmp = &(*tmp)->next;
    }
  }

  /* Move elementes smaller than the pivot to the head */
  while (*tmp) {
    if ((*tmp)->value < partition_node->value) {
      aux = *tmp;
      *tmp = aux->next;

      prepend_list(list, aux);
    }
    else {
      tmp = &(*tmp)->next;
    }
  }

  return;
}


int main()
{
  node_t nodes[10];
  node_t *head = NULL;
  int values[7] = {3, 5, 8, 5, 10, 2, 1};
  list_t list;

  init_list(&list, values, nodes, sizeof(values)/sizeof(values[0]));
  print_list(list.head);

  partition(&list, &nodes[3]);
  print_list(list.head);

  return 0;
}


