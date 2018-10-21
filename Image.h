/*KOD PREUZET SA VEZBI BEZ VELIKIH IZMENA*/

#ifndef _DRINC_IMAGE_H_
#define _DRINC_IMAGE_H_

// First header
typedef struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;
} BITMAPFILEHEADER;

// Second Header
typedef struct {
  unsigned int size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;
} BITMAPINFOHEADER;

// Image data
typedef struct Image {
  int width, height;
  char *pixels;
} Image;


Image *image_init(int width, int height); // Image initialization function

void image_done(Image *image); // Function that frees allocated memory

void image_read(Image *image, char *filename); // Function that loads bmp file

#endif