/*
 * 3_0_Queue.c
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

struct queue
{
  node_t *head;
  node_t *tail;
};
typedef struct queue queue_t;

queue_t *alloc_queue()
{
  return calloc(1, sizeof(queue_t));
}

void add_queue(queue_t *queue, int value)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->value = value;

  if (queue->head == NULL) {
    queue->head = node;
  }
  else {
    queue->tail->next = node;
  }

  queue->tail = node;

  return;
}

int remove_queue(queue_t *queue)
{
  node_t *tmp;
  int value = INT_MIN;

  if (queue->head) {
    tmp = queue->head;

    if (queue->tail == queue->head) {
      queue->tail = NULL;
    }

    queue->head = tmp->next;
    value = tmp->value;

    free(tmp);
  }

  return value;

}

void free_queue(queue_t *queue)
{
  node_t *tmp;

  while (queue->head) {
    tmp = queue->head;
    queue->head = tmp->next;

    free(tmp);
  }

  free(queue);

  return;
}


int main()
{
  int value;
  queue_t *queue = alloc_queue();

  add_queue(queue, 1);
  add_queue(queue, 2);
  add_queue(queue, 3);
  add_queue(queue, 4);
  add_queue(queue, 5);

  value = remove_queue(queue);
  printf("Value: %d\n", value);

  value = remove_queue(queue);
  printf("Value: %d\n", value);

  value = remove_queue(queue);
  printf("Value: %d\n", value);

  value = remove_queue(queue);
  printf("Value: %d\n", value);

  value = remove_queue(queue);
  printf("Value: %d\n", value);

  value = remove_queue(queue);
  printf("Value: %d\n", value);


  free_queue(queue);
}


