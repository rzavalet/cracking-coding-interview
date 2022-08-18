/*
 * 2_7_Intersection.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Given two singly linked lists, determine if the two lists intersect. Return
 * the intersecting node. No that the intersection is defined based on
 * reference, not value. That is, if the kth node of the first linked list is
 * the exact same node (by reference) as the jth node of the second linked
 * list, then they are intersecting.
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
  int value;
  struct node *next;
};

typedef struct node node_t;

void print_nodes(node_t *node)
{
  node_t *tmp;

  printf("\nPrinting list with head %p\n", node);
  for (tmp = node; tmp; tmp = tmp->next) {
    printf("%p: [%d, %p]\n", tmp, tmp->value, tmp->next);
  }

  return;
}

/* 
 * If tail is the same, then there's an intersection.
 *
 * Compare the last k elements in both lists (k = min (len1, len2)) and find
 * the first match.
 */
node_t *check_intersection(node_t *head1, node_t *head2)
{
  int len1, len2;
  node_t *tmp;
  node_t *tmp1, *tmp2;
  node_t *tail1, *tail2;


  /* Find tails */
  for (tmp = head1; tmp; tmp = tmp->next, len1++) {
    if (tmp->next == NULL) {
      tail1 = tmp;
    }
  }

  for (tmp = head2; tmp; tmp = tmp->next, len2++) {
    if (tmp->next == NULL) {
      tail2 = tmp;
    }
  }

  printf("Is there intersection? %s\n", tail1 && tail1 == tail2 ? "YES" : "NO");

  /* Discard the initial elements of the longest list */
  if (len1 > len2) {
    tmp1 = head1;
    while (len1 -- > len2) {
      tmp1 = tmp1->next;
    }

    tmp2 = head2;
  }
  else if (len2 > len1) {
    tmp2 = head2;
    while (len2 -- > len1) {
      tmp2 = tmp2->next;
    }

    tmp1 = head1;
  }

  /* Find the first match */
  while (tmp1) {
    if (tmp1 == tmp2) {
      return tmp1;
      break;
    }

    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }

  return NULL;
}


int main()
{

  node_t nodes[10];
  node_t *res = NULL;

  nodes[0].value = 0;
  nodes[0].next = &nodes[1];

  nodes[1].value = 1;
  nodes[1].next = &nodes[2];

  nodes[2].value = 2;
  nodes[2].next = &nodes[3];

  nodes[3].value = 3;
  nodes[3].next = &nodes[4];

  nodes[4].value = 4;
  nodes[4].next = &nodes[5];

  nodes[5].value = 5;
  nodes[5].next = NULL;



  nodes[6].value = 6;
  nodes[6].next = &nodes[7];

  nodes[7].value = 7;
  nodes[7].next = &nodes[4];


  print_nodes(&nodes[0]);
  print_nodes(&nodes[6]);

  res = check_intersection(&nodes[0], &nodes[6]);

  if (res) {
    printf("\nIntersection at %p: [%d, %p]\n", res, res->value, res->next);
  }
  else {
    printf("\nNo intersection\n");
  }



  return 0;
}



