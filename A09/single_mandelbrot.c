#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include <string.h>

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  struct ppm_pixel* raster = malloc(sizeof(struct ppm_pixel) * size * size);
  memset(raster, 0, (sizeof(struct ppm_pixel) * size * size));

  struct timeval tstart, tend;
  double timer;

  srand(time(0));

  gettimeofday(&tstart, NULL); 
  // generate pallet
  struct ppm_pixel* palette = malloc(maxIterations * sizeof(struct ppm_pixel));
  memset(palette, 0, maxIterations * sizeof(struct ppm_pixel));
  for (int i=0; i < maxIterations; i++) {
    struct ppm_pixel color;
    color.red = rand() % 255;
    color.green = rand() % 255;
    color.blue = rand() % 255;
    palette[i] = color;
  }
  struct ppm_pixel black = {{{0, 0, 0}}};
  // compute image
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      float xfrac = (float) (row+1) / size;
      float yfrac = (float) (col+1) / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
      //printf("xfrac: %f yfrac: %f x0: %f y0: %f\n", xfrac, yfrac, x0, y0);

      float x = 0;
      float xtmp;
      float y = 0;
      int iter = 0;
      while ((iter < maxIterations) && ((x*x + y*y) < 4*4)) {
        //printf("x*x + y*y = %g\n", x*x + y*y);
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
        //printf("x: %d y: %d iter: %d\n", x, y, iter);
      }
      struct ppm_pixel color; 
      if (iter < maxIterations) { // escaped
        color = palette[iter];
        //printf("r: %d g: %d b: %d\n", color.red, color.green, color.blue);
      } else {
        color = black;
      }
      // write color to image at location (row,col)
      raster[(row*size)+col] = color;
    }
  }
  gettimeofday(&tend, NULL);
  
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  
  printf("Computed mandelbrot set (%dx%d) in %.6g seconds\n", size, size, timer);
  char filename[32];
  sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));
  write_ppm(filename, raster, size, size);
}
