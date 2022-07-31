/*
 * utils.h
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

typedef struct treenode treenode_t;
typedef struct node node_t;
typedef struct list list_t;
typedef struct array_list array_list_t;

void          free_tree(treenode_t *root);
void          print_tree(treenode_t *root);
treenode_t *  gen_random_tree(int num_nodes);

list_t *create_list();
void    free_list(list_t *list);
list_t *duplicate_list(list_t *list);
void    print_list(list_t *list);
void    add_last(list_t *list, int value);
void    add_first(list_t *list, int value);
node_t *remove_first(list_t *list);
node_t *remove_last(list_t *list);
bool    is_empty(list_t *list);

array_list_t *create_array_list();
void          add_array_list(array_list_t *list, void *value);
void          free_array_list(array_list_t *list);

#endif /* !UTILS_H */
