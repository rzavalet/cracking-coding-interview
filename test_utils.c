/*
 * test_utils.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>

#include "utils.h"

int main()
{
  treenode_t *root = gen_random_tree(10);
  print_tree(root);
  free_tree(root);
}

