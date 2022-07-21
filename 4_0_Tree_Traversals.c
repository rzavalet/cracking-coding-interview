/*
 * 4_0_Tree_Traversals.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
  int value;
  struct node *right;
  struct node *left;
};
typedef struct node node_t;


node_t *alloc_node(int value)
{
  node_t *node = calloc(1, sizeof(node_t)); 
  node->value = value;
  return node;
}

void free_node(node_t *node)
{
  free(node);
}

void free_tree(node_t *root)
{
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free_node(root);
  return;
}

void insert_node(node_t **root, int value)
{
  node_t *node = NULL;

  if (*root == NULL) {
    *root = alloc_node(value);
  }
  else if (value > (*root)->value) {
    insert_node(&(*root)->right, value);
  }
  else {
    insert_node(&(*root)->left, value);
  }

  return;
}

void print_node(node_t *node)
{
  printf("%p: [%d, %p, %p]\n", node, node->value, node->right, node->left);
  return;
}

void preorder(node_t *root)
{
  if (root == NULL) return;

  print_node(root);
  preorder(root->left);
  preorder(root->right);
}

void postorder(node_t *root)
{
  if (root == NULL) return;

  postorder(root->left);
  postorder(root->right);
  print_node(root);
}

void inorder(node_t *root)
{
  if (root == NULL) return;

  inorder(root->left);
  print_node(root);
  inorder(root->right);
}

int main()
{
  srand(time(NULL));
  int value;
  node_t *root = NULL;

  for (int i = 0; i < 10; i++) {
    value = rand() % 1000;
    printf("Inserting: %d\n", value);
    insert_node(&root, value);
  }

  inorder(root);

  free_tree(root);

  return 0;
}

