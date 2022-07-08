/*
 * 2_5_Sum_Lists.c
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

/*
 * This function assumes that the numbers are stored in reverse order.
 */
list_t *sum_lists(list_t *l1, list_t *l2)
{
  node_t *n1 = l1->head;
  node_t *n2 = l2->head;
  list_t *l3;
  int partial_sum = 0;
  int sumand = 0;
  int rest = 0;

  l3 = alloc_list();

  while (n1 != NULL && n2 != NULL) {
    partial_sum = n1->value + n2->value + rest;
    rest = partial_sum / 10;
    sumand = partial_sum % 10;

    append_to_list(l3, sumand);

    n1 = n1->next;
    n2 = n2->next;
  }

  while (n1 != NULL) {
    partial_sum = n1->value + rest;
    rest = partial_sum / 10;
    sumand = partial_sum % 10;

    append_to_list(l3, sumand);

    n1 = n1->next;
  }

  while (n2 != NULL) {
    partial_sum = n2->value + rest;
    rest = partial_sum / 10;
    sumand = partial_sum % 10;

    append_to_list(l3, sumand);

    n2 = n2->next;
  }
  
  if (rest > 0) {
    append_to_list(l3, rest);
  }

  return l3;

}


int main()
{
  list_t *l1, *l2, *l3;

  l1 = alloc_list();
  append_to_list(l1, 7);
  append_to_list(l1, 1);
  append_to_list(l1, 6);
  print_list(l1);

  l2 = alloc_list();
  append_to_list(l2, 5);
  append_to_list(l2, 9);
  append_to_list(l2, 2);
  print_list(l2);

  l3 = sum_lists(l1, l2);
  print_list(l3);

  free_list(l1);
  free_list(l2);
  free_list(l3);

  return 0;
}








