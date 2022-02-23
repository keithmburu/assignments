/*
test_ppm.c
Author: Keith Mburu
2/25/2022
Tests read_ppm function
*/

#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  char* filename = "monalisa.ppm";
  struct ppm_pixel* raster = read_ppm(filename, &w, &h);
  printf("Testing file %s: %d %d\n", filename, w, h);

  //printing pixel values
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      printf("(%hhu,%hhu,%hhu) ", raster[i+j].red, raster[i+j].green,
        raster[i+j].blue);
    }
    printf("\n");
  }

  free(raster);
  raster = NULL;
  return 0;
}

