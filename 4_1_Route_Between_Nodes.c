/*
 * 4_1_Route_Between_Nodes.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Given a directed graph, design an algorithm to find out whether there is a
 * route between nodes;
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct node
{
  int value;
  struct node *next;
};
typedef struct node node_t;

node_t *add(node_t *head, int value)
{
  node_t *tmp = calloc(1, sizeof(node_t));
  tmp->value = value;
  tmp->next = head;

  return tmp;
}

void free_list(node_t *head)
{
  node_t *tmp;

  while (head) {
    tmp = head;
    head = tmp->next;
    free(tmp);
  }
}

#define NUM_NODES 10
struct graph
{
  node_t *adj_list[NUM_NODES];
};
typedef struct graph graph_t;

void init_graph(graph_t *graph)
{
  memset(graph, 0, sizeof(*graph));
}

void add_arc(graph_t *graph, int n1, int n2)
{
  graph->adj_list[n1] = add(graph->adj_list[n1], n2); 
}

void print_graph(graph_t *graph)
{
  for (int i = 0; i < NUM_NODES; i++) {
    for (node_t *tmp = graph->adj_list[i]; tmp; tmp = tmp->next) {
      printf("%d->%d\n", i, tmp->value);
    }
  }
}

void free_graph(graph_t *graph)
{
  for (int i = 0; i < NUM_NODES; i++) {
    free_list(graph->adj_list[i]);
  }
}

#define SIZE_QUEUE  100
struct queue
{
  int array[SIZE_QUEUE];

  int front;
  int rear;
  int numElements;
};
typedef struct queue queue_t;

void init_queue(queue_t *queue)
{
  memset(queue, 0, sizeof(*queue));
}

void enqueue(queue_t *queue, int value)
{
  if (queue->numElements >= SIZE_QUEUE) return;

  queue->array[queue->rear] = value;
  queue->rear = (1 + queue->rear) % SIZE_QUEUE;
  queue->numElements++;
}

int dequeue(queue_t *queue)
{
  if (queue->numElements <= 0) return INT_MIN;

  int tmp = queue->array[queue->front];
  queue->front = (1 + queue->front) % SIZE_QUEUE;
  queue->numElements --;

  return tmp;
}


/* BFS will find the shortest path */
int route2(graph_t *graph, int *visited, queue_t *queue, int src, int dst)
{
  int value;

  if (src == dst) return 1;

  visited[src] = 1;
  enqueue(queue, src);

  while ((value = dequeue(queue)) != INT_MIN) {

    for (node_t *tmp = graph->adj_list[value]; tmp; tmp = tmp->next) {
      if (dst == tmp->value) return 1;

      if (visited[tmp->value]) continue;

      visited[tmp->value] = 1;

      enqueue(queue, tmp->value);
    }
  }

  return 0;

}

/* The simplest implementation for me is dfs, as the code is simple using
 * recursion */
int route(graph_t *graph, int *visited, int src, int dst)
{
  node_t *tmp;
  int rc = 0;

  visited[src] = 1;
  if (src == dst) return 1;

  for (tmp = graph->adj_list[src]; tmp; tmp = tmp->next) {
    if (visited[tmp->value]) continue;

    printf("Analyzing from %d to %d\n", tmp->value, dst);
    rc = route(graph, visited, tmp->value, dst);
    if (rc == 1) return 1;
  }

  return 0;

}


int main()
{
  graph_t graph;
  int visited[NUM_NODES] = {0};
  queue_t queue;

  init_graph(&graph);
  init_queue(&queue);

  add_arc(&graph, 1, 2);
  add_arc(&graph, 1, 3);
  add_arc(&graph, 3, 4);
  add_arc(&graph, 1, 4);
  add_arc(&graph, 4, 5);
  add_arc(&graph, 4, 6);
  add_arc(&graph, 5, 6);
  
  print_graph(&graph);

  int src = 2, dst = 5;
  printf("Is there route between %d and %d? %s\n", 
      src, dst, route2(&graph, visited, &queue, src, dst) ? "YES": "NO");

  free_graph(&graph);
}




