/*
 * 4_0_DFS.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NUM_NODES 100

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


int dfs(graph_t *graph, int *visited, int src, int dst)
{
  int rc = 0;
  node_t *tmp;

  if (src == dst) return 1;

  visited[src] = 1;
  for (tmp = graph->adj_list[src]; tmp; tmp = tmp->next) {
    if (visited[tmp->value]) continue;

    rc = dfs(graph, visited, tmp->value, dst);
    if (rc == 1) return rc;
  }

  return rc;
}


int main()
{
  graph_t graph;
  int rc = 0;
  int src, dst;
  int visited[NUM_NODES] = {0};

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
  rc = dfs(&graph, visited, src, dst);
  printf("%d connects to %d? %s\n", src, dst, rc ? "YES" : "NO");
  
  src = 8;
  dst = 1;
  rc = dfs(&graph, visited, src, dst);
  printf("%d connects to %d? %s\n", src, dst, rc ? "YES" : "NO");

  free_graph(&graph);
  return 0; 
}

