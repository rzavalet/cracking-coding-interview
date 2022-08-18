/*
 * 4_11_Random_Node.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Implement a binary tree class that provides:
 * 1) insert
 * 2) find
 * 3) delete
 * 4) getRandomNode
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>

struct treenode
{
  int value;
  int num_nodes;
  struct treenode *left;
  struct treenode *right;
};
typedef struct treenode treenode_t;

int insert(treenode_t **root, int value)
{
  int rc = 0;

  if (root == NULL) return 0;

  if (*root == NULL) {
    treenode_t *n = calloc(1, sizeof(*n));
    n->value = value;
    n->num_nodes = 1;
    *root = n;
    return 1;
  }

  if ((*root)->value > value) {
    rc = insert(&(*root)->left, value);
  }
  else if ((*root)->value < value) {
    rc = insert(&(*root)->right, value);
  }
  else {
    //printf("Can't insert repeated values\n");
  }

  (*root)->num_nodes += rc; 
  return rc;
}

void free_tree(treenode_t *root)
{
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);

  return;
}

void print_subtree(treenode_t *root, FILE *file, int *null_count)
{
  if (root == NULL) return;

  if (root->left) {
    fprintf(file, "%d [label=\"(%d, %d)\"];\n", root->value, root->value, root->num_nodes);
    fprintf(file, "%d -> %d;\n", root->value, root->left->value);
  }
  else {
    (*null_count) ++;
    fprintf(file, "%d [label=\"(%d, %d)\"];\n", root->value, root->value, root->num_nodes);
    fprintf(file, "null%d [shape = point];\n", *null_count);
    fprintf(file, "%d -> null%d;\n", root->value, *null_count);
  }

  if (root->right) {
    fprintf(file, "%d [label=\"(%d, %d)\"];\n", root->value, root->value, root->num_nodes);
    fprintf(file, "%d -> %d;\n", root->value, root->right->value);
  }
  else {
    (*null_count) ++;
    fprintf(file, "%d [label=\"(%d, %d)\"];\n", root->value, root->value, root->num_nodes);
    fprintf(file, "null%d [shape = point];\n", *null_count);
    fprintf(file, "%d -> null%d;\n", root->value, *null_count);
  }

  print_subtree(root->left, file, null_count);
  print_subtree(root->right, file, null_count);

}

void print_tree(treenode_t *root)
{
  int null_count = 0;
  FILE *file = fopen("res/graph.dot", "w");

  fprintf(file, "digraph BST {\n");
  fprintf(file, "forcelabels=true;\n");
  print_subtree(root, file, &null_count);
  fprintf(file, "}\n");

  fclose(file);
  return;
}


treenode_t *get_random_node(treenode_t *root, int random_node)
{
  int to_left = 0;
  int to_right = 0;
  if (root == NULL) return NULL;

  if (root->left) {
    to_left = root->left->num_nodes;
  }
  if (root->right) {
    to_right = root->right->num_nodes;
  }

  if (random_node <= to_left) {
    return get_random_node(root->left, random_node);
  }
  else if (random_node == to_left + 1) {
    return root;
  }
  else {
    return get_random_node(root->right, random_node - to_left - 1);
  }

}


treenode_t *find(treenode_t *root, int target)
{
  if (root == NULL) return NULL;

  if (root->value == target) {
    return root;
  }
  else if (target < root->value) {
    return find(root->left, target);
  }
  else {
    return find(root->right, target);
  }
}

treenode_t *find_successor(treenode_t *root)
{
  treenode_t *tmp = NULL;

  for (tmp = root; tmp && tmp->left; tmp = tmp->left);

  return tmp;
} 

treenode_t *delete(treenode_t *root, int target)
{
  if (root == NULL) return NULL;

  if (target < root->value) {
    root->left = delete(root->left, target);
  }
  else if (target > root->value) {
    root->right = delete(root->right, target);
  }
  else {
    if (root->left == NULL) {
      treenode_t *tmp = root->right;
      free(root);

      root = tmp;
    }
    else if (root->right == NULL) {
      treenode_t *tmp = root->left;
      free(root);

      root = tmp;
    }
    else {
      treenode_t *tmp = find_successor(root->right);
      
      root->value = tmp->value;

      root->right = delete(root->right, tmp->value);
    }
  }

  return root;
}



int main()
{
  treenode_t *root = NULL;

  srand(time(NULL));

  for (int i = 0; i < 50; i++) {
    insert(&root, rand() % 100);
  }

  print_tree(root);

  int target = rand() % root->num_nodes;
  treenode_t *n1 = get_random_node(root, target);
  printf("Random node %d: %s\n", target, n1 ? "YES" : "NO");

  target = rand() % 100;
  n1 = find(root, target);
  printf("Found node %d: %s\n", target, n1 ? "YES" : "NO");

  target = rand() % 100;
  printf("Deleting node %d\n", target);
  root = delete(root, target);

  print_tree(root);

  free_tree(root);

  return 0;
}

