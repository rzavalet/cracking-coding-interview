/*
 * 3_0_Stack.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
  int value;
  struct node *next;
};
typedef struct node node_t;

struct stack
{
  node_t *top;
};
typedef struct stack stack_t;


stack_t *alloc_stack()
{
  return calloc(1, sizeof(stack_t));
}

void stack_push(stack_t *stack, int value)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->value = value;

  node->next = stack->top;
  stack->top = node;

  return;
}

int stack_pop(stack_t *stack)
{
  node_t *tmp = NULL;
  int value = INT_MIN;

  if (stack->top) {
    tmp = stack->top;
    stack->top = tmp->next;
    value = tmp->value;
    free(tmp);
  }

  return value;
}

int peek_stack(stack_t *stack)
{
  int value = INT_MIN;

  if (stack->top) {
    value = stack->top->value;
  }

  return value;
}

void free_stack(stack_t *stack)
{
  node_t *tmp;

  while (stack->top) {
    tmp = stack->top;
    stack->top = stack->top->next;

    free(tmp);
  }

  free(stack);

  return;
}


int main()
{
  stack_t *stack = alloc_stack();
  int value;

  stack_push(stack, 1);
  stack_push(stack, 2);
  stack_push(stack, 3);
  stack_push(stack, 4);
  stack_push(stack, 5);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  value = stack_pop(stack);
  printf("value: %d\n", value);

  free_stack(stack);
}

