/*
 * 1_3_URLify.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>

#define TEST(_s)  \
  do {\
    strcpy(buffer, _s);\
    printf("[%s] -> [%s]\n", _s, URLify(buffer, strlen(_s))); \
  } while (0)

char *URLify(char *buffer, size_t len)
{
  char *p, *q, *f;
  int num_spaces;

  q = buffer + len;
  for (p = buffer, num_spaces = 0;  p < q; p++)
    if (*p == ' ') num_spaces ++;

  f = buffer + len + 2 * num_spaces;
  *f = '\0';
  for (p = buffer + len - 1, q = f - 1;
       p > buffer; 
       p --, q--) {
    if (*p == ' ') {
      *q-- = '0';
      *q-- = '2';
      *q = '%';
    }
    else {
      *q = *p;
    }
  }

  return buffer;
}

int main()
{
  char buffer[1024] = {0};

  TEST("Mr John Smith");
  TEST("Juana");
  TEST("Yo quiero luz de luna para mi noche triste");

}

