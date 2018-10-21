/*KOD PREUZET SA VEZBI BEZ VELIKIH IZMENA*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Image.h"

Image *image_init(int width, int height) {

  Image *image;

  assert(width >= 0 && height >= 0);

  /// Allocate space
  image = (Image *) malloc(sizeof(Image));
  assert(image != nullptr);

  // Init data
  image->width = width;
  image->height = height;
  if (width == 0 || height == 0)
    image->pixels = nullptr;
  else {
    image->pixels = (char *)malloc(3 * width * height * sizeof(char));
    assert(image->pixels != nullptr);
  }

  // Return pointer to Image struct
  return image;
}

void image_done(Image *image) {

  // Free allocated memory
  free(image->pixels);
  free(image);
}

void image_read(Image *image, char *filename) {

  FILE *file;
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  unsigned int i;
  unsigned char r, g, b, a;

  // Overwrite previous content
  free(image->pixels);
  image->pixels = nullptr;

  // Open bmp file
  assert((file = fopen(filename, "rb")) != nullptr);

  // First header
  fread(&bfh.type, 2, 1, file);
  fread(&bfh.size, 4, 1, file);
  fread(&bfh.reserved1, 2, 1, file);
  fread(&bfh.reserved2, 2, 1, file);
  fread(&bfh.offsetbits, 4, 1, file);

  // Second header
  fread(&bih.size, 4, 1, file);
  fread(&bih.width, 4, 1, file);
  fread(&bih.height, 4, 1, file);
  fread(&bih.planes, 2, 1, file);
  fread(&bih.bitcount, 2, 1, file);
  fread(&bih.compression, 4, 1, file);
  fread(&bih.sizeimage, 4, 1, file);
  fread(&bih.xpelspermeter, 4, 1, file);
  fread(&bih.ypelspermeter, 4, 1, file);
  fread(&bih.colorsused, 4, 1, file);
  fread(&bih.colorsimportant, 4, 1, file);

  // Take width and height of the image
  image->width = bih.width;
  image->height = bih.height;

  // Allocate pixel array
  if (bih.bitcount == 24)
    image->pixels = (char *)malloc(3 * bih.width * bih.height * sizeof(char));
  else if (bih.bitcount == 32)
    image->pixels = (char *)malloc(4 * bih.width * bih.height * sizeof(char));
  else {
    fprintf(stderr, "image_read(): 24 or 32 bit per pixel images supported.\n");
    exit(1);
  }
  assert(image->pixels != nullptr);

  if (bih.bitcount == 24)
    // RGB
    for (i = 0; i < bih.width * bih.height; i++) {

      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      image->pixels[3 * i] = r;
      image->pixels[3 * i + 1] = g;
      image->pixels[3 * i + 2] = b;
    }
  else if (bih.bitcount == 32)
    //RGBA
    for (i = 0; i < bih.width * bih.height; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      image->pixels[4 * i] = r;
      image->pixels[4 * i + 1] = g;
      image->pixels[4 * i + 2] = b;
      image->pixels[4 * i + 3] = a;
    }

  // Close file
  fclose(file);
}