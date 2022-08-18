/*
 * 1_7_RotateMatrix.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>

int rotateMatrix(int n, short *matrix)
{
  int i, j, k;
  int start, end;
  short tmp;

  start = 0;
  end = n-1;

  while (end > start) {

    for (i = start, j = 0; i < end; j++, i++) {
      /* Swap top and right */
      tmp = *(matrix + i * n + end);
      *(matrix + i * n + end) = *(matrix + start * n + i);
      *(matrix + start * n + i) = tmp;

      /* Swap top and botom */
      tmp = *(matrix + end * n + end - j);
      *(matrix + end * n + end - j) = *(matrix + start * n + i);
      *(matrix + start * n + i) = tmp;

      /* Swap top and left */
      tmp = *(matrix + (end - j) * n + start);
      *(matrix + (end - j) * n + start) = *(matrix + start * n + i);
      *(matrix + start * n + i) = tmp;
    }


    start ++;
    end --;
  }
}

/* This is my implementation of the book's solution.
 * Less swaping is required if we rotate elements in counter clockwise
 * direction.
 */
int rotateMatrix2(int n, short *matrix)
{
  int i, j, k;
  int start, end;
  short tmp;

  start = 0;
  end = n-1;

  while (end > start) {

    for (i = start, j = 0; i < end; j++, i++) {
      tmp = *(matrix + start * n + i);

      /* top */
      *(matrix + start * n + i) = *(matrix + (end - j) * n + start);

      /* left */
      *(matrix + (end - j) * n + start) = *(matrix + end * n + end - j);

      /* bottom */
      *(matrix + end * n + end - j) = *(matrix + i * n + end);

      /* right */
      *(matrix + i * n + end) = tmp;
    }


    start ++;
    end --;
  }
}

int printMatrix(int n, short *matrix)
{
  int i,j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf(" %3d", *(matrix + i * n + j));
    }
    printf("\n");
  }
}

int main()
{
  short matrix1[4][4] = {
                          {  1,  2,  3,  4 },
                          {  5,  6,  7,  8 },
                          {  9, 10, 11, 12 },
                          { 13, 14, 15, 16 },
                       };

  short matrix2[5][5] = {
                          {  1,  2,  3,  4,  5 },
                          {  6,  7,  8,  9, 10 },
                          { 11, 12, 13, 14, 15 },
                          { 16, 17, 18, 19, 20 },
                          { 21, 22, 23, 24, 25 }
                       };

  printf("\n\nMatrix before:\n");
  printMatrix(4, (short *)matrix1);
  rotateMatrix2(4, (short *)matrix1);
  printf("\n\nMatrix after:\n");
  printMatrix(4, (short *)matrix1);

  printf("\n\nMatrix before:\n");
  printMatrix(5, (short *)matrix2);
  rotateMatrix2(5, (short *)matrix2);
  printf("\n\nMatrix after:\n");
  printMatrix(5, (short *)matrix2);


  return 0;
}

