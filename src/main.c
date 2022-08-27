#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "imagemodifiers.h"

/*! \brief Image compression implementation
 * \Note Input image is 24-bit Bitmap file taken as per Microsoft doc
 */
int main(int argc, char *argv[]) {
    /* Define allowable flags */
    char *flags = "cd";

    /* Get flag and check validity */
    char flag = getopt(argc, argv, flags);
    if (flag == '?')
    {
        printf("Invalid flag.\n");
        return 1;
    }

    /* Only one filter at a time! */
    if (getopt(argc, argv, flags) != -1)
    {
        printf("Only one flag allowed.\n");
        return 2;
    }

    if (argc != optind + 2)
    {
        printf("Usage: ./a.out [flag] infile outfile\n");
        return 3;
    }

    // File I/O
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    FILE *inptr = fopen(infile, "r");           /* Open input file */
    if (!inptr)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    FILE *outptr = fopen(outfile, "w");         /* Open output file */
    if (!outptr)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    /* Read infile's BITMAPFILEHEADER */
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    /* Read infile's BITMAPINFOHEADER */
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (!image)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    /* Determine padding for scanlines */
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    /* Iterate over infile's scanlines */
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        /*! IMPORTANT
         * Skip over padding */
        fseek(inptr, padding, SEEK_CUR);
    }

    /* Check flags */
    switch (flag)
    {
        // Blur
        case 'c':
            compress(height, width, image);
            break;

        // Grayscale
        case 'd':
            decompress(height, width, image);
            break;

    }

    /* Write outfile's HEADERS
     * BITMAPFILEHEADER
     * BITMAPINFOHEADER
     */
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free free free!
    free(image);

    fclose(inptr);
    fclose(outptr);
    return 0;
}

