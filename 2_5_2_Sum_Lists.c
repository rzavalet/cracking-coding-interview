/*
 * 2_5_2_Sum_Lists.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * You have two numbers represented by a linked list, where each node contains
 * a single digit. The digits are stored in reverse order, such that the 1's
 * digit is at the head of the list. Write a function that adds the two numbers
 * and returns the sum as a linked list.
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *next;
};
typedef struct node node_t;

struct list {
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
  node_t *tmp;

  if (list == NULL) return;

  while (list->head) {
    tmp = list->head;
    list->head = list->head->next;

    free(tmp);
  }
  
  free(list);

  return;
}

void print_list(list_t *list)
{
  node_t *tmp;

  if (list == NULL) return;

  printf("List: [%p, %p]\n", list->head, list->tail);
  for (tmp = list->head; tmp; tmp = tmp->next) {
    printf("  %p: [%d, %p]\n", tmp, tmp->value, tmp->next);
  }

  return;
}

void append_to_list(list_t *list, int value)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->value = value;

  if (list->head == NULL) {
    list->head = node;
  }
  else {
    list->tail->next = node;
  }

  list->tail = node;
}

void prepend_to_list(list_t *list, int value)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->value = value;

  if (list->head == NULL) {
    list->tail = node;
  }
  else {
    node->next = list->head;
  }

  list->head = node;
}


#define abs(_x)  (_x >= 0 ? _x : - _x)

int sum_list_recursive(node_t *n1, node_t *n2, list_t *list3)
{
  int units = 0;
  int sum = 0;

  if (n1 == NULL && n2 == NULL) return 0;

  units = sum_list_recursive(n1->next, n2->next, list3);
  sum = units + n1->value + n2->value;
  units = sum % 10;

  prepend_to_list(list3, units);

  return (sum - units)/10;
}


list_t *sum_lists(list_t *list1, list_t *list2)
{
  int sz1 = 0;
  int sz2 = 0;
  int dif = 0;
  int units = 0;
  list_t *list3 = NULL;
  list_t *ltmp;
  node_t *tmp;

  /* Let's make the two lists of the same size */
  for (tmp = list1->head, sz1 = 0; tmp; tmp = tmp->next, sz1 ++);
  for (tmp = list2->head, sz2 = 0; tmp; tmp = tmp->next, sz2 ++);

  dif = abs(sz1 - sz2);

  if (sz1 > sz2) {
    ltmp = list2;
  }
  else if (sz2 > sz1) {
    ltmp = list1;
  }

  while (dif --) {
    prepend_to_list(ltmp, 0);
  }

  /* Sum the two lists recursively */
  list3 = alloc_list();
  units = sum_list_recursive(list1->head, list2->head, list3);
  if (units > 0) {
    prepend_to_list(list3, units);
  }


  return list3;
}


int main()
{
  list_t *list1 = NULL;
  list_t *list2 = NULL;
  list_t *list3 = NULL;

  list1 = alloc_list();
  list2 = alloc_list();

  append_to_list(list1, 6);
  append_to_list(list1, 1);
  append_to_list(list1, 7);
  append_to_list(list1, 8);

  append_to_list(list2, 2);
  append_to_list(list2, 9);
  append_to_list(list2, 5);

  print_list(list1);
  print_list(list2);

  list3 = sum_lists(list1, list2);
  print_list(list3);

  free_list(list1);
  free_list(list2);
  free_list(list3);

  return 0;
}

