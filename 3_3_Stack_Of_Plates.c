/*
 * 3_3_Stack_Of_Plates.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implemente a set of stacks that offers these operations:
 *
 *    - SetOfStacks.push()
 *    - SetOfStacks.pop()
 *    - SetOfStacks.popAt(int index)
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


#define SIZE_STACK  5
#define NUM_STACKS  3

struct stack
{
  int array[SIZE_STACK];
  int *top;
};
typedef struct stack stack_t;

int push(stack_t *stack, int value);
int pop(stack_t *stack);

struct setOfStacks
{
  stack_t arrayOfStacks[NUM_STACKS];
  stack_t *curStack;
};
typedef struct setOfStacks setOfStacks_t;

setOfStacks_t *alloc_setOfStacks();
void free_setOfStacks(setOfStacks_t *sostacks);
void push_sostacks(setOfStacks_t *sostacks, int value);
int pop_sostacks(setOfStacks_t *sostacks);
int popAt_sostacks(setOfStacks_t *sostacks, unsigned int idxStack);

int main()
{
  int value;
  setOfStacks_t *sostacks = alloc_setOfStacks();

  for (int i = 0; i < SIZE_STACK * NUM_STACKS; i++) {
    push_sostacks(sostacks, i);
  }

  printf("%d\n", popAt_sostacks(sostacks, 0));
  printf("%d\n", popAt_sostacks(sostacks, 1));
  printf("%d\n", popAt_sostacks(sostacks, 2));

  while ((value = pop_sostacks(sostacks)) != INT_MIN) {
    printf("%d\n", value);
  }


  free_setOfStacks(sostacks);

  return 0;
}

void init_stack(stack_t *stack)
{
  memset(stack->array, 0, sizeof(stack->array));
  stack->top = stack->array;
}


int push(stack_t *stack, int value)
{
  if (stack->top >= stack->array + sizeof(stack->array) / sizeof(stack->array[0])) return 1;

  *(stack->top ++) = value;
  return 0;
}

int pop(stack_t *stack)
{
  if (stack->top == stack->array) return INT_MIN;

  return *(-- stack->top);
}

setOfStacks_t *alloc_setOfStacks()
{
  setOfStacks_t *sostacks = calloc(1, sizeof(setOfStacks_t));

  for (int i = 0; i < NUM_STACKS; i++) {
    init_stack(sostacks->arrayOfStacks + i);
  }

  sostacks->curStack = sostacks->arrayOfStacks;

  return sostacks;
}

void free_setOfStacks(setOfStacks_t *sostacks)
{
  free(sostacks);
  return;
}

void push_sostacks(setOfStacks_t *sostacks, int value)
{
  int rc = 0;

  rc = push(sostacks->curStack, value);
  if (rc == 0) return;

  if (sostacks->curStack >= sostacks->arrayOfStacks + sizeof(sostacks->arrayOfStacks) / sizeof(sostacks->arrayOfStacks[0])) return;

  push(++sostacks->curStack, value);

  return;
}

int pop_sostacks(setOfStacks_t *sostacks)
{
  int value = INT_MIN;

  value = pop(sostacks->curStack);
  if (value != INT_MIN) return value;

  if (sostacks->curStack == sostacks->arrayOfStacks) return INT_MIN;

  return pop(--sostacks->curStack);
}

int popAt_sostacks(setOfStacks_t *sostacks, unsigned int idxStack)
{
  if (idxStack >= sizeof(sostacks->arrayOfStacks) / sizeof(sostacks->arrayOfStacks[0])) return INT_MIN;

  return pop(sostacks->arrayOfStacks + idxStack);
}


















