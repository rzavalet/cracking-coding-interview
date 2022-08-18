/*
 * 2_1_Remove_Duplicates.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * DESCRIPTION:
 *  2.1 Remove all duplicate nodes from a linked list.
 *
 *  After checking the answer in the book, I realized I missunderstood the
 *  problem. My solutions below remove all nodes whose values are repeated.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG
#ifdef DEBUG
#define DBG(...)  printf(__VA_ARGS__)
#else
#define DBG(...)
#endif

struct node 
{
  struct node *next;
  int value;
};

typedef struct node node_t;

struct list
{
  node_t *head;
  node_t *tail;
};

typedef struct list list_t;


list_t *create_list()
{
  return calloc(1, sizeof(list_t));
}

list_t *free_list(list_t *list)
{
  node_t *target;

  if (list == NULL) return NULL;

  while(list->head != NULL) {
    target = list->head;
    list->head = list->head->next;
    free(target);
  }

  free(list);
  list = NULL;

  return list;
}

void append_node(list_t *list, int value)
{
  if (list == NULL) return;

  if (list->head == NULL) {
    list->head = calloc(1, sizeof(node_t));
    list->head->value = value;
    list->tail = list->head;
  }
  else {
    list->tail->next = calloc(1, sizeof(node_t));
    list->tail = list->tail->next;
    list->tail->value = value;
  }

  return;
}

void print_list(list_t *list)
{
  node_t *current = NULL;

  if (list == NULL) return;

  printf("(head: %p, tail: %p)\n", list->head, list->tail);
  current = list->head;

  while(current != NULL) {
    printf("[%p: %2d, %p] -> \n", current, current->value, current->next);
    current = current->next;
  }

  return;
}

/* 
 * Brute force: Use two pointers. The second one is used to find repeated
 * values.
 */
void remove_duplicate(list_t *list) 
{
  node_t **ind1 = NULL;
  node_t **ind2 = NULL;
  node_t *target = NULL;
  int value = -1;
  int found = 0;

  if (list == NULL) return;

  ind1 = &list->head;

  DBG("\n\n");

  while (*ind1 != NULL) {
    value = (*ind1)->value;
    ind2 = &(*ind1)->next;
    found = 0;

    while (*ind2 != NULL) {
      DBG("Looking for value %d\n", value);
      if ((*ind2)->value == value) {
        target = (*ind2);
        *ind2 = (*ind2)->next;
        DBG("(1) Removing %p\n", target);
        free(target);
        found = 1;
      }
      else {
        ind2 = &(*ind2)->next;
      }
      DBG("Next (%p)\n", *ind2);
    }

    if (found) {
      target = (*ind1);

      *ind1 = (*ind1)->next;
      DBG("(2) Removing %p\n", target);
      free(target);
    }
    else {
      ind1 = &(*ind1)->next;
    }
  }

  /* Restore the tail */
  for (list->tail = list->head; 
       list->tail != NULL && list->tail->next != NULL; 
       list->tail = list->tail->next);

  return;
}

/* 
 * Faster version. Uses an array as a hash table.
 */
void remove_duplicate2(list_t *list) 
{
  node_t **ind = NULL;
  node_t *target = NULL;

  int table[100] = {0};
  int i;

  for (target = list->head; target != NULL; table[target->value] ++, target = target->next);

  ind = &list->head;

  while (*ind != NULL) {
    if (table[(*ind)->value] > 1) {
      target = *ind;
      *ind = (*ind)->next;

      free(target);
    }
    else {
      ind = &(*ind)->next;
    }
  }

  for (list->tail = list->head;
       list->tail != NULL && list->tail->next != NULL;
       list->tail = list->tail->next);

}

int main()
{
  list_t *list = create_list();

  append_node(list, 1);
  append_node(list, 2);
  append_node(list, 3);
  append_node(list, 4);
  append_node(list, 5);
  append_node(list, 6);
  printf("\nPrinting initial list:\n");
  print_list(list);

  append_node(list, 1);
  append_node(list, 1);
  append_node(list, 2);
  append_node(list, 3);
  append_node(list, 4);
  append_node(list, 5);
  printf("\nPrinting list with repeated nodes:\n");
  print_list(list);

  remove_duplicate2(list);
  printf("\nPrinting list without duplicates:\n");
  print_list(list);

  list = free_list(list);

  return 0;
}

