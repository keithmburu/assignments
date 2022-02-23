/*
glitch.c
Author: Keith Mburu
2/25/2022
Creates a "glitched" version of an image
*/
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
  char* filename = argv[1];
  int w, h;
  struct ppm_pixel* raster = read_ppm(filename, &w, &h);
  if (raster == NULL) {
   printf("Could not create raster\n");
   exit(1);
  }
  printf("Reading %s with width %d and height %d\n", filename, w, h); 

  //modifying pixel values
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      for (int k=0; k<3; k++) {
        //unsigned char newcolorvalue = raster[i*w+j].colors[k]<<(rand()%2);
        unsigned char newcolorvalue = raster[i*w+j].colors[(k+1)%3]<<(rand()%2);
        raster[i*w+j].colors[k] = newcolorvalue;
      }
    }
  }

  //outputting glitched image to file
  write_ppm(filename, raster, w, h);

  free(raster);
  return 0;
}
