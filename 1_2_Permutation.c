/*
 * 1_2_Permutation.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>


#define TEST(_s1, _s2)   printf("[%s] vs [%s] --> %d\n", _s1, _s2, check_permutation(_s1, _s2));

int check_permutation(const char *str1, const char *str2)
{
  int i;
  int abc[30] = {0};
  const char *p;

  for (p = str1; (*p) != '\0'; abc[(*p) - 'a'] += 1, p++);
  for (p = str2; (*p) != '\0'; abc[(*p) - 'a'] -= 1, p++);

  for(i = 0; i < 30; i++) {
    if (abc[i] != 0) return 0;
  }

  return 1;
}


int main()
{

  TEST("hola", "adios");
  TEST("hola", "hola");
  TEST("hola", "aloh");

  return 0;
}

