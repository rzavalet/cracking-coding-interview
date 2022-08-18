/*
 * 4_3_List_Of_Depths.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Given a binary tree, design an algorithm which creates a linked list of all
 * nodes at each depth.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

struct nodetree
{
  int value;
  struct nodetree *left;
  struct nodetree *right;
};
typedef struct nodetree nodetree_t;

struct node
{
  int value;
  struct node *next;
};
typedef struct node node_t;

void insert(nodetree_t **root, int value)
{
  if (*root == NULL) {
    *root = calloc(1, sizeof(nodetree_t));
    (*root)->value = value;
    return;
  }

  if (value <= (*root)->value) {
    insert(&(*root)->left, value);
  }
  else {
    insert(&(*root)->right, value);
  }

  return;
}

void free_tree(nodetree_t *root)
{
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);
  return;
}

void print_inorder(nodetree_t *root)
{
  if (root == NULL) return;

  print_inorder(root->left);
  printf("%d\n", root->value);
  print_inorder(root->right);

  return;
}

node_t *push(node_t *head, int value)
{
  node_t *tmp = calloc(1, sizeof(node_t));
  tmp->value = value;
  tmp->next = head;

  return tmp;
}

void free_list(node_t *head)
{
  node_t *tmp;

  while (head) {
    tmp = head;
    head = head->next;

    free(tmp);
  }

  return;
}


/* Just do a tree traversal and pass in the level. At each level we add the
 * node to the appropriate list. */
void list_depths(nodetree_t *root, node_t **lists, int level)
{
  if (root == NULL) return;

  lists[level] = push(lists[level], root->value);

  list_depths(root->left, lists, level + 1);
  list_depths(root->right, lists, level + 1);

  return;
}


#define NUM_LEVELS 50
int main()
{
  nodetree_t *root = NULL;
  node_t *lists[NUM_LEVELS] = {0};

  srand(time(NULL));

  for (int i = 0; i < 20; i++) {
    insert(&root, rand() % 1000);
  }

  print_inorder(root);

  list_depths(root, lists, 0);

  for (int i = 0; i < NUM_LEVELS; i ++) {

    if (lists[i] == NULL) continue;

    printf("Level %d...\n", i);

    node_t *tmp;

    for (tmp = lists[i]; tmp; tmp = tmp->next) {
      printf("%d, ", tmp->value);
    }
    printf("\n\n");
  }

  for (int i = 0; i < NUM_LEVELS; i++) {
    free_list(lists[i]);
  }

  free_tree(root);

  return 0;
}

