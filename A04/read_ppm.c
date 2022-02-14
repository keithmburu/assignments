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
  int nlines = 1000;
  if (file == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }
  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  memset(buffer, '\0', BUFFERSIZE);
  struct ppm_pixel** raster = NULL;
  for (int n=0; n<nlines; n++) {
    fgets(buffer, BUFFERSIZE, file);
    printf("%d %s\n", n, buffer);
    if (n == 1) {
      sscanf(buffer, " %d %d ", w, h);
      nlines = *h+3;
      raster = malloc(sizeof(struct ppm_pixel*)* *h);
      for (int i=0; i < *h; i++) {
        raster[i] = malloc(sizeof(struct ppm_pixel)* *w);
      }
      if (raster == NULL) {
        fclose(file);
        return NULL;
      }
    }
    else if (n == 2) {
       int maxval;
       sscanf(buffer, " %d ", &maxval);
    }
    else if (n >= 3) {
      printf("\nline %d\n", n);
      int progress = 0;
      for (int j=0; j < *w; j++) { 
        unsigned char r;
        unsigned char g;
        unsigned char b;
        fscanf(file, " %hhu %hhu %hhu ", &r, &g, &b);
        char lastread[32];
        sscanf(buffer+progress, " %hhu %hhu %hhu ", &r, &g, &b);                
        sprintf(lastread, "%hhu %hhu %hhu", r, g, b);
        progress += strlen(lastread)+5;
        struct ppm_pixel newpixel= {r, g, b};
        raster[n-3][j] = newpixel;
        printf("raster[i][j]: %hhu %hhu %hhu\n", raster[n-3][j].red, raster[n-3][j].green, raster[n-3][j].blue);
      }
    }
    memset(buffer, '\0', BUFFERSIZE);
  }    
  fclose(file);
  return raster;
}

