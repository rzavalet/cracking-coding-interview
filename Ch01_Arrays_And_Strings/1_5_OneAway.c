/*
 * 1_5_OneAway.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <assert.h>

#define TEST(_s1, _s2)  \
  printf("[%s] vs [%s] -> one away? %s\n", _s1, _s2, one_away(_s1,_s2)? "TRUE" : "FALSE") \


#define ABS(x)    (x >= 0 ? x : -x)

/*
 * Let's distinguish three cases:
 *
 * 1) String lengths differ by more than 1 
 *      -> They must differ by more than one char.
 * 2) String lengths are of the same size 
 *      -> We can compare char by char and stop if
 *         two chars are different.
 * 3) String lengths differ by exactly one
 *      -> In this case we know for sure that they differ by at least 1. So, we
 *      need to find out if there's an extra character that differs.
 */
int one_away(const char *str1, const char *str2)
{
  const char *p, *q;
  int l1, l2;
  int are_different = 0;

  for (p = str1, l1 = 0; *p; l1++, p++);
  for (q = str1, l2 = 0; *q; l2++, q++);

  /* Case (1) */
  if (ABS(l1-l2) > 1) return 0;

  /* p holds the long string; q, the short one */
  if (l1 >= l2) {
    p = str1;
    q = str2;
  }
  else {
    p = str2;
    q = str1;
  }

  while (*p && *q) {
    if (*p == *q) {
      p++;
      q++;
    }
    else {
      if (are_different) return 0;
      are_different = 1;

      if (l1 == l2) {
        /* Case (2) */
        p++;
        q++;
      }
      else {
        /* Case (3) */
        p++;
      }
    }
  }

  return 1;

}


int main()
{
  TEST("pale", "pale");
  TEST("pale", "ple");
  TEST("pales", "pale");
  TEST("pale", "bale");
  TEST("pale", "bake");
  TEST("mexico", "micoex");
  TEST("mexico", "micoe");

  return 0;
}

