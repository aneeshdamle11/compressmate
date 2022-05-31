#include <stdio.h>
#include "matrixmodifiers.h"

void transpose(int rows, int columns, float arr[rows][columns]) {

    int i, j, temp;

    for (i = 0; i < rows; ++i) {
        for (j = i; j < columns; ++j) {

            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;

        }
    }

    return;
}


void print_matrix(int rows, int columns, float arr[rows][columns]) {

    int i, j;

    for (int i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {

            printf("%f\t", arr[i][j]);

        }
        putchar('\n');
    }
}


