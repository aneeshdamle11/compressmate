#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavlet.h"

/* Threshold for lossy compression */
#define THRESHOLD (0)


/* IWT algorithm implementation */
void wavelet_transform(double *arr, int size) {

    if (size <= 1)
        return;

    double avg[size];
    for (int i = 0; i < size / 2; ++i) {
        avg[i] = (arr[2*i] + arr[2*i + 1]) / 2;
        if (fabs(avg[i]) < THRESHOLD)
            avg[i] = 0;

        avg[i + (size / 2)] = (arr[2*i] - arr[2*i + 1]) / 2;
        if (fabs(avg[i + size / 2]) < THRESHOLD)
            avg[i] = 0;

    }

    for (int i = 0; i < size; ++i) {
        arr[i] = avg[i];
    }

    wavelet_transform(arr, size / 2);

}


/* Decoding IWT algorithm */
void inverse_wavelet_transform(double *arr, int size) {

    if (size <= 1)
        return;
    inverse_wavelet_transform(arr, size / 2);

    int i;
    double temp[size];

    for (i = 0; i < size/2; ++i) {

        // TODO : Threshold values modifications
        temp[2*i] = arr[i] + arr[i + (size / 2)];
        temp[2*i+1] = arr[i] - arr[i + (size / 2)];

    }
    for (int i = 0; i < size; ++i) {
        arr[i] = temp[i];
    }

}

