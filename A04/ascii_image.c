/*
ascii_image.c
Author: Keith Mburu
2/18/2022
Represents RGB image using ASCII
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void print_image(struct ppm_pixel** raster, int width, int height) {
  for (int i=0; i < height; i++) {
    for (int j=0; j < width; j++) {
      int total = raster[i][j].red + raster[i][j].green + raster[i][j].blue;
      int average = total/3;
      char symbol = '\0';
      if (0 <= average && average <= 25) {
        symbol = '@';
      }
      else if (26 <= average && average <= 50) {
        symbol = '#';
      }
      else if (51 <= average && average <= 75) {
        symbol = '%';
      }
      else if (76 <= average && average <= 100) {
        symbol = '*';
      }
      else if (101 <= average && average <= 125) {
        symbol = 'o';
      }
      else if (126 <= average && average <= 150) {
        symbol = ';';
      }
      else if (151 <= average && average <= 175) {
        symbol = ':';
      }
      else if (176 <= average && average <= 200) {
        symbol = ',';
      }
      else if (201 <= average && average <= 225) {
        symbol = '.';
      }
      else if (226 <= average && average <= 255) {
        symbol = ' ';
      }
      printf("%c", symbol);
    }
    free(raster[i]); 
    printf("\n");
  }  
}

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

  int width;
  int height;
  struct ppm_pixel** raster = read_ppm(argv[1], &width, &height); // matrix

  printf("Reading %s with width %d and height %d\n", argv[1], width, 
    height);
  print_image(raster, width, height);
  free(raster);
  return 0;
}

