#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define BUFFERSIZE 1024

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }
  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  memset(buffer, '\0', BUFFERSIZE);
  
  struct ppm_pixel** raster = NULL;
  
  fgets(buffer, BUFFERSIZE, file);
  printf("%s\n", buffer);
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file);
  if (buffer[0] == '#') {
    fgets(buffer, BUFFERSIZE, file);   
  }
  printf("%s\n", buffer);
  sscanf(buffer, " %d %d ", w, h);
  raster = malloc(sizeof(struct ppm_pixel*)* *h);
  for (int i=0; i < *h; i++) {
    raster[i] = malloc(sizeof(struct ppm_pixel)* *w);
  }
  if (raster == NULL) {
    fclose(file);
    return NULL;
  }
  memset(buffer, '\0', BUFFERSIZE);
  
  fgets(buffer, BUFFERSIZE, file);
  printf("%s\n", buffer);
  int maxval;
  sscanf(buffer, " %d ", &maxval);

  for (int i=0; i < *h; i++) {
    for (int j=0; j < *w; j++) { 
      unsigned char r;
      unsigned char g;
      unsigned char b;
      fscanf(file, " %hhu %hhu %hhu", &r, &g, &b);
      struct ppm_pixel newpixel= {r, g, b};
      raster[i][j] = newpixel;
      printf("raster[i][j]: %hhu %hhu %hhu\n", raster[i][j].red, raster[i][j].green, raster[i][j].blue);
    }
  }      
  fclose(file);
  return raster;
}

