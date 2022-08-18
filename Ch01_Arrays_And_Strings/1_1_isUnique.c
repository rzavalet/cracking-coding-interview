/*
 * 1_1_isUnique.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <assert.h>
#include <time.h>

#define str(s) #s
#define xstr(s) str(s)
#define TEST(_str, _f1, _f2)  \
do {\
  int res = _f1(_str); \
  int res2 = _f2(_str); \
  printf("%s --> %d\n", _str, res);\
  assert(res == res2);\
} while (0)



int isUnique(const char *string) 
{
  const char *p, *q;

  if (string[0] != '\0' && string[1] == '\0') return 1;

  for (p = string; *p != '\0'; p++) {
    for (q = p + 1; *q != '\0'; q++) {
      if (*p == *q) return 0;
    }
  }

  return 1;
}

int isUnique2(const char *string)
{
  char alphabet[100] = {0};
  const char *p;

  for (p = string; *p != '\0'; p++) {
    if (alphabet[(*p) - 'a'] > 0) return 0;
    alphabet[(*p) - 'a'] += 1;
  }

  return 1;
}

int main() 
{
  FILE *f = NULL;
  char buffer[128];
  struct timespec tstart = {0}, tend = {0};
  double diff;
  static const char *fname = "long_dict.txt";


//  f = fopen("words_alpha.txt", "r");
//  while (fgets(buffer, sizeof(buffer), f) != NULL) {
//    TEST(buffer, isUnique, isUnique2);
//  }
//
//  fclose(f);
  
  f = fopen(fname, "r");
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    isUnique(buffer);
  }
  clock_gettime(CLOCK_MONOTONIC, &tend);
  diff = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
  printf("Elapsed time with isUnique(): %.2lf\n", diff);
  fclose(f);

  f = fopen(fname, "r");
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    isUnique2(buffer);
  }
  clock_gettime(CLOCK_MONOTONIC, &tend);
  diff = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
  printf("Elapsed time with isUnique2(): %.2lf\n", diff);
  fclose(f);


  return 0;
}
