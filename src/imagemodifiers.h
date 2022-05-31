#ifndef IMAGE_MODIFY_H
#define IMAGE_MODIFY_H (1)

#include "bmp.h"

/*! \brief Compress image matrix
 * \Note : TODO
 */
void compress(int height, int width, RGBTRIPLE image[height][width]);

/*! \brief Decode modified image matrix to obtain original image
 * \Note : TODO
 */
void decompress(int height, int width, RGBTRIPLE image[height][width]);

#endif /* IMAGE_MODIFY_H */
