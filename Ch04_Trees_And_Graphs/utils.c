/*
 * utils.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "utils.h"


void insert_treenode(treenode_t **root, int value)
{
  if (root == NULL) {
    return;
  }

  if (*root == NULL) {
    *root = calloc(1, sizeof(**root));
    (*root)->value = value;
    return;
  }

  if ((*root)->value < value) {
    insert_treenode(&(*root)->right, value);
  }
  else if ((*root)->value > value) {
    insert_treenode(&(*root)->left, value);
  }
  else {
    printf("Repeated nodes are not allowed\n");
  }

  return;
}

void free_tree(treenode_t *root)
{
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);

  return;
}

void print_tree_aux(treenode_t *root, FILE *file, int *null_count)
{
  if (root == NULL) return;

  if (root->left) {
    fprintf(file, "%d -> %d;\n", root->value, root->left->value);
  }
  else {
    (*null_count) ++;
    fprintf(file, "null%d [shape = point];\n", *null_count);
    fprintf(file, "%d -> null%d;\n", root->value, *null_count);
  }

  if (root->right) {
    fprintf(file, "%d -> %d;\n", root->value, root->right->value);
  }
  else {
    (*null_count) ++;
    fprintf(file, "null%d [shape = point];\n", *null_count);
    fprintf(file, "%d -> null%d;\n", root->value, *null_count);
  }

  print_tree_aux(root->left, file, null_count);
  print_tree_aux(root->right, file, null_count);

  return;
}

void print_tree(treenode_t *root)
{
  FILE *file = NULL;
  int null_count = 0;

  if (root == NULL) return;

  file = fopen("res/graph.dot", "w");
  fprintf(file, "digraph BST {\n");
  print_tree_aux(root, file, &null_count);
  fprintf(file, "}\n");
  fclose(file);

  return;
}

treenode_t *gen_random_tree(int num_nodes)
{
  srand(time(NULL));
  treenode_t *root = NULL;

  for (int i = 0; i < num_nodes; i++) {
    insert_treenode(&root, rand() % 1000);
  }

  return root;
}

treenode_t *gen_tree_from_array(int *arr, int sz_arr)
{
  srand(time(NULL));
  treenode_t *root = NULL;

  for (int i = 0; i < sz_arr; i++) {
    insert_treenode(&root, arr[i]);
  }

  return root;
}

void add_last(list_t *list, int value) 
{
  if (list == NULL) return;

  node_t *tmp = calloc(1, sizeof(node_t));
  tmp->value = value;

  if (list->head == NULL) {
    list->head = tmp;
  }
  else {
    list->tail->next = tmp;
    tmp->prev = list->tail;
  }

  list->tail = tmp;

  return;
}

void add_first(list_t *list, int value)
{
  if (list == NULL) return;

  node_t *tmp = calloc(1, sizeof(node_t));
  tmp->value = value;

  if (list->tail == NULL) {
    list->tail = tmp;
  }
  else {
    tmp->next = list->head;
    list->head->prev = tmp;
  }

  list->head = tmp;

  return;
}

node_t *remove_first(list_t *list)
{
  node_t *tmp = NULL;

  if (list == NULL) return NULL;
  if (list->head == NULL) return NULL;

  tmp = list->head;
  list->head = tmp->next;

  if (list->head == NULL) {
    list->tail = NULL;
  }
  else {
    list->head->prev = NULL;
  }

  return tmp;
}

node_t *remove_last(list_t *list)
{
  node_t *tmp = NULL;

  if (list == NULL) return NULL;

  if (list->tail == NULL) return NULL;

  tmp = list->tail;

  if (list->tail->prev) {
    list->tail->prev->next = NULL;
    list->tail = list->tail->prev;
  }
  else {
    list->tail = NULL;
    list->head = NULL;
  }

  return tmp;
}


list_t *create_list()
{
  return calloc(1, sizeof(list_t));
}

void free_list(list_t *list)
{
  node_t *tmp;

  if (list == NULL) return;

  while (list->head) {
    tmp = list->head;
    list->head = tmp->next;

    free(tmp);
  }

  free(list);

  return;
}

list_t *duplicate_list(list_t *list)
{
  node_t *tmp;
  list_t *new_list = create_list();

  if (list == NULL) return NULL;

  for (tmp = list->head; tmp; tmp = tmp->next) {
    add_last(new_list, tmp->value);
  }

  return new_list;
}

void print_list(list_t *list)
{
  if (list == NULL) return;

  for (node_t *tmp = list->head; tmp; tmp = tmp->next) {
    printf("%d -> ", tmp->value);
  }

  printf("NULL\n");

  return;
}

bool is_empty(list_t *list)
{
  if (list == NULL) return true;

  return list->head == NULL;
}


array_list_t *create_array_list()
{
  array_list_t *tmp = calloc(1, sizeof(*tmp));

  tmp->array = calloc(100, sizeof(void *));
  tmp->size = 100;
  return tmp;
}

void add_array_list(array_list_t *list, void *value)
{
  if (list == NULL) return;

  if (list->next_slot >= list->size) return;

  list->array[list->next_slot++] = value;

  return;
}

void free_array_list(array_list_t *list)
{
  if (list == NULL) return;

  free(list->array);
  free(list);

  return;
}


