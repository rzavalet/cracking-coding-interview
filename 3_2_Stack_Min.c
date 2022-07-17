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

#define SIZE_STACK 10
struct node 
{
  int value;
  struct node *min;
};
typedef struct node node_t;

struct stack
{
  node_t array[SIZE_STACK];
  node_t *top;
};
typedef struct stack stack_t;

stack_t *alloc_stack()
{
  stack_t *stack = calloc(1, sizeof(stack_t));
  stack->top = stack->array;

  return stack;
}

void free_stack(stack_t *stack)
{
  free(stack);

  return;
}

/* The trick here is to check if the new element is smaller than the min in the
 * substack. If so, then this node is the new min. Otherwise, the substack's
 * min is still the min.
 */
void push(stack_t *stack, int value)
{
  if (stack->top >= stack->array + sizeof(stack->array) / sizeof(stack->array[0])) return;

  stack->top->value = value;
  stack->top->min = (stack->top == stack->array)
                                    ? stack->array
                                    : ((value < (stack->top - 1)->value)
                                          ? stack->top
                                          : (stack->top - 1)->min);
  stack->top ++;

  return;
}

int pop(stack_t *stack)
{
  if (stack->top == stack->array) return INT_MIN;

  return (--stack->top)->value;
}

int min(stack_t *stack)
{
  if (stack->top == stack->array) return INT_MAX;

  return (stack->top - 1)->min->value;
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





