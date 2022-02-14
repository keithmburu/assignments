#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    char usage[32] = "";
    for (int i = 0; i < argc; i++) {
      strcat(usage, argv[i]);
      strcat(usage, " ");
    }
    printf("usage: %s\n", usage);
    exit(1);
  }
  char filename[32] = "./";
  strcat(filename, argv[1]);
  int width;
  int height;
  struct ppm_pixel** raster = read_ppm(filename, &width, &height);
  if (raster == NULL) {
    exit(2);
  }
  printf("Reading %s.ppm with width %d and height %d\n", filename, width, height);
  for (int i=0; i < height; i++) {
    for (int j=0; j < width; j++) {
      int total = raster[i][j].red + raster[i][j].green + raster[i][j].blue;
      int average = total/3;
      char symbol;
      if (average <= 25) {
        symbol = '@';
      }
      else if (average <= 50) {
        symbol = '#';
      }
      else if (average <= 75) {
        symbol = '%';
      }
      else if (average <= 100) {
        symbol = '*';
      }
      else if (average <= 125) {
        symbol = 'o';
      }
      else if (average <= 150) {
        symbol = ';';
      }
      else if (average <= 175) {
        symbol = ':';
      }
      else if (average <= 200) {
        symbol = ',';
      }
      else if (average <= 225) {
        symbol = '.';
      }
      else if (average <= 255) {
        symbol = ' ';
      }
      printf("%c", symbol);
    }
  printf("\n");
  }  
  return 0;
}

