/*
 * 4_4_Check_Balanced.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a function to check if a binary tree is balanced.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

struct treenode
{
  int value;
  struct treenode *left;
  struct treenode *right;
};
typedef struct treenode treenode_t;


#define abs(a)  ((a) > 0 ? (a) : -(a))
#define max(a, b) ((a) > (b) ? (a) : (b))

bool check_height(treenode_t *root, int *height)
{
  int height_left;
  int height_right;
  bool rc;

  if (root == NULL) {
    *height = 0;
    return true;
  }

  rc = check_height(root->left, &height_left);
  if (rc == false) return rc;

  rc = check_height(root->right, &height_right);
  if (rc == false) return rc;

  if (abs(height_left - height_right) > 1) return false;

  *height = 1 + max(height_left, height_right);
  return true;
}


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


void insert_balanced(treenode_t **root, int min, int max)
{
  int mid;

  if (min > max) return;

  mid = min + (max - min) / 2;
  insert(root, mid);

  insert_balanced(root, min, mid - 1);
  insert_balanced(root, mid + 1, max);

  return;
}

treenode_t *gen_balanced_tree(int num_nodes)
{
  treenode_t *root = NULL;

  insert_balanced(&root, 0, num_nodes);

  return root;
}


treenode_t *gen_random_tree(int num_nodes)
{
  treenode_t *root = NULL;
  srand(time(NULL));

  for (int i = 0; i < num_nodes; i++) {
    insert(&root, rand() % 1000);
  }

  return root;
}


int main()
{
  int height = 0;
  bool rc;
  treenode_t *r1;

  r1 = gen_random_tree(10);
  rc = check_height(r1, &height);
  free_tree(r1);
  assert(rc == 0); // it is very unlikely to end up with a balanced tree here.

  printf("Is balanced? %s\n", rc ? "YES" : "NO");


  r1 = gen_balanced_tree(10);
  rc = check_height(r1, &height);
  free_tree(r1);
  assert(rc == 1);

  printf("Is balanced? %s\n", rc ? "YES" : "NO");

  return 0;
}



