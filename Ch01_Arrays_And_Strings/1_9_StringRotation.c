/*
 * 1_9_StringRotation.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEST(_str1, _str2)  \
  printf("[%s] vs [%s] -> is rotation? %s\n", _str1, _str2, string_rotation(_str1, _str2) ? "TRUE" : "FALSE")

int is_substring(const char *haystack, const char *needle)
{
  if (strstr(haystack, needle)) return 1;
  return 0;
}

/* This is my implementation of the book's solution. It is a nice observation
 * that the problem can be reduced to find xy in yxyx 
 */
int string_rotation(const char *str1, const char *str2)
{
  const char *p;
  char *buffer = NULL;
  int l1, l2;
  int rc;

  for (p=str1,l1=0; *p; p++,l1++);
  for (p=str2,l2=0; *p; p++,l2++);

  if (l1 != l2) return 0;

  buffer = malloc(2*l1 + 1);
  assert(buffer);

  strcpy(buffer,str1);
  strcpy(buffer + l1,str1);
  
  rc = is_substring(buffer, str2);
  
  free(buffer);

  return rc;
}

int main()
{

  TEST("waterbottle", "erbottlewat");
  TEST("erbottlewat", "waterbottle");
  TEST("waterbottle", "erbottlewa");
  TEST("erbottlewa","waterbottle");
  TEST("holahola", "hola");
  TEST("hola","holahola");
  TEST("hola", "laho");
  TEST("laho","hola");
  TEST("","");

  return 0;
}
