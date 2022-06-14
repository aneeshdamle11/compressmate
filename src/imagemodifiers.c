#include <stdio.h>
#include <stdlib.h>
#include "imagemodifiers.h"
#include "../wavet/wavlet.h"
#include "../k2t/k2tree.h"

#define SQ_NUM (512)

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

void encrypt(int height, int width, RGBTRIPLE image[height][width]) {

    image_wavelet_transform(height, width/2, image, 'r');
    image_wavelet_transform(height, width/2, image, 'g');
    image_wavelet_transform(height, width/2, image, 'b');
    image_wavelet_transform(height, width/2, image + height/2, 'r');
    image_wavelet_transform(height, width/2, image + height/2, 'g');
    image_wavelet_transform(height, width/2, image + height/2, 'b');

}

void k2c(FILE *fp, int height, int width, RGBTRIPLE image[height][width], char color) {

    int i, j;
    int temp[SQ_NUM][SQ_NUM];         // Image to be compressed
    for (i = 0; i < SQ_NUM; ++i) {
        for (j = 0; j < SQ_NUM; ++j) {
            temp[i][j] = 0;
        }
    }

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

    K2Tree p = k2_image_compress(SQ_NUM, SQ_NUM, temp);
    if (!p) {
        printf("Noooo\n");
        return;
    }
    int t_count = get_Tnode_count(p->tlist);
    int l_count = get_Lnode_count(p->llist);
    int t_key, l_key;

    // Write size of T array
    fwrite(&t_count, sizeof(int), 1, fp);
    // Write contents of T array in file
    Tnode *pT = p->tlist;
    for (i = 0; i < t_count; ++i) {
        t_key = pT->key;
        pT = pT->next;
        fwrite(&t_key, 1, 1, fp);
    }

    printf("T success\n");

    // Write size of L array
    fwrite(&l_count, sizeof(int), 1, fp);
    // Write contents of L array in file
    Lnode *pL = p->llist;
    for (int i = 0; i < l_count; ++i) {
        l_key = pL->key;
        pL = pL->next;
        fwrite(&l_key, 1, 1, fp);
    }

    printf("L success\n");

    destroy_Llist(&(p->llist));
    destroy_Tlist(&(p->tlist));
    free(p);


}

/* Compress image matrix */
void compress(int height, int width, RGBTRIPLE image[height][width]) {

    encrypt(height, width, image);

    FILE *fp = fopen("comp3.txt", "wb");
    if (!fp) {
        printf("Unable to access file\n");
        return;
    }

    k2c(fp, height, width, image, 'r');
    k2c(fp, height, width, image, 'g');
    k2c(fp, height, width, image, 'b');

    fclose(fp);
    return;
}


void decrypt(int height, int width, RGBTRIPLE image[height][width]) {

    image_inverse_wavelet_transform(height, width/2, image, 'r');
    image_inverse_wavelet_transform(height, width/2, image, 'g');
    image_inverse_wavelet_transform(height, width/2, image, 'b');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'r');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'g');
    image_inverse_wavelet_transform(height, width/2, image + height/2, 'b');

}


void decompress(int height, int width, RGBTRIPLE image[height][width]) {


    // Reading file contents
    FILE *fp = fopen("comp3.txt", "rb");
    if (!fp) {
        printf("Unable to access file\n");
        return;
    }

    // For red
    int **temp = make_image(fp, SQ_NUM, SQ_NUM);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].rgbtRed = temp[i][j];
        }
    }

    // For green
    temp = make_image(fp, SQ_NUM, SQ_NUM);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].rgbtGreen = temp[i][j];
        }
    }

    // For blue
    temp = make_image(fp, SQ_NUM, SQ_NUM);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].rgbtBlue = temp[i][j];
        }
    }

    free(temp);
    fclose(fp);

    decrypt(height, width, image);

    return;
}

