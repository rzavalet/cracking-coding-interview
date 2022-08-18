/*
 * 1_6_StringCompression.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>

#define TEST(_str)  printf("[%s] -> [%s]\n", _str, compress(_str));

char buffer[1024] = {0};

int l10(int a) {
  int ctr = 0;

  while (a > 0) {
    a /= 10;
    ctr ++;
  }

  return ctr;
}

#if 0
/* I missunderstood the excercise. This function will compress a character iff
 * the compressed version for that char is smaller than the uncompressed
 * version.
 */
const char *compress(const char *str)
{
  const char *p = str;
  const char *q = str;
  char *b = buffer;
  int count = 0;
  int l = 0;

  while (*p) {
    for (q = p, count = 0; *q == *p; count++, q++);

    l = l10(count);

    if (l < count) {
      *b++ = *p;
      sprintf(b, "%d", count);
      b += l;
      p = q;
    }
    else {
      while (p != q) {
        *b = *p;
        p ++;
        b ++;
      }
    }
  }

  *b = '\0';

  return buffer;
}
#endif

const char *compress(const char *str)
{
  const char *p;
  const char *q;
  char *b;
  int count = 0;
  int l = 0;
  int ls1, ls2;

  /* Count original string */
  //for (ls1 = 0, p = str; *p; p++, ls1++);

  /* We have two pointers that initially point to the start of the original
   * string. One pointer traverses the string to count repetitions. The
   * second one "remembers" the character. 
   * We cheat by using sprintf() to convert the number to a string.
   */
  p = str;
  b = buffer;
  while (*p) {
    for (q = p, count = 0; *q == *p; count++, q++);

    *b++ = *p;
    l = sprintf(b, "%d", count);
    b += l;
    p = q;
  }

  *b = '\0';

  /* Count resulting string */
  //for (p = buffer, ls2 = 0; *p; p++, ls2 ++);

  ls1 = p - str;
  ls2 = b - buffer;

  if (ls1 > ls2) return buffer;
  else return str;
}

int main()
{
  TEST("aabcccccaaa");
  TEST("mama");
  TEST("aabccc");

  return 0;
}

