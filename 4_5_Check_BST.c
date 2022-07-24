/*
 * 4_5_Check_BST.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Check if a binary tree is a BST
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <string.h>


struct treenode
{
  int value;

  struct treenode *left;
  struct treenode *right;
};
typedef struct treenode treenode_t;


void insert(treenode_t **node, int value)
{
  if (*node == NULL) {
    *node = calloc(1, sizeof(**node));
    (*node)->value = value;
    return;
  }

  if (value > (*node)->value) {
    insert(&(*node)->right, value);
  }
  else {
    insert(&(*node)->left, value);
  }

  return;
}

void free_tree(treenode_t *node)
{
  if (node == NULL) return;

  free_tree(node->left);
  free_tree(node->right);
  free(node);

  return;
}


void gen_random_bst_tree(treenode_t **node, int num_nodes)
{
  srand(time(NULL));

  for (int i = 0; i < num_nodes; i++) {
    insert(node, rand() % 1000);
  }

  return;
}

#define left_child(x)   ( ((x) << 1) + 1)
#define right_child(x)   ( ((x) << 1) + 2)

void insert2(treenode_t **node, int cur_node, int *values, int num_nodes)
{
  treenode_t *tmp;

  if (cur_node >= num_nodes) {
    *node = NULL;
    return;
  }

  if (values[cur_node] == INT_MIN) {
    *node = NULL;
    return;
  }
  
  tmp = calloc(1, sizeof(*tmp));
  tmp->value = values[cur_node];

  insert2(&tmp->left, left_child(cur_node), values, num_nodes);
  insert2(&tmp->right, right_child(cur_node), values, num_nodes);

  *node = tmp;

  return;
}

void gen_random_tree(treenode_t **node, int num_nodes)
{
  int *array = calloc(num_nodes, sizeof(int));
  srand(time(NULL));

  for (int i = 0; i < num_nodes; i++) {
    array[i] = rand() % 1000;
  }

  insert2(node, 0, array, num_nodes);

  free(array);

  return;
}

bool check_bst2(treenode_t *root, int min, int max)
{
  if (root == NULL) {
    return true;
  }

  if (min > root->value  || root->value >= max) {
    return false;
  }

  if (!check_bst2(root->left, min, root->value)) {
    return false;
  }

  if (!check_bst2(root->right, root->value, max)) {
    return false;
  }

  return true;
}

bool check_bst(treenode_t *root)
{
  check_bst2(root, INT_MIN, INT_MAX);
}

int main()
{
  treenode_t *root;
  bool rc = 0;

  root = NULL;
  gen_random_tree(&root, 10);
  rc = check_bst(root);
  printf("Is BST ? %s\n", rc ? "YES" : "NO");
  assert(rc == false);
  free_tree(root);
  

  root = NULL;
  gen_random_bst_tree(&root, 10);
  rc = check_bst(root);
  printf("Is BST ? %s\n", rc ? "YES" : "NO");
  assert(rc == true);
  free_tree(root);

  /* My initial approach failed to verify the following. In a bst, we must make
   * sure that all elements in the left subtree are less than the root; and all
   * elements in the right subtree are greater than the root. Simply checking
   * the left and right children is not enought. */
  int array[7] = {20, 10, 30, INT_MIN, 25, INT_MIN, INT_MIN};
  root = NULL;
  insert2(&root, 0, array, 7);
  rc = check_bst(root);
  printf("Is BST ? %s\n", rc ? "YES" : "NO");
  assert(rc == false);
  free_tree(root);

  return 0;
}

