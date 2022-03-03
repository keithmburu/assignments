/*
read_ppm.c
Author: Keith Mburu
2/25/2022
Reading pixel matrix from file and writing pixel matrix to file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define BUFFERSIZE 1024

/*
Reads in a ppm file and formats the contents as a matrix of pixels
filename: name of file to be read in
w: width of correponding image
h: height of corresponding image
returns pointer to the matrix of pixels
*/
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }
  
  // header lines
  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  int headerlines = 3;
  while (headerlines > 0) {
    fgets(buffer, BUFFERSIZE, file);
    if (headerlines == 2) {
      sscanf(buffer, " %d %d ", w, h);
    }
    if (buffer[0] != '#') {
      headerlines -= 1;
    }
    memset(buffer, '\0', BUFFERSIZE);
  }

  free(buffer);
  buffer = NULL;      
  
  int size = sizeof(struct ppm_pixel) * *w * *h;
  struct ppm_pixel* raster = malloc(size); // matrix
  if (raster == NULL) {
    printf("Could not create raster\n");
    return NULL;
  }
  
  // reading pixel matrix into raster
  fread(raster, size, 1, file);

  fclose(file);
  file = NULL;
  return raster;
}

/*
Writes a matrix of pixels to a ppm file
filename: name of file to be read in
pxs: matrix of pixels to be written
w: width of correponding image
h: height of corresponding image
returns pointer to the matrix of pixels
*/
void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE* file = fopen(filename, "wb");
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    exit(1);
  }

  printf("Writing file %s\n", filename);
  fprintf(file, "P6\n%d %d\n255\n", w, h);
  
  if (pxs == NULL) {
    printf("Pixel matrix to be written is empty!");
    exit(1);
  }
  
  // writing raster to file
  fwrite(pxs, sizeof(struct ppm_pixel) * w * h, 1, file);

  fclose(file);
  file = NULL;
}
