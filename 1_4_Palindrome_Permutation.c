/*
 * 1_4_Palindrome_Permutation.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>


#define TEST(_s)  printf("[%s] -> %s\n", _s, isPermutation(_s) ? "True" : "False")

int count_set_bits(long abc)
{
  int count = 0;

  while (abc) {
    abc &= (abc - 1);
    count ++;
  }

  return count;
}

int isPermutation(const char *str)
{
  int i;
  long abc = 0;
  const char *p;

  for (p = str; *p != '\0'; p++)
    if (*p != ' ') {
      if (*p >= 'a' && *p <= 'z')
        abc ^= (2 << (*p - 'a'));
      else if (*p >= 'A' && *p <= 'Z')
        abc ^= (2 << (*p - 'A'));
    }

  if (count_set_bits(abc) <= 1) return 1;
  else return 0;

}



int main()
{
  TEST("Tact Coa");
  TEST("Ala");
  TEST("Hola");
  TEST("Anita lava la tina");
  TEST("Jose Cuervo");
  TEST("A");
  TEST(" ");
}

