/*
 * 2_0_Basic_Linked_List.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node *next;
  int data;
};

typedef struct node node_t;

node_t *append_to_list(node_t *head, int data) 
{
  node_t *new = NULL;
  node_t *tmp = NULL;

  new = malloc(sizeof(*new));
  new->data = data;
  new->next = NULL;

  if (head == NULL) return new;

  for (tmp = head;
       tmp->next != NULL; 
       tmp = tmp->next);

  tmp->next = new;

  return head;
}

node_t *delete_from_list(node_t *head, int data)
{
  node_t *tmp1 = NULL;
  node_t *tmp2 = NULL;

  if (head == NULL) return NULL;

  if (head->data == data) {
    tmp1 = head;
    head = head->next;
    free(tmp1);
    return head;
  }

  for (tmp2 = NULL, tmp1 = head; 
       tmp1 != NULL && tmp1->data != data; 
       tmp2 = tmp1, tmp1 = tmp1->next);

  if (tmp1 != NULL && tmp1->data == data) {
    tmp2->next = tmp1->next;
    free(tmp1);
  }

  return head;
}

/*
 * This is Torvalds' approach to deleting a node, aka "good taste".
 */
void delete_from_list2(node_t **headPP, int data) 
{
  node_t **tmp = NULL;
  node_t *target = NULL;

  if (headPP == NULL || *headPP == NULL) return;

  for (tmp = headPP; *tmp != NULL && (*tmp)->data != data; tmp = &((*tmp)->next));

  if (*tmp != NULL && (*tmp)->data == data) {
    target = *tmp;
    *tmp = (*tmp)->next;

    free(target);
  }
}


void print_list(node_t *head)
{
  while (head != NULL) {
    printf("[%5d] -> ", head->data);
    head = head->next;
  }

  printf("NULL\n");
}

int main()
{
  node_t *list = NULL;

  list = append_to_list(list, 1);
  list = append_to_list(list, 5);
  list = append_to_list(list, 2);
  list = append_to_list(list, 13);
  list = append_to_list(list, 7);
  list = append_to_list(list, 3);

  print_list(list);

#if 0
  list = delete_from_list(list, 50);
  list = delete_from_list(list, 1);
  list = delete_from_list(list, 3);
  list = delete_from_list(list, 2);
#else
  delete_from_list2(&list, 50);
  delete_from_list2(&list, 1);
  delete_from_list2(&list, 3);
  delete_from_list2(&list, 2);
#endif

  print_list(list);

  return 0;
}

