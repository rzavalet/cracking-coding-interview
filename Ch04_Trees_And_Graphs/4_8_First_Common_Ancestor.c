/*
 * 4_8_First_Common_Ancestor.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Find the first common ancestor of two nodes in a binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
  int value;
  bool ancestor;
  struct node *left;
  struct node *right;
};
typedef struct node node_t;

void insert_node(node_t **node, int num_nodes, int cur_node)
{
  node_t *tmp;

  if (node == NULL) return;

  if (cur_node >= num_nodes) {
    *node = NULL;
    return;
  }

  tmp = calloc(1, sizeof(*tmp));

  tmp->value = cur_node;

  insert_node(&(tmp->left), num_nodes, 2 * cur_node + 1);
  insert_node(&(tmp->right), num_nodes, 2 * cur_node + 2);

  *node = tmp;

  return;
}

node_t *gen_random_tree(int num_nodes)
{
  srand(time(NULL));

  node_t *root = NULL;

  insert_node(&root, num_nodes, 0);

  return root;
}

void print_node(FILE *file, node_t *node, int *nullcount)
{
  if (node == NULL) return;

  if (node->left) {
    fprintf(file, "%d -> %d;\n", node->value, node->left->value);
  }
  else {
    (*nullcount) ++;
    fprintf(file, "null%d [shape = point];\n", *nullcount);
    fprintf(file, "%d -> null%d;\n", node->value, *nullcount);
  }

  if (node->right) {
    fprintf(file, "%d -> %d;\n", node->value, node->right->value);
  }
  else {
    (*nullcount) ++;
    fprintf(file, "null%d [shape = point];\n", *nullcount);
    fprintf(file, "%d -> null%d;\n", node->value, *nullcount);
  }

  print_node(file, node->left, nullcount);
  print_node(file, node->right, nullcount);

  return;
}

void print_tree(node_t *root)
{
  FILE *file = fopen("res/graph.dot", "w");
  int nullcount = 0;

  fprintf(file, "digraph BT { \n");
  print_node(file, root, &nullcount);
  fprintf(file, "}\n");

  fclose(file);

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

/* Mark all nodes in the path from <root> to <value>
 */
bool mark_ancestors(node_t *root, int value)
{
  bool mark = false;
  if (root == NULL) return false;

  /* When we find the value, mark it as "ancestor" and then return true. The
   * return code is used in the caller to mark itself as "ancestor" as well.
   */
  if (root->value == value) {
    root->ancestor = true;
    return true;
  }

  mark = mark_ancestors(root->left, value);
  if (mark) {
    root->ancestor = true;
    return mark;
  }

  mark = mark_ancestors(root->right, value);
  if (mark) {
    root->ancestor = true;
    return mark;
  }

  return false;
}

/* Traverse the tree in search of <value>. After finding the value, break the
 * recursion and pop up. In the way up, find the first node marked as
 * "ancestor". 
 */
bool find_ancestor(node_t *root, int value, int *ancestor)
{
  bool found = false;
  if (root == NULL) return false;

  if (root->value == value) {
    if (root->ancestor) {
      *ancestor = root->value;
    }
    return true;
  }

  found = find_ancestor(root->left, value, ancestor);
  if (found) {
    if (root->ancestor && *ancestor == INT_MIN) {
      *ancestor = root->value;
    }

    return true;
  }

  found = find_ancestor(root->right, value, ancestor);
  if (found) {
    if (root->ancestor && *ancestor == INT_MIN) {
      *ancestor = root->value;
    }

    return true;
  }

  return false;
}

/* In my solution, I assume that I don't have direct access to the node. So, I
 * need to traverse the tree and find the first element. Then, I mark the
 * ancestors recursively.
 *
 * Then, in a second step, I find the second node, and in the recursive call, I
 * find the first node marked in the path to the first node. 
 */
void find_common_ancestor(node_t *root, int v1, int v2)
{
  bool found = false;
  int ancestor = INT_MIN;

  (void) mark_ancestors(root, v1);

  found = find_ancestor(root, v2, &ancestor);
  if (found) {
    printf("Ancestor of %d and %d is: %d\n", v1, v2, ancestor);
  }
  else {
    printf("No common ancestor for %d and %d\n", v1, v2);
  }

  return;
}


int main()
{
  node_t *root = gen_random_tree(10);

  print_tree(root);

  find_common_ancestor(root, 5, 5);
  free_tree(root);
  
  return 0;
}

