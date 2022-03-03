/*
encode.c
Author: Keith Mburu
3/4/2022
Encodes an image with a message
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

#define BUFFERSIZE 1024

/*
Converts ASCII character to its binary representation
character: char to be converted
bin: return address
*/
void char_to_bin(char character, char* bin) {
  int dec = character;
  unsigned int mask = 0x00000001;
  for (int i=7; i > -1; i--) {
    char bit;
    if ((dec & mask) == 0x00000001) {
      bit = '1';
    }
    else {
      bit = '0';
    }
    bin[i] = bit;
    //printf("binter: %s\n", bin);
    dec = dec>>1;
    //printf("dec: %X\n", dec);
  }
  bin[8] = '\0';
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
  char* filename = argv[1];
  int w, h;
  struct ppm_pixel* raster = read_ppm(filename, &w, &h);
  if (raster == NULL) {
    printf("Could not create raster\n");
    exit(1); //done
  }
  printf("Reading %s with width %d and height %d\n", filename, w, h); 

  int max = ((w * h * 3)/8)-1;
  printf("Max number of characters in the image: %d\n", max);

  char* phrase = malloc(sizeof(char)*(max+1));
  printf("Enter a phrase: ");
  fgets(phrase, sizeof(char)*(max+1), stdin);
  //printf("\nPhrase is %ld characters long\n", strlen(phrase));

  char* encoded = malloc(sizeof(char)*((max+1)*8 + 1));  
  memset(encoded, '\0', (sizeof(char)*((max+1)*8 + 1)));
  char bin[9]; 
  for (int i=0; i <= strlen(phrase); i++) {
    char_to_bin(phrase[i], bin);
    //printf("'%c' in binary: %s\n", phrase[i], bin);
    strcat(encoded, bin); 
  }

  //printf("encoded: %s\n", encoded);
  
  int index = 0; 
  for (int i=0; (i<h) & (index < strlen(encoded)); i++) {
    for (int j=0; (j<w) & (index < strlen(encoded)); j++) {
      for (int k=0; (k<3) & (index < strlen(encoded)); k++) {
        unsigned int mask;
        if (encoded[index] == '0')  {
          // make last bit 0 and leave the rest unchanged
          mask = 0xFFFFFFF0;
          raster[i*w+j].colors[k] = (raster[i*w+j].colors[k] & mask);
        }
        else if (encoded[index] == '1') { 
          // make last bit 1 and leave the rest unchanged
          mask = 0x00000001;
          raster[i*w+j].colors[k] = (raster[i*w+j].colors[k] | mask);
        }
        index++;
      }
    }
  }

  //outputting encoded image to file
  char* outfilename = malloc(sizeof(char)*(strlen(filename)+10));
  for (int i=0; ((i < strlen(filename)) && (filename[i] != '.')); i++) {
    outfilename[i] = filename[i];
    if (filename[i+1] == '.') {
      outfilename[i+1] = '\0';
    }
  }
  strcat(outfilename, "-encoded.ppm");
  write_ppm(outfilename, raster, w, h);

  free(outfilename);
  outfilename = NULL;
  free(encoded);
  encoded = NULL;
  free(phrase);
  phrase = NULL;
  free(raster);
  raster = NULL;
  return 0;
}
