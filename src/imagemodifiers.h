#ifndef IMAGE_MODIFY_H
#define IMAGE_MODIFY_H (1)

#include "bmp.h"

#define SQ_NUM (512)
//#define DECMP (1)

/*! \brief Compress image matrix
 */
void compress(int height, int width, RGBTRIPLE image[height][width]);

/*! \brief Decode modified image matrix to obtain original image
 */
void decompress(int height, int width, RGBTRIPLE image[height][width]);

#endif /* IMAGE_MODIFY_H */
