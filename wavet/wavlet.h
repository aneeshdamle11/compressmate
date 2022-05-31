#ifndef WAVELET_H
#define WAVELET_H (1)

void wavelet_transform(float *arr, int size);

void inverse_wavelet_transform(float *arr, int size);

void transpose(int rows, int columns, float arr[rows][columns]);

#endif /* WAVELET_H */
