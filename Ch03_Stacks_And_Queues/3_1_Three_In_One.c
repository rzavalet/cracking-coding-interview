/*
 * 3_1_Three_In_One.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_SIZE  9
#define NUM_STACKS  3
struct stack
{
  int big_array[STACK_SIZE];
  int start[NUM_STACKS];
  int top[NUM_STACKS];
};
typedef struct stack stack_t;

stack_t *alloc_stack()
{
  stack_t *stack = calloc(1, sizeof(stack_t));

  for (int i = 0; i < NUM_STACKS; i++) {
    stack->start[i] = stack->top[i] = i * (STACK_SIZE / NUM_STACKS);
    printf("%d: start = %d, top = %d\n", i, stack->start[i], stack->top[i]);
  }

  return stack;
}

void free_stack(stack_t *stack) 
{
  free(stack);
}


void push(stack_t *stack, int stack_num, int value)
{
  if (stack->top[stack_num] >= stack->start[stack_num] + STACK_SIZE / NUM_STACKS) return;

  stack->big_array[stack->top[stack_num]++] = value;
  return;
}

int pop(stack_t *stack, int stack_num)
{
  if (stack->start[stack_num] == stack->top[stack_num]) 
    return INT_MIN;

  return stack->big_array[--stack->top[stack_num]];
}

int main()
{
  int value;
  int stack_idx = 0;
  stack_t *stack = alloc_stack();

  push(stack, stack_idx, 1);
  push(stack, stack_idx, 2);
  push(stack, stack_idx, 3);

  stack_idx ++;

  push(stack, stack_idx, 11);
  push(stack, stack_idx, 12);
  push(stack, stack_idx, 13);

  stack_idx ++;

  push(stack, stack_idx, 21);
  push(stack, stack_idx, 22);
  push(stack, stack_idx, 23);

  for (int i = 0; i < 9; i++) {
    value = pop(stack, i / 3);
    printf("%d: Value: %d\n", i/3, value);
  }

#if 0
  for (int i = 0; i < STACK_SIZE; i++) {
    printf("[%d] Value: %d\n", i, stack->big_array[i]);
  }
#endif

  free_stack(stack);
}


