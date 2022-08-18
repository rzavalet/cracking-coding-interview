/*
 * 4_7_Build_Order.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * You are given a list of projects and a list of dependecies. All of a
 * project's dependecies must be build before the project is. Find a build
 * order that will allow the projects to be build. If there is no valid build
 * order, return an error.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <string.h>


struct graph
{
  bool **adj_mat;
  int *in_degree;
  int num_nodes;
};
typedef struct graph graph_t;

graph_t *create_graph(int num_nodes)
{
  graph_t *graph = calloc(1, sizeof(*graph));

  graph->num_nodes = num_nodes;
  graph->in_degree = calloc(num_nodes, sizeof(int));
  graph->adj_mat = calloc(num_nodes, sizeof(bool *));

  for (int i = 0; i < num_nodes; i++) {
    graph->adj_mat[i] = calloc(num_nodes, sizeof(bool));
  }
  
  srand(time(NULL));

  for (int i = 0; i < num_nodes; i++) {
    for (int j = 0; j < num_nodes - i; j++) {
      if (rand() % 100 < 15 && i != j) {
        graph->adj_mat[i][j] = true;
        graph->in_degree[j] ++;
      }
    }
  }

  return graph;
}

void destroy_graph(graph_t *graph)
{
  if (graph == NULL) return;

  for (int i = 0; i < graph->num_nodes; i++) {
    free(graph->adj_mat[i]);
  }

  free(graph->in_degree);
  free(graph->adj_mat);
  free(graph);

  return;
}


#define SIZE_ARR  1024
struct queue
{
  int array[SIZE_ARR];
  int num_elements;
  int tail;
  int head;
};
typedef struct queue queue_t;

void enqueue(queue_t *queue, int value)
{
  if (queue->num_elements >= SIZE_ARR) return;

  queue->array[queue->tail] = value;
  queue->tail = (queue->tail + 1) % SIZE_ARR;
  queue->num_elements ++;

  return;
}

int dequeue(queue_t *queue)
{
  int tmp;
  if (queue->num_elements <= 0) return INT_MIN;

  tmp = queue->array[queue->head];
  queue->head = (queue->head + 1) % SIZE_ARR;
  queue->num_elements --;

  return tmp;
}

bool is_empty(queue_t *queue)
{
  return (queue->num_elements == 0);
}



void topo_order2(graph_t *graph)
{
  queue_t queue = {0};
  int *order = calloc(graph->num_nodes, sizeof(int));
  int cur = 0;
  int *copy_indegree = calloc(graph->num_nodes, sizeof(int));
  int node;

  memcpy(copy_indegree, graph->in_degree, graph->num_nodes * sizeof(int));

  while (true) {
    for (int i = 0; i < graph->num_nodes; i++) {
      if (copy_indegree[i] == 0) {
        copy_indegree[i] --; // So that we don't enqueue it again
        enqueue(&queue, i);
      }
    }

    if (is_empty(&queue)) break;

    while ((node = dequeue(&queue)) != INT_MIN) {
      order[cur++] = node;
      for (int i = 0; i < graph->num_nodes; i++) {
        if (graph->adj_mat[node][i]) { // We are "removing" node "node", so,
                                       // decrement the in-degree of adjacent
                                       // nodes
          copy_indegree[i] --;
        }
      }

    }
  }

  for (int i = 0; i < graph->num_nodes; i++) {
    if (copy_indegree[i] > 0 ) {
      printf("No valid ordering. Found a cycle in node %d\n", i);
      goto done;
    }
  }

  for (int i = 0; i < graph->num_nodes; i++) {
    printf("%d, ", order[i]);
  }
  printf("\n");

done:
  free(order);
  free(copy_indegree);
  return;
}

bool dfs(graph_t *graph, int src_node, int *order, int *next, bool *visited, bool *in_stack)
{
  bool rc = false;
  visited[src_node] = true;
  in_stack[src_node] = true;
  printf("I am visiting node: %d\n", src_node);

  for (int i = 0; i < graph->num_nodes; i++) {
    if (graph->adj_mat[src_node][i]) {
      if (in_stack[i]) return false;

      if (!visited[i]) {
        rc = dfs(graph, i, order, next, visited, in_stack);
        if (rc == false) return rc;
      }
    }
  }

  -- (*next);
  order[*next] = src_node;
  in_stack[src_node] = false;
  return true;
}

void topo_order(graph_t *graph)
{
  int *order = calloc(graph->num_nodes, sizeof(int));
  int next = graph->num_nodes;
  bool *visited = calloc(graph->num_nodes, sizeof(bool));
  bool *in_stack = calloc(graph->num_nodes, sizeof(bool));
  bool rc = false;


  for (int i = 0; i < graph->num_nodes; i++) {
    if (visited[i] == 1) continue;

    rc = dfs(graph, i, order, &next, visited, in_stack);
    if (rc == false) {
      printf("No valid ordering. Found a cycle\n");
      goto done;
    }
  }

  for (int i = 0; i < graph->num_nodes; i++) {
    printf("%d, ", order[i]);
  }
  printf("\n");

done:
  free(visited);
  free(order);
  free(in_stack);

  return;
}

void print_graph(graph_t *graph)
{
  FILE *file = NULL;

  if (graph == NULL) return;

  file = fopen("res/graph.dot", "w");

  fprintf(file, "digraph {\n");
  for (int i = 0; i < graph->num_nodes; i++) {
    for (int j = 0; j < graph->num_nodes; j++) {
      if (graph->adj_mat[i][j]) {
        fprintf(file, "%d -> %d; \n", i, j);
      }
      else {
        fprintf(file, "%d; \n", i);
      }

    }
  }

  fprintf(file, "}\n");
  fclose(file);

  return;
}

int main()
{
  graph_t *graph = create_graph(10);

  print_graph(graph);

  topo_order2(graph);

  destroy_graph(graph);

  return 0;
}

