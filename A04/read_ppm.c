/*
read_ppm.c
Author: Keith Mburu
2/18/2022
Reads in a ppm file and formats the contents as a matrix of pixels
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define BUFFERSIZE 64

/*
Reads in a ppm file and formats the contents as a matrix of pixels
filename: name of file to be read in
w: width of correponding image
h: height of corresponding image
returns pointer to the matrix of pixels
*/
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }
  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  memset(buffer, '\0', BUFFERSIZE);
   
  fgets(buffer, BUFFERSIZE, file); // "magic number"
  printf("%s\n", buffer); 
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file); // comment or width, height
  if (buffer[0] == '#') {
    memset(buffer, '\0', BUFFERSIZE);
    printf("%s\n", buffer); 
    fgets(buffer, BUFFERSIZE, file);   
  }
  printf("%s\n", buffer);
  sscanf(buffer, " %d %d ", w, h);
  struct ppm_pixel** raster = malloc(sizeof(struct ppm_pixel*)* *h); // matrix
  if (raster == NULL) {
    free(buffer);
    fclose(file);
    return NULL;
  }
  for (int i=0; i < *h; i++) {
    raster[i] = malloc(sizeof(struct ppm_pixel)* *w);
    if (raster[i] == NULL) {
      free(buffer);
      fclose(file);
      return NULL;
    }
  }
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file); // maxval
  printf("%s\n", buffer);
  memset(buffer, '\0', BUFFERSIZE);

  for (int i=0; i < *h; i++) { // pixels
    for (int j=0; j < *w; j++) { 
      unsigned char r;
      unsigned char g;
      unsigned char b;
      fscanf(file, " %hhu %hhu %hhu", &r, &g, &b);
      struct ppm_pixel newpixel= {r, g, b};
      raster[i][j] = newpixel;
    }
  }
  free(buffer);      
  fclose(file);
  return raster;
}

