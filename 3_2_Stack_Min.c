/*
 * 3_2_Stack_Min.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Design a stack that in addition to push and pop, has a function min which
 * returns the minimum element.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node 
{
  int value;
  struct node *min;
};
typedef struct node node_t;

struct stack
{
  node_t array[100];

  int top;
};
typedef struct stack stack_t;

stack_t *alloc_stack()
{
  return calloc(1, sizeof(stack_t));
}

void free_stack(stack_t *stack)
{
  free(stack);
}

void push(stack_t *stack, int value)
{
  if (stack->top >= sizeof(stack->array) / sizeof(stack->array[0])) return;

  stack->array[stack->top].value = value;
  stack->array[stack->top].min = (stack->top == 0 )
                                    ? &stack->array[stack->top] 
                                    : ((value < stack->array[stack->top - 1].value)
                                          ? &stack->array[stack->top]
                                          : stack->array[stack->top - 1].min);
  stack->top ++;
}

int pop(stack_t *stack)
{
  if (stack->top <= 0) return INT_MIN;

  return stack->array[--stack->top].value;
}

int min(stack_t *stack)
{
  if (stack->top <= 0) return INT_MAX;

  return stack->array[stack->top - 1].min->value;
}


int main()
{
  stack_t *stack = alloc_stack();

  push(stack, 10);
  push(stack, 9);
  push(stack, 8);
  push(stack, 7);
  push(stack, 6);
  push(stack, 5);
  push(stack, 2);
  push(stack, 3);
  push(stack, 4);
  push(stack, 1);
  push(stack, 2);

  do {
    printf("Min: %d\n", min(stack));
  } while (pop(stack) != INT_MIN);

  free_stack(stack);

  return 0;
}





