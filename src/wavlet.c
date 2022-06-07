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

/*! \brief Lifting wavelet transform implementation
 * \Note - Fast discrete biorthogonal CDF 9/7 wavelet 
 * forward and inverse transform (lifting implementation)
 */

double *tempbank=0;

/*! \brief fwt97: Forward wavelet transform
*  Forward biorthogonal 9/7 wavelet transform (lifting implementation)
*
*  \param[in]   x: input signal (will be replaced by its output transform)
*               n is the length of the signal, and must be a power of 2.
*
* \retval void
*  First half part of the output signal contains the approx coefficients
*  Second half part contains the detail (or) wavelets coefficients
*
*/
void fwt97(double* x,int n) {

	double a;
	int i;

    /* First predict step */
	a = -1.586134342;
	for (i = 1; i < n - 2; i += 2)
	    x[i] += a * (x[i-1] + x[i+1]);
	x[n-1] += 2 * a * x[n-2];

    /* First update step */
	a = -0.05298011854;
    for (i = 2; i < n; i += 2) {
        x[i] += a * (x[i-1] + x[i+1]);
    }

	x[0] += 2 * a * x[1];

	/* Second predict step */
	a = 0.8829110762;
	for (i = 1;i < n-2;i += 2)
	    x[i] += a * (x[i-1] + x[i+1]);
	x[n-1]+=2*a*x[n-2];

	/* Second update step */
	a = 0.4435068522;
	for (i = 2; i < n; i += 2)
	    x[i] += a * (x[i-1]+x[i+1]);
	x[0]+=2*a*x[1];

    /* Scale */
	a = 1 / 1.149604398;
	for (i = 0; i < n; i++)
	    if (i % 2)
	        x[i] *= a;
	    else
	        x[i] /= a;

    /* Pack */
	if (tempbank == 0)
	    tempbank = (double *) malloc(n * sizeof(double));

	for (i = 0; i < n; i++)
	    if (i % 2 == 0)
	        tempbank[i / 2] = x[i];
	    else
	        tempbank[n/2 + i/2] = x[i];

	for (i = 0; i < n; i++)
	    x[i] = tempbank[i];

}


/*! \breif iwt97: Inverse Lifting Wavelet Transform Implementation
 * \Note Inverse biorthogonal 9/7 wavelet transform
 *
 *  \Explanantion
 *  iwt97(fwt97(x,n),n) = x for every signal x of length n.
 *
 *  \param[in]   x: input signal (will be replaced by its output transform)
 *               n is the length of the signal, and must be a power of 2.
 *  \retval void
 */
void iwt97(double* x,int n) {

	double a;
	int i;

    /* Unpack */
	if (tempbank == 0)
	    tempbank = (double *)malloc(n * sizeof(double));

	for (i = 0; i < n/2; i++) {

		tempbank[i*2] = x[i];
		tempbank[i*2 + 1] = x[i + n/2];

	}

	for (i=0; i < n; i++)
	    x[i] = tempbank[i];

    /* Reverse scaling */
	a = 1.149604398;
	for (i = 0;i < n; i++)
	    if (i % 2)
	        x[i] *= a;
	    else
	        x[i] /= a;

    /* Reverse second update step */
	a =- 0.4435068522;
	for (i = 2; i < n; i += 2)
	    x[i] += a * (x[i-1]+x[i+1]);
	x[0] += 2 * a * x[1];

    /* Reverse predict step */
	a =- 0.8829110762;
	for (i = 1; i < n-2; i += 2)
	    x[i] += a * (x[i-1] + x[i+1]);
	x[n-1] += 2 * a * x[n-2];

    /* Reverse first update step */
	a = 0.05298011854;
	for (i = 2; i < n; i += 2)
	    x[i] += a * (x[i-1] + x[i+1]);
	x[0] += 2 * a * x[1];

    /* Reverse first predict step */
    a = 1.586134342;
	for (i = 1; i < n-2; i += 2)
	    x[i] += a * (x[i-1] + x[i+1]);
	x[n-1] += 2 * a * x[n-2];

}



