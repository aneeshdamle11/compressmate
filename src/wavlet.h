#ifndef WAVELET_H
#define WAVELET_H (1)


void wavelet_transform(double *arr, int size);


void inverse_wavelet_transform(double *arr, int size);


void iwt97(double* x,int n);


void fwt97(double* x,int n);


#endif /* WAVELET_H */
