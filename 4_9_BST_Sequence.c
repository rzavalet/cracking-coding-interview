/*
 * 4_9_BST_Sequence.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * A binary search tree was created by traversing through an array from left to
 * right and inserting each element. Given a binary search tree with distinct
 * elements, print all possible arrays tath could have led to this tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

struct treenode
{
  int value;
  struct treenode *left;
  struct treenode *right;
};
typedef struct treenode treenode_t;

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

struct node 
{
  int value;
  struct node *prev;
  struct node *next;
};
typedef struct node node_t;

struct list
{
  node_t *head;
  node_t *tail;
};
typedef struct list list_t;

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


struct array_list
{
  void **array;
  int size;
  int next_slot;
};
typedef struct array_list array_list_t;

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



void interleave(list_t *l1, list_t *l2, array_list_t *results, list_t *prefix)
{
  node_t *tmp = NULL;
  node_t *tmp2 = NULL;
  list_t *new_list =  NULL;

  if (is_empty(l1) || is_empty(l2)) {
    list_t *result = duplicate_list(prefix);

    for (node_t *tmp = l1->head; tmp; tmp = tmp->next) {
      add_last(result, tmp->value);
    }

    for (node_t *tmp = l2->head; tmp; tmp = tmp->next) {
      add_last(result, tmp->value);
    }

    add_array_list(results, result);
    return;
  }

  tmp = remove_first(l1);
  if (tmp != NULL) {
    add_last(prefix, tmp->value);
    interleave(l1, l2, results, prefix);
    tmp2 = remove_last(prefix);
    add_first(l1, tmp->value);
    free(tmp);
    free(tmp2);
  }

  tmp = remove_first(l2);
  if (tmp != NULL) {
    add_last(prefix, tmp->value);
    interleave(l1, l2, results, prefix);
    tmp2 = remove_last(prefix);
    add_first(l2, tmp->value);
    free(tmp);
    free(tmp2);
  }

  return;
}


array_list_t *bst_sequence_aux(treenode_t *root)
{
  array_list_t *result = create_array_list();

  if (root == NULL) {
    list_t *tmp = create_list();
    add_array_list(result, tmp);
    return result;
  }

  list_t *prefix = create_list();
  add_last(prefix, root->value);

  array_list_t *leftSeq = bst_sequence_aux(root->left);
  array_list_t *rightSeq = bst_sequence_aux(root->right);

  for (int i = 0; i < leftSeq->next_slot; i++) {
    for (int j = 0; j < rightSeq->next_slot; j++) {
      array_list_t *interleaved = create_array_list();
      interleave(leftSeq->array[i],
                 rightSeq->array[j],
                 interleaved,
                 prefix);
      
      for(int k = 0; k < interleaved->next_slot; k++) {
        add_array_list(result, interleaved->array[k]);
      }
      free_array_list(interleaved);

    }
  }

  for (int i = 0; i < leftSeq->next_slot; i++) {
    free_list(leftSeq->array[i]);
    leftSeq->array[i] = NULL;
  }
  free_array_list(leftSeq);

  for (int j = 0; j < rightSeq->next_slot; j++) {
    free_list(rightSeq->array[j]);
    rightSeq->array[j] = NULL;
  }
  free_array_list(rightSeq);

  free_list(prefix);


  return result;
}


void bst_sequence(treenode_t *root)
{
  array_list_t *results;

  results = bst_sequence_aux(root);

  for (int i = 0; i < results->next_slot; i++) {
    print_list(results->array[i]);
    free_list(results->array[i]);
  }

  free_array_list(results);

  return;
}


int main() 
{
  treenode_t *root = gen_random_tree(4);
  print_tree(root);
  bst_sequence(root);
  free_tree(root);

  return 0;
}




