#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>

int main() {

  // todo: call read_ppm
  struct ppm_pixel** raster = NULL;
  int width;
  int height;
  raster = read_ppm("./feep-ascii.ppm", &width, &height);
  printf("Testing file feep-ascii.ppm: %d %d\n", width, height);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      printf("(%hhu %hhu %hhu) ", raster[i][j].red, raster[i][j].green, raster[i][j].blue);
    }
    free(raster[i]);
    printf("\n");
  }
  free(raster);
  return 0;
}

