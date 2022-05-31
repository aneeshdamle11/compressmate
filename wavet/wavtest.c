#include <stdio.h>
#include <stdlib.h>
#include "wavlet.h"
#include "matrixmodifiers.h"

/* Wavelet transform implementation */
int main(void)
{
/*
    float arr[8] = {156, 159, 158, 155, 158, 156, 159, 158};
    wavelet_transform(arr, 8);
    for (int i = 0; i < 8; ++i) {
        printf("%f ", arr[i]);
    }
    putchar('\n');

    inverse_wavelet_transform(arr, 8);
    for (int i = 0; i < 8; ++i) {
        printf("%f ", arr[i]);
    }
    putchar('\n');
*/


    int i, j;

    float arr[8][8] = {

        {156, 159, 158, 155, 158, 156, 159, 158},
        {160, 154, 157, 158, 157, 159, 158, 158},
        {156, 159, 158, 155, 158, 156, 159, 158},
        {160, 154, 157, 158, 157, 159, 158, 158},
        {156, 153, 155, 159, 159, 155, 156, 155},
        {155, 155, 155, 157, 156, 159, 152, 158},
        {156, 153, 157, 156, 153, 155, 154, 155},
        {159, 159, 156, 158, 156, 159, 157, 161}

    };

    printf("Original:\n");
    print_matrix(8, 8, arr);
    putchar('\n');

    // Wavelet transform: row-wise
    for (i = 0; i < 8; ++i) {
        wavelet_transform(arr[i], 8);
    }

    transpose(8, 8, arr);
    // Wavelet transform: column-wise
    for (i = 0; i < 8; ++i) {
        wavelet_transform(arr[i], 8);
    }

    transpose(8, 8, arr);

    // Print transformed wavelet
    printf("\nWT:\n");
    print_matrix(8, 8, arr);
    putchar('\n');

    // Inverse wavelet transform
    transpose(8, 8, arr);
    for (i = 0; i < 8; ++i) {
        inverse_wavelet_transform(arr[i], 8);
    }
    transpose(8, 8, arr);
    for (i = 0; i < 8; ++i) {
        inverse_wavelet_transform(arr[i], 8);
    }

    printf("\nIWT:\n");
    print_matrix(8, 8, arr);
    putchar('\n');
 
    exit(0);

    putchar('\n');
    putchar('z');
    putchar('\n');
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++i) {
            printf("%f\n", arr[i][j]);
        }
        putchar('\n');
    }

    return 0;

}

