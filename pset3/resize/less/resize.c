// Copies a BMP file
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int increase = atoi(argv[1]);
    if (increase > 100 || increase < 0)
    {
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    //printf("increment: %i\n", increase);
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    //keeping old biwidth
    LONG biWidthOld = bi.biWidth;
    LONG biHeightOld = bi.biHeight;
    //new width and height
    bi.biWidth *= increase;
    bi.biHeight *= increase;

    //printf("BiWidth: %d\n", bi.biWidth);
    // bi.biWidth = increase*bi.biWidth;
    // bi.biHeight = increase*bi.biHeight;
    // bi.biSizeImage = bi.biWidth*abs(bi.biHeight);
    //printf("BiWidth: %d\nBiHeight: %d\nBiSizeImage: %d\n", bi.biWidth, bi.biHeight, bi.biSizeImage);
    RGBTRIPLE newarray [bi.biWidth * abs(bi.biHeight)];
    //printf("%i\n", newsize);


    //
    // write outfile's BITMAPFILEHEADER


    // write outfile's BITMAPINFOHEADER

    // determine padding for scanlines
    int paddingOld = (4 - (biWidthOld * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((3 * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biHeightOld); i < biHeight; i++)
    {
        // iterate over pixels in scanline

        for (int j = 0; j < increase; j++)
        {
            for (int h = 0; h < biWidthOld; h++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //fseek(inptr, paddingold, SEEK_CUR);

                //fwrite(&newarray, sizeof(RGBTRIPLE), 1, outptr);
                for (int k = 0; k < increase; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

                //fseek(inptr, -(paddingold + (sizeof(RGBTRIPLE) * (bi.biWidth/increase))), SEEK_CUR);
                //newarray[(j+(i*bi.biWidth))]=triple;
                //printf("%i\t%i\t%i\n", j, i, (j+(i*bi.biWidth)));
                //fwrite(&newarray, sizeof(RGBTRIPLE), 1, outptr);
                //fwrite(&newarray, sizeof(RGBTRIPLE), bi.biWidth, outptr);
                //fseek(inptr, -(paddingnew + (sizeof(RGBTRIPLE) * (bi.biWidth))), SEEK_CUR);

                //fwrite(&newarray, sizeof(RGBTRIPLE), 1, outptr);
                //fseek(inptr, paddingold, SEEK_CUR);
                //SCOPE!
                //RGBTRIPLE newarray[bi.biWidth];
            }
            //adding padding
            for (int g = 0; g < padding; g++)
            {
                fputc(0x00, outptr);
            }
            if (j < increase - 1)
            {
                fseek(inptr, -(biWidthOld * (int)sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        //fwrite(&newarray, sizeof(RGBTRIPLE), 1, outptr);
        // skip over padding, if any
        fseek(inptr, paddingOld, SEEK_CUR);
        //then add it back (to demonstrate how)
        // for (int k = 0; k < padding; k++)
        // {
        //     fputc(0x00, outptr);
        // }
    }
    //fwrite(&newarray, sizeof(RGBTRIPLE), 1, outptr);
    // bi.biWidth = increase*bi.biWidth;
    // bi.biHeight = increase*bi.biHeight;
    // bi.biSizeImage = bi.biWidth*abs(bi.biHeight);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}
