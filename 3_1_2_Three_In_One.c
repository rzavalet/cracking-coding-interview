/*
 * 3_1_2_Three_In_One.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement three stacks using a single array.
 * This version allows the stack to continue growing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_STACKS 3
#define INITIAL_SIZE  10
#define NUM_PUSHES 99

struct stack {
  int *big_array;
  int sz_array;

  int top[NUM_STACKS];
  int base[NUM_STACKS];
};
typedef struct stack stack_t;

stack_t *alloc_stack()
{
  stack_t *stack = calloc(1, sizeof(stack_t));

  stack->sz_array = INITIAL_SIZE;
  stack->big_array = calloc(INITIAL_SIZE, sizeof(int));

  for (int i = 0; i < NUM_STACKS; i++) {
    stack->top[i] = stack->base[i] = i * (stack->sz_array / NUM_STACKS);
  }

  return stack;
}

void free_stack(stack_t *stack)
{
  free(stack->big_array);
  free(stack);

  return;
}

void grow(stack_t *stack)
{
  int i, j;
  int new_base;
  int new_top;
  int *new_array;

  new_array = calloc(stack->sz_array << 1, sizeof(int));
  stack->sz_array <<= 1;
  printf("Resizing to %d\n", stack->sz_array);

  for (i = NUM_STACKS - 1; i >= 0; i--) {
    new_base = i * (stack->sz_array / NUM_STACKS);
    new_top = new_base;

    for (j = stack->base[i]; j < stack->top[i]; j++, new_top ++) {
      new_array[new_top] = stack->big_array[j];
    }
    stack->base[i] = new_base;
    stack->top[i] = new_top;
  }

  free(stack->big_array);
  stack->big_array = new_array;

  return;
}

void print_array(stack_t *stack)
{
  for (int i = 0; i < stack->sz_array; i++) {
    printf("%d, ", stack->big_array[i]);
  }
  printf("\n");

  return;
}


void push(stack_t *stack, int num_stack, int value)
{
  if (stack->top[num_stack] >= stack->base[num_stack] + (stack->sz_array / NUM_STACKS)) {
    grow(stack);
  }

  stack->big_array[stack->top[num_stack]++] = value;
}

int pop(stack_t *stack, int num_stack)
{
  if (stack->top[num_stack] == stack->base[num_stack]) 
    return INT_MIN;

  return stack->big_array[--stack->top[num_stack]];
}



int main()
{
  stack_t *stack = alloc_stack();


  for (int i = 0; i <= NUM_PUSHES; i++) {
    push(stack, i % 3, i);
    print_array(stack);
  }

  for (int i = NUM_PUSHES; i >= 0; i --) {
    int j = pop(stack, i % 3);
    printf("[%d] %d\n", i%3, j);
  }

  free_stack(stack);

  return 0;
}









