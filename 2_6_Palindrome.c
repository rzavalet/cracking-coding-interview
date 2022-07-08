/*
 * 2_6_Palindrome.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a function to check if a linked list is palindrome.
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
  char value;
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
  node_t *tmp;

  while (list->head) {
    tmp = list->head;
    list->head = tmp->next;

    free(tmp);
  }

  free(list);

  return;
}

void append_list(list_t *list, char value)
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

  return;
}

/* 
 * This is my solution. The book only checks up to half of the list.
 */
node_t *recursive_check(node_t *head, node_t *node, int *same)
{
  node_t *tmp;
  if (head == NULL) return node;

  tmp = recursive_check(head->next, node, same);

  if (tmp == NULL) return NULL;

  printf("Checking [%c] vs [%c]\n", head->value, tmp->value);
  if (head->value == tmp->value) {
    *same = 1;
    return tmp->next;
  }

  *same = 0;
  return NULL;
}

int main()
{
  int rc = 0;
  list_t *list = alloc_list();

  append_list(list, 'c');
  append_list(list, 'a');
  append_list(list, 'c');
  append_list(list, 'a');
  //append_list(list, 'c');

  (void) recursive_check(list->head, list->head, &rc);
  printf("Is palindrome? %s\n", rc ? "YES" : "NO");

  free_list(list);

  return 0;
}

