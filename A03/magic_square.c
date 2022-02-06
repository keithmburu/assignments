//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name:
//
#include <stdio.h>
#include <stdlib.h>

void clear(int status, int** matrix, int nrows) {
  for (int i=0; i < nrows; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
  exit(status);
}

void main() {
  int nrows;
  int ncols;
  scanf(" %d", &nrows);
  scanf(" %d", &ncols);
  int** matrix = malloc(sizeof(int*) * nrows);
  for (int i=0; i < nrows; i++) {
    matrix[i] = malloc(sizeof(int) * ncols);
    for (int j=0; j < ncols; j++) {
      int value;
      scanf(" %d", &value);
      matrix[i][j] = value;
    }
  }

  for (int i=0; i < nrows; i++) {
    for (int j=0; j < ncols; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  
  int checksum = 0;
  // check row sums
  for (int i=0; i < nrows; i++) {
    int sum = 0;
    for (int j=0; j < ncols; j++) {
      sum += matrix[i][j];
    }
    if (i == 0) {
      checksum = sum;
    }
    if (sum != checksum) {
      printf("M is NOT a magic square! row sum = %d\n", sum);
      clear(1, matrix, nrows);
    }
  }

  // check column sums
  for (int j=0; j < ncols; j++) {
    int sum = 0;
    for (int i=0; i < nrows; i++) {
      sum += matrix[i][j];
    }
    if (sum != checksum) {
      printf("M is NOT a magic square! column sum = %d\n", sum);
      clear(2, matrix, nrows);
    }
  }

  // check diagonal sums
  int lsum = 0;
  int rsum = 0;
  for (int i=0; i < nrows; i++) {
    for (int j=0; j < ncols; j++) {
      if (i == j) lsum += matrix[i][j];
      if (i == ncols-1-j) rsum += matrix[i][j];
    }
  }
  if (lsum != checksum || rsum != checksum) {
    printf("M is NOT a magic square! diagonal sum = %d\n", rsum);
    clear(3, matrix, nrows);
  }

  printf("M is a magic square (magic constant = %d)\n", checksum);
  clear(0, matrix, nrows);
}

