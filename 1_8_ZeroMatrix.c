/*
 * 1_8_ZeroMatrix.c
 * Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>


/* Use these as queues to save the position of zeros */
int hcols[128] = {0};
int hrows[128] = {0};


/* Accumulate all x and y where 0's are present. Then use the collected x and y
 * to decide which rows/columns to zero out. */
int zero_matrix(int rows, int cols, short *matrix) 
{
  int i,j;
  int k = 0;
  int row, col;

  /* Find all zeros */
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      if (*(matrix + i * rows + j) == 0) {
        hrows[k] = i;
        hcols[k] = j;
        k ++;
      }
    }
  }

  /* Zero out cols and rows */
  for (i = 0; i < k; i++) {

    row = hrows[i];
    for (j = 0; j < cols; j++) {
      *(matrix + row * rows + j) = 0;
    }

    col = hcols[i];
    for (j = 0; j < rows; j++) {
      *(matrix + j * rows + col) = 0;
    }
  }

  return 0;
}


/* This one is the book's nice solution. It uses the first row/column as the
 * accumulator. */
int zero_matrix2(int rows, int cols, short *matrix)
{
  int i, j;
  int zeroInCol0 = 0;
  int zeroInRow0 = 0;

  /* See if there's a zero in the 0th row */
  for (i=0; i<cols; i++) {
    if (*(matrix + 0 * rows + i) == 0) {
      zeroInRow0 = 1;
      break;
    }
  }

  /* See if there's a zero in the 0th col */
  for (i=0; i<rows; i++) {
    if (*(matrix + i * rows + 0) == 0) {
      zeroInCol0 = 1;
      break;
    }
  }

  /* Find all zeros */
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      if (*(matrix + i * rows + j) == 0) {
        /* Mark in the 0th row, that column j is 0 */
        *(matrix + 0 * rows + j) = 0;

        /* Makr in the 0th column, that row i is 0 */
        *(matrix + i * rows + 0) = 0;
      }
    }
  }

  /* Zero out rows */
  for (i=1; i<rows; i++) {
    if (*(matrix + i * rows + 0) == 0) {
      for (j=1; j<cols; j++) {
        *(matrix + i * rows + j) = 0;
      }
    }
  }

  /* Zero out cols */
  for (i=1; i<cols; i++) {
    if (*(matrix + 0 * rows + i) == 0) {
      for (j=1; j<rows; j++) {
        *(matrix + 0 * j + i) = 0;
      }
    }
  }

  /* Zero out 0th row if needed */
  if (zeroInRow0) {
    for (i=0; i<cols; i++) {
      *(matrix + 0 * rows + i) = 0;
    }
  }


  /* Zero out 0th col if needed */
  if (zeroInCol0) {
    for (i=0; i<rows; i++) {
      *(matrix + i * rows + 0) = 0;
    }
  }

  return 0;
}


int printMatrix(int rows, int cols, short *matrix)
{
  int i,j;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf(" %3d", *(matrix + i * rows + j));
    }
    printf("\n");
  }
}

int main()
{
  short matrix2[5][5] = {
                          {  1,  2,  3,  4,  5 },
                          {  6,  7,  8,  9, 10 },
                          {  0, 12, 13, 14, 15 },
                          { 16, 17,  0, 19, 20 },
                          { 21, 22, 23, 24, 25 }
                       };


  printf("\n\nMatrix before:\n");
  printMatrix(5, 5, (short *)matrix2);
  zero_matrix(5, 5, (short *)matrix2);
  printf("\n\nMatrix after:\n");
  printMatrix(5, 5, (short *)matrix2);



  return 0;
}

