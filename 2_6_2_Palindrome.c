/*
 * 2_6_2_Palindrome.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a function to check if a linked list is palindrome.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
  char value;
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
  node_t *tmp = NULL;

  while (list->head) {
    tmp = list->head;
    list->head = tmp->next;

    free(tmp);
  }
  
  free(list);
  return;
}

void append_list(list_t *list, int value)
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

void print_list(list_t *list)
{
  node_t *tmp;
  if (list == NULL) return;

  printf("[%p, %p] \n", list->head, list->tail);

  for (tmp = list->head; tmp; tmp = tmp->next) {
    printf("   %p: [%d, %p]\n", tmp, tmp->value, tmp->next);
  }

  return;
}


struct stack {
  int values[128];
  int top;
};

typedef struct stack stack_t;

stack_t *alloc_stack() {
  return calloc(1, sizeof(stack_t));
}

void push(stack_t *stack, int value)
{
  if (stack->top >= sizeof(stack->values)) return;

  stack->values[stack->top++] = value; 
  return;
}

int pop(stack_t *stack)
{
  if (stack->top <= 0) return INT_MIN;

  return stack->values[-- stack->top];
}

void free_stack(stack_t *stack)
{
  free(stack);

  return;
}


/* This version of the solution uses a stack to hold up to half the linked
 * list. If we pop elements from the stack, those elements should match the
 * remaining of the list.
 */
int is_palindrome(list_t *list)
{
  int rc = 0;
  int value = 0;
  node_t *p1, *p2;
  stack_t *stack = alloc_stack();

  p1 = list->head;
  p2 = list->head;

  /* Push half the list to the stack */
  while (p1 && p1->next) {
    push(stack, p2->value);

    p2 = p2->next;
    p1 = p1->next->next;
  }

  /* Skip the middle element */
  if (p1) {
    p2 = p2->next;
  }


  /* Compare the remainder of the list with what we have in the stack */
  while (p2) {
    value = pop(stack); 
    if (value != p2->value) goto done;
    p2 = p2->next;
  }

  rc = 1;

done:
  free_stack(stack);
  return rc;
}



int main()
{
  list_t *list = alloc_list();
  int rc = 0;

  append_list(list, 'c');
  append_list(list, 'a');
  append_list(list, 'c');
  append_list(list, 'a');
  append_list(list, 'c');
  //append_list(list, 'a');

  print_list(list);

  rc = is_palindrome(list);
  printf("Is palindrome? %s\n", rc ? "YES" : "NO");

  free_list(list);

  return 0;
}

