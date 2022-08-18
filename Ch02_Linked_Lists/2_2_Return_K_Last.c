/*
 * 2_2_Return_K_Last.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * 2.2 Return Kth to Last
 * Implement an algorithm to find the kth to last element of a singly linked
 * list.
 *
 * For my implementations, k=0 means the last element; k=1 means the
 * penultimate element; and so on.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if 0
#define DEBUG
#endif
#ifdef DEBUG
#define DBG(...)  printf(__VA_ARGS__)
#else
#define DBG(...)
#endif

#define k_to_last(_l, _k)  k_to_last3(_l, _k)

struct node {
  int value;
  struct node *next;
};
typedef struct node node_t;


struct list {
  node_t *head;
  node_t *tail;
};
typedef struct list list_t;

list_t *alloc_list()
{
  return calloc(1, sizeof(list_t));
}

void free_list(list_t *list)
{
  node_t *cur = list->head;
  node_t *tmp;

  while (cur != NULL) {
    tmp = cur;
    cur = cur->next;

    free(tmp);
  }

  free(list);

  return;
}

void append_to_list(list_t *list, int value)
{
  node_t *n = NULL;

  n = calloc(1, sizeof(node_t));
  n->value = value;

  if (list->tail == NULL) {
    list->tail = n;
    list->head = n;
  }
  else {
    list->tail->next = n;
    list->tail = n;
  }

  return;
}

void print_list(list_t *list)
{
  node_t *cur = list->head;

  printf("[head: %p, tail: %p]\n", list->head, list->tail);

  while (cur != NULL) {
    printf("[%p] (value: %d, next: %p) \n", cur, cur->value, cur->next);
    cur = cur->next;
  }

  return;
}

/*
 * Iterative version using two pointers
 */
node_t *k_to_last1(list_t *list, int k)
{
  node_t *p1 = NULL;
  node_t *p2 = NULL;
  int i;

  /* Advance p1 k positions */
  for (i=0, p1=list->head; i < k && p1 != NULL; i++, p1 = p1->next);

  if (p1 != NULL && i == k) {
    p2  = list->head;
    /* Find the last element. Notice that the last element is the one whose
     * next pointer points to NULL (Could have also checked against tail)
     */
    while (p1 != NULL && p1->next != NULL) {
      p1 = p1->next;
      p2 = p2->next;
    }
  }

  return p2;
}


/*
 * What I missed:
 *   - Instead of counting forward, I could have counted starting from the last
 *   recursion.
 *   - I could have leveraged the return value to return the node.
 *      - When we find the node, we return the current node.
 *      - After that, we return what ever the previous recursion returned.
 */
void find_k_to_last(node_t *cur, int *countp, int ith, int k, node_t **nodepp)
{
  if (cur == NULL) {
    return;
  }

  *countp += 1;
  ith += 1;

  DBG("[%p] is node number %d\n", cur, ith);

  find_k_to_last(cur->next, countp, ith, k, nodepp);

  DBG("[%p] is %d to last\n", cur, *countp - ith);

  if (*countp - ith == k) {
    *nodepp = cur; 
    DBG("[%p] is our guy\n", cur);
  }

}



/*
 * Recursive version
 */
node_t *k_to_last2(list_t *list, int k)
{
  int count = 0;
  int ith = 0;
  node_t *nodep = NULL;

  find_k_to_last(list->head, &count, ith, k, &nodep);

  return nodep;
}


/*-------------------------------------------
 * BEGIN: These are the book's solutions
 *------------------------------------------*/
// This is the recursive version
node_t *k_to_last_book(node_t *cur, int k, int *ith)
{
  node_t *tmp = NULL;

  if (cur == NULL) {
    return NULL;
  }

  tmp = k_to_last_book(cur->next, k, ith);
  *ith += 1; // Count starting from the last recursion.
  if (*ith == k) { // Return the ith element
    return cur;
  }

  return tmp; // After that, keep returning what the inner recursion gave.

}

node_t *k_to_last3(list_t *list, int k)
{
  int i = -1;

  return k_to_last_book(list->head, k, &i);
}



/*-------------------------------------------
 * END: These are the book's solutions
 *------------------------------------------*/

int main()
{
  list_t *l;
  node_t *n;
  int k;

  l = alloc_list();
  append_to_list(l, 10);
  append_to_list(l, 9);
  append_to_list(l, 8);
  append_to_list(l, 7);
  append_to_list(l, 6);
  append_to_list(l, 5);
  append_to_list(l, 4);
  append_to_list(l, 3);
  append_to_list(l, 2);
  append_to_list(l, 1);

  print_list(l);

  k = 5;
  n = k_to_last(l, k);
  printf("%d to last = [%p] %d\n", k, n, n ? n->value : -1);
  assert(n->value == k+1);

  k = 0;
  n = k_to_last(l, k);
  printf("%d to last = [%p] %d\n", k, n, n ? n->value : -1);
  assert(n->value == k+1);

  k = 1;
  n = k_to_last(l, k);
  printf("%d to last = [%p] %d\n", k, n, n ? n->value : -1);
  assert(n->value == k+1);

  k = 9;
  n = k_to_last(l, k);
  printf("%d to last = [%p] %d\n", k, n, n ? n->value : -1);
  assert(n->value == k+1);

  k = 10;
  n = k_to_last(l, k);
  printf("%d to last = [%p] %d\n", k, n, n ? n->value : -1);
  assert(n == NULL);

  free_list(l);

  return 0;
}
