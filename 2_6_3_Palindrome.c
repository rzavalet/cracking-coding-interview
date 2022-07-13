/*
 * 2_6_3_Palindrome.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a function to check if a linked list is palindrome.
 */

#include <stdio.h>
#include <stdlib.h>

#if 0
#define DEBUG
#endif

#ifdef DEBUG
#define DBG(...)  printf(__VA_ARGS__)
#else
#define DBG(...)
#endif


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
}

void print_list(list_t *list)
{
  node_t *tmp;

  printf("[%p, %p]\n", list->head, list->tail);
  for (tmp = list->head; tmp; tmp = tmp->next) {
    printf("  %p: [%c, %p]\n", tmp, tmp->value, tmp->next);
  }

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

/* This is the book's recursive solution. My solution is shorter, however
 * it requires 2x recursive calls (compared to this solution). This
 * solution needs the size of the list, which feels a bit ackward to me. If you
 * need to iterate to find the size of the list, you could simply use a stack
 * to check the palindrome in one go. The extra space may be compensated with
 * the stack usage in the recursive case.
 */
int check_palindrome(node_t *node, int len, node_t **head)
{
  int rc = 0;

  if (len == 1) {
    DBG("The mid is: %p\n", node);
    *head = node->next;
    return 1;
  }
  if (len == 0) {
    DBG("The mid is: %p\n", node);
    *head = node;
    return 1;
  }

  rc = check_palindrome(node->next, len - 2, head);

  if (rc == 0) {
    return rc;
  }

  if (node->value == (*head)->value) {
    *head = node->next;
    return 1;
  }

  return 0;
}


int is_palindrome(list_t *list)
{
  int rc = 0;
  int len = 0;
  node_t *node = NULL;
  node_t *the_head = NULL;

  for (node = list->head; node; node = node->next, len ++);

  rc = check_palindrome(list->head, len, &the_head);

  return rc;
}

int main()
{
  int rc = 0;
  list_t *list = alloc_list();

  append_list(list, 'c');
  append_list(list, 'a');
  append_list(list, 'c');
  append_list(list, 'a');
  append_list(list, 'c');

  print_list(list);

  rc = is_palindrome(list);
  printf("Is palindrome? %s\n", rc ? "YES" : "NO");

  free_list(list);
}



