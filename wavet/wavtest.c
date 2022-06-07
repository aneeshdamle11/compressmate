#include <stdio.h>
#include <stdlib.h>
#include "wavlet.h"
#include "matrixmodifiers.h"

#define ROW_SIZE (8)
#define COLUMN_SIZE (8)


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


    double arr[8][8] = {

        {156, 159, 158, 155, 158, 156, 159, 158},
        {160, 154, 157, 158, 157, 159, 158, 158},
        {156, 159, 158, 155, 158, 156, 159, 158},
        {160, 154, 157, 158, 157, 159, 158, 158},
        {156, 153, 155, 159, 159, 155, 156, 155},
        {155, 155, 155, 157, 156, 159, 152, 158},
        {156, 153, 157, 156, 153, 155, 154, 155},
        {159, 159, 156, 158, 156, 159, 157, 161}

    };

/*
    double arr[2][2] = {
        {156, 159},
        {160, 154}
    };
*/
    printf("Original:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');

    // Wavelet transform: row-wise
    for (i = 0; i < ROW_SIZE; ++i) {
        wavelet_transform(arr[i], ROW_SIZE);
    }

    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    // Wavelet transform: column-wise
    for (i = 0; i < COLUMN_SIZE; ++i) {
        wavelet_transform(arr[i], ROW_SIZE);
    }

    transpose(ROW_SIZE, COLUMN_SIZE, arr);

    // Print transformed wavelet
    printf("\nWT:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');

    // Inverse wavelet transform
    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    for (i = 0; i < ROW_SIZE; ++i) {
        inverse_wavelet_transform(arr[i], ROW_SIZE);
    }
    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    for (i = 0; i < ROW_SIZE; ++i) {
        inverse_wavelet_transform(arr[i], ROW_SIZE);
    }

    printf("\nIWT:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');
 
    return 0;

}

