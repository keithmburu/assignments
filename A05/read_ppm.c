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

#define BUFFERSIZE 1024

/*
Reads in a ppm file and formats the contents as a matrix of pixels
filename: name of file to be read in
w: width of correponding image
h: height of corresponding image
returns pointer to the matrix of pixels
*/
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }
  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  memset(buffer, '\0', BUFFERSIZE);
   
  fgets(buffer, BUFFERSIZE, file); // "magic number"
  //printf("%s\n", buffer); 
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file); // comment or width, height
  if (buffer[0] == '#') {
    //printf("%s\n", buffer); 
    memset(buffer, '\0', BUFFERSIZE);
    fgets(buffer, BUFFERSIZE, file);   
  }
  //printf("%s\n", buffer);
  sscanf(buffer, " %d %d ", w, h);
  struct ppm_pixel** raster = malloc(sizeof(struct ppm_pixel*)* *h); // matrix
  if (raster == NULL) {
    free(buffer);
    fclose(file);
    return NULL;
  }
  for (int i=0; i < *h; i++) {
    raster[i] = malloc(3*sizeof(int)* *w);
    //memset(raster[i], NULL, *w);
    if (raster[i] == NULL) {
      free(buffer);
      fclose(file);
      return NULL;
    }
  }
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file); // maxval
  //printf("%s\n", buffer);
  memset(buffer, '\0', BUFFERSIZE);

  for (int i=0; i < *h; i++) { 
    fread(raster[i], 3*sizeof(int), *w, file);
  }

  free(buffer);
  buffer = NULL;      
  fclose(file);
  return raster;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel** pxs, int w, int h) {

}
