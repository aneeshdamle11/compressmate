#include <stdio.h>
#include <stdlib.h>
#include "imagemodifiers.h"
#include "../wavet/wavlet.h"

// Copies image
void copy_image(int height, int width, RGBTRIPLE to[height][width], RGBTRIPLE from[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            to[i][j].rgbtRed = from[i][j].rgbtRed;
            to[i][j].rgbtGreen = from[i][j].rgbtGreen;
            to[i][j].rgbtBlue = from[i][j].rgbtBlue;
        }
    }

    return;
}


// Wavelet transform on given color channel
void image_wavelet_transform(int height, int width,
                             RGBTRIPLE image[height][width], char color) {
    int i, j;
    double temp[height][width];         // Image to be transformed
    double temp_T[width][height];       // Transpose of transform

    if (color == 'b') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtBlue;
            }
        }
    } else if (color == 'g') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtGreen;
            }
        }
    } else if (color == 'r') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtRed;
            }
        }
    } else
        return;


    // Wavelet transform: row-wise
    for (i = 0; i < height; ++i) {
        wavelet_transform(temp[i], width);
    }

    // Transpose
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            temp_T[j][i] = temp[i][j];
        }
    }

    // Wavelet transform: column-wise
    for (i = 0; i < width; ++i) {
        wavelet_transform(temp_T[i], height);
    }

    // Transpose
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            temp[j][i] = temp_T[i][j];
        }
    }


    if (color == 'b') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtBlue = temp[i][j];
            }
        }
    } else if (color == 'g') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtGreen = temp[i][j];
            }
        }
    } else if (color == 'r') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtRed = temp[i][j];
            }
        }
    }

    return;
}


void image_inverse_wavelet_transform(int height, int width,
                             RGBTRIPLE image[height][width], char color) {

    int i, j;
    double temp[height][width];         // Image to be inversely-transformed
    double temp_T[width][height];       // Transpose of inverse-transform

    if (color == 'b') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtBlue;
            }
        }
    } else if (color == 'g') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtGreen;
            }
        }
    } else if (color == 'r') {

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                temp[i][j] = image[i][j].rgbtRed;
            }
        }
    } else
        return;


    // Inverse wavelet transform: row-wise
    for (i = 0; i < height; ++i) {
        inverse_wavelet_transform(temp[i], width);
    }

    // Transpose
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            temp_T[j][i] = temp[i][j];
        }
    }

    // Inverse wavelet transform: column-wise
    for (i = 0; i < width; ++i) {
        inverse_wavelet_transform(temp_T[i], height);
    }

    // Transpose
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            temp[j][i] = temp_T[i][j];
        }
    }


    if (color == 'b') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtBlue = temp[i][j];
            }
        }
    } else if (color == 'g') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtGreen = temp[i][j];
            }
        }
    } else if (color == 'r') {
        // Update original image
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                image[i][j].rgbtRed = temp[i][j];
            }
        }
    }

    return;
}

/* Compress image matrix */
void compress(int height, int width, RGBTRIPLE image[height][width]) {

    image_wavelet_transform(height, width/2, image, 'r');
    image_wavelet_transform(height, width/2, image, 'g');
    image_wavelet_transform(height, width/2, image, 'b');
    image_wavelet_transform(height, width/2, image + height/2, 'r');
    image_wavelet_transform(height, width/2, image + height/2, 'g');
    image_wavelet_transform(height, width/2, image + height/2, 'b');

    return;
}


void decompress(int height, int width, RGBTRIPLE image[height][width]) {

    image_inverse_wavelet_transform(height, width/2, image, 'r');
    image_inverse_wavelet_transform(height, width/2, image, 'g');
    image_inverse_wavelet_transform(height, width/2, image, 'b');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'r');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'g');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'b');

    return;
}

