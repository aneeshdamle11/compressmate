#include <stdio.h>
#include "matrixmodifiers.h"

void transpose(int rows, int columns, double arr[rows][columns]) {

    int i, j;

    // Transpose
    double arrT[columns][rows];

    for (i = 0; i < rows; ++i) {
        for (j = i; j < columns; ++j) {
            arrT[j][i] = arr[i][j];
        }
    }

    return;
}


void print_matrix(int rows, int columns, double arr[rows][columns]) {

    int i, j;

    for (int i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {

            printf("%lf\t", arr[i][j]);

        }
        putchar('\n');
    }
}


