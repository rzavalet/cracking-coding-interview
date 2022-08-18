/*
 * 4_10_Check_Subtree.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * T1 and T2 are two very large binary trees, with T1 much bigger than T2.
 * Create an algorithm to determine if T2 is a subtree of T1.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "utils.h"

treenode_t *find_node(treenode_t *root, int value)
{
  treenode_t *res = NULL;

  if (root == NULL) return NULL;

  if (root->value == value) return root;

  res = find_node(root->left, value);
  if (res != NULL) return res;

  res = find_node(root->right, value);
  if (res != NULL) return res;

  return NULL;
}


bool compare_trees(treenode_t *root1, treenode_t *root2)
{
  if (root1 == NULL && root2 == NULL) {
    return true;
  }

  if ((root1 == NULL && root2 != NULL) ||  (root1 != NULL && root2 == NULL)) return false;

  if (root1->value != root2->value) return false;

  return compare_trees(root1->left, root2->left) && compare_trees(root1->right, root2->right);
}

bool is_subtree(treenode_t *root1, treenode_t *root2)
{
  treenode_t *tmp = NULL;

  tmp = find_node(root1, root2->value);
  if (tmp == NULL) return false;

  return compare_trees(tmp, root2);
}



int main()
{
  int arr[100];
  treenode_t *T1;
  treenode_t *T2;
  bool res = false;

  srand(time(NULL));

  for (int i = 0; i < 100; i++) {
    arr[i] = rand() % 10000;
  }

  T1 = gen_tree_from_array(arr, 100);
  print_tree(T1);

  //T2 = find_node(T1, arr[rand() % 50]);
  //T2 = gen_random_tree(10);
  T2 = gen_tree_from_array(arr, 10);
  printf("Root of T2 is = %d\n", T2->value);

  res = is_subtree(T1, T2);
  printf("T2 is subtree of T1? %s\n", res ? "Yes" : "No");

  free_tree(T1);
  free_tree(T2);
}

