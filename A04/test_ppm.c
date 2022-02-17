/*
test_ppm.c
Author: Keith Mburu
2/18/2022
Tests read_ppm function
*/

#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int width;
  int height;
  struct ppm_pixel** raster = read_ppm("feep-ascii.ppm", &width, &height);

  printf("Testing file feep-ascii.ppm: %d %d\n", width, height);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      printf("(%hhu,%hhu,%hhu) ", raster[i][j].red, raster[i][j].green, 
        raster[i][j].blue);
    }
    free(raster[i]);
    printf("\n");
  }
  free(raster);
  return 0;
}

