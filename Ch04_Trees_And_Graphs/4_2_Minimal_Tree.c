/*
 * 4_2_Minimal_Tree.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Given a sorted (increasing order) array with unit integer elements, write an
 * algorithm to create a binary search tree with minimal height.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node
{
  int value;
  struct node *left;
  struct node *right;
};
typedef struct node node_t;

void min_tree(node_t **node, int *array, int low, int high)
{
  node_t *tmp;
  if (low > high) return;

  tmp = calloc(1, sizeof(node_t));
  *node = tmp;
  int mid = low + (high - low) / 2;
  tmp->value = array[mid];
  min_tree(&tmp->left, array, low, mid-1);
  min_tree(&tmp->right, array, mid + 1, high);


  return;
}

void free_tree(node_t *root)
{
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);

  return;
}


void print_inorder(node_t *root)
{
  if (root == NULL) return;

  print_inorder(root->left);
  printf("%d\n", root->value);
  print_inorder(root->right);

  return;
}


#define NUM_ITEMS 20

int main()
{
  node_t *root = NULL;
  int array[NUM_ITEMS];

  for (int i = 0; i < NUM_ITEMS; i++) {
    array[i] = i;
  }

  min_tree(&root, array, 0, NUM_ITEMS - 1);

  printf("Root: %d\n", root->value);
  print_inorder(root);

  free_tree(root);

  return 0;
}

