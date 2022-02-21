#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  char* filename = argv[1];
  int w, h;
  struct ppm_pixel** raster = read_ppm(filename, &w, &h);
  if (raster == NULL) {
    printf("Could not create raster\n");
    exit(1);
  }
  printf("Reading %s with width %d and height %d\n", filename, w, h); 
  int max = (w * h * 3)/8;
  printf("Max number of characters in the image: %d\n", max);
  char* message = malloc(sizeof(char)*max); 
  unsigned int mask = 0x00000001;
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      for (int i=0; i < 3; i++) {
        char bit[2];
        if ((raster[i][j].colors[i] & mask) == 0x00000001) {
          bit[0] = '1';
        }
        else {
          bit[0] = '0';
        }
        bit[1] = '\0';
        //printf("%s\n", bit);
        strcat(message, bit);
        //printf("%s\n", message);
      }
    }
    free(raster[i]);
    raster[i] = NULL;
  }
  free(raster);
  raster = NULL;
  printf("%s\n", message);
  return 0;
}
