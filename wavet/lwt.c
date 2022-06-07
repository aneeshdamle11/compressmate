#include <stdio.h>
#include <stdlib.h>
#include "matrixmodifiers.h"

#define ROW_SIZE (8)
#define COLUMN_SIZE (8)

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
    for (i = 2; i < n; i += 2)
        x[i] += a * (x[i-1] + x[i+1]);
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

int main2(void) {

	//double x[32];
	int i;

	/* Excerpts
	 * Makes a fancy cubic signal */

	//for (i=0;i<32;i++) x[i]=5+i+0.4*i*i-0.02*i*i*i;
/*	
    double x[8] = {156, 159, 158, 155, 158, 156, 159, 158};

	// Prints original sigal x
	printf("Original signal:\n");
	for (i = 0; i < 8; i++)
	    printf("x[%d]=%f\n", i, x[i]);
	putchar('\n');

    // Forward wavelet transform (9 / 7)
	fwt97(x, 8);

    // Print the wavelet coefficients
	printf("Wavelets coefficients:\n");
	for (i = 0;i < 8; i++)
	    printf("wc[%d]=%f\n", i, x[i]);
	putchar('\n');

    // Inverse wavelet transform (9 / 7)
	iwt97(x,8); 

	// Print reconstructed signals
	printf("Reconstructed signal:\n");
	for (i = 0; i < 8; i++)
	    printf("xx[%d]=%f\n", i, x[i]);
*/

/*
    double arr[2][2] = {
        {156, 159},
        {160, 154}
    };
*/
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


    printf("Original:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');

    // Wavelet transform: row-wise
    for (i = 0; i < ROW_SIZE; ++i) {
        fwt97(arr[i], ROW_SIZE);
    }

    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    // Wavelet transform: column-wise
    for (i = 0; i < COLUMN_SIZE; ++i) {
        fwt97(arr[i], ROW_SIZE);
    }

    transpose(ROW_SIZE, COLUMN_SIZE, arr);

    // Print transformed wavelet
    printf("\nWT:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');

    // Inverse wavelet transform
    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    for (i = 0; i < ROW_SIZE; ++i) {
        iwt97(arr[i], ROW_SIZE);
    }
    transpose(ROW_SIZE, COLUMN_SIZE, arr);
    for (i = 0; i < ROW_SIZE; ++i) {
        iwt97(arr[i], ROW_SIZE);
    }

    printf("\nIWT:\n");
    print_matrix(ROW_SIZE, COLUMN_SIZE, arr);
    putchar('\n');
 
    return 0;
}
