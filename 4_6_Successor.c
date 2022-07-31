/*
 * 4_6_Successor.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define NUM_NODES 50
#define RND_RANGE 100

struct node
{
  int value;
  struct node *parent;
  struct node *left;
  struct node *right;
};
typedef struct node node_t;


void insert(node_t **node, int value, node_t *parent)
{
  if (*node == NULL) {
    *node = calloc(1, sizeof(node_t));
    (*node)->value = value;
    (*node)->parent = parent;
    return;
  }


  if (value < (*node)->value) {
    insert(&(*node)->left, value, *node);
  }
  else {
    insert(&(*node)->right, value, *node);
  }

  return;
}

void free_tree(node_t *node) 
{
  if (node == NULL) return;

  free_tree(node->left);
  free_tree(node->right);
  free(node);

  return;
}

void gen_random_tree(node_t **root, int num_values)
{
  int tmp;
  int map[RND_RANGE] = {0};

  for (int i = 0; i < num_values; i++) {

    while (map[(tmp = rand() % RND_RANGE)]);

    map[tmp] = 1;
    insert(root, tmp, NULL);
  }

  return;
}

node_t *get_random_node(node_t *root, int idx) 
{
  node_t *tmp = NULL;

  if (root == NULL) {
    return NULL;
  }

  if (idx == 0) {
    return root;
  }

  idx --;

  tmp = get_random_node(root->left, idx);
  if (tmp != NULL) return tmp;

  idx --;
  tmp = get_random_node(root->right, idx);
  if (tmp != NULL) return tmp;

  return NULL;
}

node_t *find_min(node_t *node)
{
  node_t *tmp = NULL;

  if (node == NULL) {
    return NULL;
  }
 
  for (tmp = node; tmp && tmp->left; tmp = tmp->left);

  return tmp;
}

node_t *find_successor(node_t *node, bool coming_from_right)
{
  node_t *tmp = NULL;

  if (node == NULL) {
    return NULL;
  }

  if (node->right != NULL) {
    return find_min(node->right);
  }

  for (tmp = node; tmp && tmp->parent && tmp == tmp->parent->right; tmp = tmp->parent);

  if (tmp == NULL || tmp->parent == NULL) {
    return NULL;
  }

  return tmp->parent;

  assert(0);

  return NULL;
}

void get_inorder_arr(node_t *root, int *arr, int *idx)
{
  if (root == NULL) return;

  get_inorder_arr(root->left, arr, idx);

  arr[*idx] = root->value;
  (*idx) ++;

  get_inorder_arr(root->right, arr, idx);

  return;
}

int search(int *arr, int sz_arr, int target)
{
  int low = 0, high = sz_arr - 1;
  int mid;

  while (low <= high) {
    mid = low + (high - low) / 2;
    if (target == arr[mid]) {
      if (mid < sz_arr - 1) return arr[mid + 1];
    }
    else if (target < arr[mid]) high = mid - 1;
    else low = mid + 1;
  }

  return INT_MIN;
}

void print_array(int *arr, int sz_arr)
{
  printf("Printing array: \n");
  for (int i = 0; i < sz_arr; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");

  return;
}

void print_dot_node(node_t * root, FILE *file, int *nullcount)
{
  if (root == NULL) {
    return;
  }

  if (root->left) {
    fprintf(file, "%d -> %d;\n", root->value, root->left->value); 
  }
  else {
    (*nullcount) ++;
    fprintf(file, "null%d [shape = point];\n", *nullcount);
    fprintf(file, "%d -> null%d;\n", root->value, *nullcount); 
  }

  if (root->right) {
    fprintf(file, "%d -> %d;\n", root->value, root->right->value); 
  }
  else {
    (*nullcount) ++;
    fprintf(file, "null%d [shape = point];\n", *nullcount);
    fprintf(file, "%d -> null%d;\n", root->value, *nullcount); 
  }

  print_dot_node(root->left, file, nullcount);
  print_dot_node(root->right, file, nullcount);

  return;
}

void print_dot(node_t *root)
{
  FILE *file = fopen("res/graph.dot", "w");
  int nullcount = 0;

  fprintf(file, "digraph BST {\n");

  print_dot_node(root, file, &nullcount);

  fprintf(file, "}\n");

  fclose(file);
}

int main()
{
  node_t *root = NULL;
  node_t *node = NULL;
  int *arr = NULL;
  int num1, num2, num3;
  int i = 0;

  srand(time(NULL));

  gen_random_tree(&root, NUM_NODES);
  print_dot(root);

  arr = calloc(NUM_NODES, sizeof(int));
  get_inorder_arr(root, arr, &i);

  node = get_random_node(root, rand() % 5);
  if (node == NULL) goto done;

  num1 = node->value;
  printf("Finding successor of %d\n", num1);

  node = find_successor(node, false);
  if (node == NULL) goto done;
  num2 = node->value;
  num3 = search(arr, NUM_NODES, num1);

  printf("Successor is %d [%d]\n", num2, num3);
  assert(num2 >= num1);

  assert(num2 == num3);

done:
  free_tree(root);
  free(arr);

  return 0;
}
