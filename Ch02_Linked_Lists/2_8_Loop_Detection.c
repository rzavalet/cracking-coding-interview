/*
 * 2_8_Loop_Detection.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Given a circular linked list, implement an algorithm that returns the node
 * at the begining of the loop.
 */
#include <stdio.h>
#include <stdlib.h>

struct node
{
  int value;
  struct node *next;
};
typedef struct node node_t;

void init_nodes(int *a, node_t *nodes, int num_nodes) 
{
  int i;

  for (i = 0; i < num_nodes; i++) {
    nodes[i].value = a[i];
    nodes[i].next = &nodes[(i+1) % num_nodes];
  }

  return;
}

/* This is the book's solution */
node_t *find_start_loop(node_t *head)
{
  node_t *fast, *slow;

  fast = head;
  slow = head;

  /* Find the matching point. This point is k positions before the start of the
   * loop. But we don't know yet the value of k */
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;

    if (fast == slow) break;
  }

  if (fast != slow) return NULL;

  /* We now that the start of the loop is also k positions after the start of
   * the list. So, move the two pointers one by one until they match. That's
   * the start of the loop */
  for (fast = head; fast != slow; fast = fast->next, slow = slow->next);

  return fast;
}


int main()
{
  node_t nodes[10];
  node_t *start_loop = NULL;
  int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  init_nodes(values, nodes, sizeof(nodes) / sizeof(node_t));
  nodes[9].next = &nodes[2];

  start_loop = find_start_loop(&nodes[0]);

  if (start_loop)
    printf("Start of loop is at node with number: %d\n", start_loop->value);
  else
    printf("There's no loop\n");

  return 0;
}

