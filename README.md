# compressmate
Joint compression and encryption of images with **KD Trees**!

This project introduces a novel implementation of jointly compressing and encrypting bitmap images with a variant trees - **K2Tree**.

## Usage
Make sure that the input image is a Bitmap(.bmp) file
> make image

1. Compressing a bitmap file
> ./a.out -c image cipher
>
> This command will do 2 things:
> * This will compress input 'image' in a default 'compressed.ad' file
> * Also, an encrypted image with the given name 'cipher' will be created

2. Decrypting a bitmap file
> ./a.out -d cipher outfile
>
> The encrypted file will be decrypted to give an 'outfile' similar to original 'image'

This implementation showcases lossy joint compression and encryption.
In the underlying implementation, the image is encrypted using IWT and K2Tree algorithms
K2Tree compression requires the image to be transformed using Integer Wavelet transform.
IWT is lossy, making the compression lossy.

## Scope for improvement
1. Generalised implementation could include JPEG, GIMP-output file formats.
2. Decompression, more robust encryption is under development
3. Decompression ratios could be further added to test how good the compression is.
4. Lossless methods could be researched.

## References:
1. The paper from which the idea is inspired could be downloaded from: https://www.mdpi.com/2076-3417/8/10/1963
2. https://en.wikipedia.org/wiki/K-d_tree
3. https://www.dcc.uchile.cl/TR/2009/TR_DCC-20090429-005.pdf
4. https://bridgesuncc.github.io/assignments/data//24-ImageCompressionKdTree/README.html



