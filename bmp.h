#ifndef BMP_H
#define BMP_H (1)

#include <stdint.h>

/*! \brief This file includes BMP related datatypes
 * \Note Microsoft Reference
 */

/*! \brief Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 *
 * \Ref http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 *      http://en.wikipedia.org/wiki/Stdint.h
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;


/*! \brief BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * \Ref http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct BITMAPFILEHEADER
{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} __attribute__((__packed__)) BITMAPFILEHEADER;


/*! \brief BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * \ref http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct BITMAPINFOHEADER
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__)) BITMAPINFOHEADER;



/*! \brief RGBTRIPLE
 *
 * \Note This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 * Alias to pixel
 *
 * \ref adaptation http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct RGBTRIPLE
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE;


#endif /* BMP_H */
