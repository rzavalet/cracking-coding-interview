/*
 * 4_0_BFS.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NUM_NODES 100
#define QUEUE_CAP 1024

struct queue
{
  int values[QUEUE_CAP];
  int num_elements;
  int tail;
  int head;
};
typedef struct queue queue_t;

void init_queue(queue_t *queue)
{
  memset(queue, 0, sizeof(*queue));
  return;
}

void enqueue(queue_t *queue, int value)
{
  if (queue->num_elements >= QUEUE_CAP) return;

  queue->values[queue->tail] = value;
  queue->tail = (1 + queue->tail) % QUEUE_CAP;
  queue->num_elements ++;

  return;
}

int dequeue(queue_t *queue)
{
  int tmp;

  if (queue->num_elements <= 0) return INT_MIN;

  tmp = queue->values[queue->head];
  queue->values[queue->head] = 0;
  queue->head = (1 + queue->head) % QUEUE_CAP;
  queue->num_elements --;

  return tmp;
}



struct node
{
  int value;
  struct node *next;
};
typedef struct node node_t;

node_t *add_node(node_t *head, int value)
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

  return;
}

struct graph
{
  node_t *adj_list[NUM_NODES];
};
typedef struct graph graph_t;

void add_arc(graph_t *graph, int n1, int n2)
{
  if (n1 >= NUM_NODES) return;

  graph->adj_list[n1] = add_node(graph->adj_list[n1], n2);
  return;
}

void free_graph(graph_t *graph)
{
  int i;

  for (i = 0; i < NUM_NODES; i++) {
    if (graph->adj_list[i] == NULL) continue;

    free_list(graph->adj_list[i]);
  }

  memset(graph, 0, sizeof(*graph));
  return;
}

void print(graph_t *graph)
{
  for (int i = 0; i < NUM_NODES; i++) {
    if (graph->adj_list[i] == NULL) continue;

    for (node_t *tmp = graph->adj_list[i]; tmp; tmp = tmp->next) {
        printf("%d -> %d\n", i, tmp->value);
    }

  }

  return;
}


int bfs(graph_t *graph, queue_t *queue, int *visited, int src, int dst)
{
  int rc = 0;
  int value;
  node_t *tmp;

  if (dst == src) return 1;

  enqueue(queue, src);
  visited[src] = 1;

  while ((value = dequeue(queue)) != INT_MIN) {

    if (visited[value]) continue;

    for (tmp = graph->adj_list[value]; tmp; tmp = tmp->next) {
      if (dst == tmp->value) return 1;

      if (visited[tmp->value]) continue;

      enqueue(queue, tmp->value);
      visited[tmp->value] = 1;
    }

  }

  return 0;
}


int main()
{
  graph_t graph;
  int rc = 0;
  int src, dst;
  int visited[NUM_NODES] = {0};
  queue_t queue;

  init_queue(&queue);

  memset(&graph, 0, sizeof(graph));

  add_arc(&graph, 1, 2);
  add_arc(&graph, 1, 3);
  add_arc(&graph, 2, 4);
  add_arc(&graph, 2, 5);
  add_arc(&graph, 3, 6);
  add_arc(&graph, 3, 7);
  add_arc(&graph, 4, 8);
  add_arc(&graph, 5, 8);
  add_arc(&graph, 6, 8);
  add_arc(&graph, 7, 8);

  print(&graph);

  src = 1;
  dst = 8;
  rc = bfs(&graph, &queue, visited, src, dst);
  printf("%d connects to %d? %s\n", src, dst, rc ? "YES" : "NO");
  
  src = 8;
  dst = 1;
  rc = bfs(&graph, &queue, visited, src, dst);
  printf("%d connects to %d? %s\n", src, dst, rc ? "YES" : "NO");

  free_graph(&graph);
  return 0; 
}

