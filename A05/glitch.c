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
    exit(0);
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
  char* outfilename = malloc(sizeof(char)*(strlen(filename)+10));
  for (int i=0; ((i < strlen(filename)) && (filename[i] != '.')); i++) {
    outfilename[i] = filename[i];
    if (filename[i+1] == '.') {
      outfilename[i+1] = '\0';
    }
  }
  strcat(outfilename, "-glitch.ppm");
  write_ppm(outfilename, raster, w, h);

  free(outfilename);
  outfilename = NULL;
  free(raster);
  raster = NULL;
  return 0;
}
