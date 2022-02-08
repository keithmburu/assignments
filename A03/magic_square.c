//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name:
//
#include <stdio.h>
#include <stdlib.h>

void clear(int** matrix, int nrows) {
  for (int i=0; i < nrows; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
}

void check_rows_cols(int dim1, int dim2, int** matrix, int* checksum, int* failed) {
  for (int i=0; i < dim1; i++) {
    int sum = 0;
    for (int j=0; j < dim2; j++) {
      sum += matrix[i][j];
    }
    if (*checksum == 0) *checksum = sum;
    if (sum != *checksum) {
      printf("M is NOT a magic square!\n");
      *failed = 1;
      break; // done
    }
  }
}

void check_diags(int nrows, int ncols, int** matrix, int checksum, int* failed) {
  int lsum = 0;
  int rsum = 0;
  for (int i=0; i < nrows; i++) {
    for (int j=0; j < ncols; j++) {
      if (i == j) lsum += matrix[i][j];
      if (i == ncols-1-j) rsum += matrix[i][j];
    }
  }
  if (lsum != checksum || rsum != checksum) {
    printf("M is NOT a magic square!\n");
    *failed = 1;
  }
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
  int failed = 0;
  check_rows_cols(nrows, ncols, matrix, &checksum, &failed);
  if (!failed) check_rows_cols(ncols, nrows, matrix, &checksum, &failed);
  if (!failed) check_diags(nrows, ncols, matrix, checksum, &failed);
  if (!failed) printf("M is a magic square (magic constant = %d)\n", checksum);
  
  clear(matrix, nrows);
}

