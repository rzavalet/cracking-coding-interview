/*
 * 3_5_Sort_Stack.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Write a program to sort a stack such that the smalles items are on the top.
 * You can use an additional temporary stack, but you may not copy the elements
 * into any other data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define NUM_ITEMS 100
struct stack
{
  int array[NUM_ITEMS];
  int *top;
};
typedef struct stack stack_t;

stack_t *alloc_stack()
{
  stack_t *stack = calloc(1, sizeof(stack_t));
  stack->top = stack->array;
}

void free_stack(stack_t *stack)
{
  free(stack);

  return;
}

void push(stack_t *stack, int value)
{
  if (stack->top >= stack->array + sizeof(stack->array) / sizeof(stack->array[0])) return;

  *(stack->top) = value;
  stack->top ++;

  return;
}

int pop(stack_t *stack)
{
  int value;
  if (stack->top <= stack->array) return INT_MIN;

  -- stack->top;
  value = *stack->top;
  *stack->top = 0;
  return value;
}

int peek(stack_t *stack)
{
  if (stack->top <= stack->array) return INT_MIN;

  return *(stack->top - 1);
}


/* This is my solution. After looking into the book's solution, I realize that
 * we can do better. In my approach we pop and re-push the stack in search for
 * the minimum element. 
 */
stack_t *sort_stack(stack_t *stack)
{
  int cur_min = INT_MAX;
  int value;
  stack_t *aux_stack = alloc_stack();

  while ((value = peek(stack)) != INT_MIN) {
    int min = INT_MAX;

    while ((value = pop(stack)) != INT_MIN) {
      if (value < min) min = value;
      push(aux_stack, value);
    }

    while((value = peek(aux_stack)) != cur_min && value != INT_MIN) {
      value = pop(aux_stack);

      if (value != min) 
        push(stack, value);
    }

    cur_min = min;
    push(aux_stack, cur_min);
  }

  return aux_stack;
}

/* This is the book's solution.
 * 
 * Pop elements from the aux stack in search of the proper place for an item.
 */
stack_t *sort_stack2(stack_t *stack)
{
  int value;
  stack_t *aux_stack = alloc_stack();

  while ((value = peek(stack)) != INT_MIN) {
    value = pop(stack);

    /* Find the right position of value in the aux stack. Removed elements
     * while searching the right spot, are inserted to the original stack. 
     */
    int tmp;
    while ((tmp = peek(aux_stack)) > value) {
      tmp = pop(aux_stack);
      push(stack, tmp);
    }

    /* Push the value to this position in the aux stack */
    push(aux_stack, value);

  }
  
  return aux_stack;
}



int main()
{
  int value;
  stack_t *stack = alloc_stack();
  stack_t *sorted_stack = NULL;

  srandom(time(NULL));
  for (int i = 0; i < 10; i++) {
    push(stack, random() % 1000);
  }

  sorted_stack = sort_stack2(stack);

  while ((value = pop(sorted_stack)) != INT_MIN) {
    printf("%d\n", value);
  }

  free_stack(stack);
  free_stack(sorted_stack);

  return 0;
}

