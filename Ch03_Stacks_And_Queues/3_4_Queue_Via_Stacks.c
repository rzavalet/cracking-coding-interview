/*
 * 3_4_Queue_Via_Stacks.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a my queue class which implements a queue using two stacks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NUM_ITEMS 100

struct stack
{
  int array[NUM_ITEMS];
  int *top;
};
typedef struct stack stack_t;
void init_stack(stack_t *stack);
void push(stack_t *stack, int value);
int pop(stack_t *stack);

struct queue
{
  stack_t to_enqueue;
  stack_t to_dequeue;

  int enqueuing;
};
typedef struct queue queue_t;

queue_t *alloc_queue();
void free_queue(queue_t *queue);
void enqueue(queue_t *queue, int value);
int dequeue(queue_t *queue);


int main()
{
  int value = INT_MIN;
  queue_t *queue = alloc_queue();

  for (int i = 0; i < 20; i++) {
    enqueue(queue, i);
  }

  while ((value = dequeue(queue)) != INT_MIN) {
    printf("%d\n", value);
  }
  
  free_queue(queue);

  return 0;
}

void init_stack(stack_t *stack)
{
  memset(stack, 0, sizeof(*stack));
  stack->top = stack->array;

  return;
}

void push(stack_t *stack, int value)
{
  if (stack->top >= stack->array + sizeof(stack->array) / sizeof(stack->array[0])) return;

  *(stack->top ++) = value;

  return;
}

int pop(stack_t *stack)
{
  if (stack->top <= stack->array) return INT_MIN;

  return *(--stack->top);
}

queue_t *alloc_queue()
{
  queue_t *queue = calloc(1, sizeof(queue_t));

  init_stack(&queue->to_enqueue);
  init_stack(&queue->to_dequeue);
  queue->enqueuing = 1;

  return queue;
}

void free_queue(queue_t *queue)
{
  free(queue);

  return;
}

void enqueue(queue_t *queue, int value)
{
  if (queue->enqueuing == 0) {
    int value;

    while ((value = pop(&queue->to_dequeue)) != INT_MIN) {
      push(&queue->to_enqueue, value);
    }
  }

  queue->enqueuing = 1;
  push(&queue->to_enqueue, value);

  return;
}

int dequeue(queue_t *queue)
{
  if (queue->enqueuing == 1) {
    int value;

    while ((value = pop(&queue->to_enqueue)) != INT_MIN) {
      push(&queue->to_dequeue, value);
    }
  }

  queue->enqueuing = 0;
  return pop(&queue->to_dequeue);
}

