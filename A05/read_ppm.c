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

  int size = sizeof(struct ppm_pixel) * *w * *h;
  struct ppm_pixel* raster = malloc(size); // matrix
  if (raster == NULL) {
    free(buffer);
    fclose(file);
    return NULL;
  }
  
  fgets(buffer, BUFFERSIZE, file); // maxval
  //printf("%s\n", buffer);
  memset(buffer, '\0', BUFFERSIZE);

  //reading pixel matrix into raster
  fread(raster, size, 1, file);

  free(buffer);
  buffer = NULL;      
  fclose(file);
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
  FILE* infile = fopen(filename, "rb");
  if (infile == NULL) {
    printf("Cannot open file: %s\n", filename);
    exit(1);
  }

  char* outfilename = malloc(sizeof(char)*(strlen(filename)+7));
  for (int i=0; ((i < strlen(filename)) && (filename[i] != '.')); i++) {
    outfilename[i] = filename[i];
  }
  strcat(outfilename, "-glitch.ppm");

  FILE* outfile = fopen(outfilename, "wb");

  char* buffer = malloc(sizeof(char) * BUFFERSIZE);
  memset(buffer, '\0', BUFFERSIZE);
  
  // "magic number"
  fgets(buffer+strlen(buffer), BUFFERSIZE-strlen(buffer), infile);  
  //printf("%s\n", buffer); 

  char* hashtag = buffer+strlen(buffer); 

  // comment or width, height
  fgets(buffer+strlen(buffer), BUFFERSIZE-strlen(buffer), infile);  
  if (*hashtag == '#') {
    //printf("%s\n", buffer); 
    fgets(buffer+strlen(buffer), BUFFERSIZE-strlen(buffer), infile);   
  }
  //printf("%s\n", buffer);
  sscanf(buffer+strlen(buffer), " %d %d ", &w, &h);

  //maxval
  fgets(buffer+strlen(buffer), BUFFERSIZE-strlen(buffer), infile); 
  //printf("%s\n", buffer);

  printf("Writing file %s\n", outfilename);
  fwrite(buffer, sizeof(char)*strlen(buffer), 1, outfile);  
  
  if (pxs != NULL) {
    fwrite(pxs, sizeof(struct ppm_pixel) * w * h, 1, outfile);
  }

  free(buffer);
  fclose(infile);
  fclose(outfile);  
  buffer = NULL;
  infile = NULL;
  outfile = NULL;   
}
