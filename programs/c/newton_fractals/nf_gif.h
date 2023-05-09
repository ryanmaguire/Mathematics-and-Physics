/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools and structs for working with GIFs.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/04                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_GIF_H
#define NF_GIF_H

/*  FILE data type, fputc, and more found here.                               */
#include <stdio.h>

/*  memcpy function provided here.                                            */
#include <string.h>

/*  malloc, calloc, and free provided here.                                   */
#include <stdlib.h>

/*  NF_INLINE macro is defined here.                                          */
#include "nf_inline.h"

/*  Booleans provided here.                                                   */
#include "nf_bool.h"

static const int kGifTransIndex = 0;

struct nf_gif_writer {
    FILE* f;
    unsigned char* oldImage;
    nf_bool firstFrame;
};

struct nf_gif_palette {
    int bitDepth;

    unsigned char r[256];
    unsigned char g[256];
    unsigned char b[256];

    /*  k-d tree over RGB space, organized in heap fashion. i.e. the left     *
     *  child of node i is node i*2, the right child is node i*2+1. Nodes     *
     *  256-511 are implicitly leaves containing a color.                     */
    unsigned char treeSplitElt[256];
    unsigned char treeSplit[256];
};

/*  Simple structure to write out the LZW-compressed portion of the image     *
 *  one bit at a time.                                                        */
struct nf_gif_bit_status {

    /*  How many bits in the partial byte written so far.                     */
    unsigned char bitIndex;

    /*  Current partial byte.                                                 */
    unsigned char byte;
    unsigned int chunkIndex;

    /*  Bytes are written in here until we have 256 of them, then written to  *
     *  the file.                                                             */
    unsigned char chunk[256];
};

/*  The LZW dictionary is a 256-ary tree constructed as the file is encoded,  *
 *  this is one node.                                                         */
struct nf_gif_lz_node {
    unsigned short int m_next[256];
};

NF_INLINE int
nf_int_max(int l, int r)
{
    if (l < r)
        return r;
    else
        return l;
}

NF_INLINE int
nf_int_min(int l, int r)
{
    if (r < l)
        return r;
    else
        return l;
}

/*  Walks the k-d tree to pick the palette entry for a desired color. Takes   *
 *  as in/out parameters the current best color and its error. Only changes   *
 *  them if it finds a better color in its subtree. This is the major hotspot *
 *  in the code at the moment.                                                */
NF_INLINE void
nf_gif_get_closest_palette_color(struct nf_gif_palette* palette,
                                 int red, int green, int blue,
                                 int *bestInd, int *bestDiff, int treeRoot)
{
    /*  Variables for the error in each color channel.                        */
    int r_err, g_err, b_err, diff;

    /*  Variable for indexing the tree.                                       */
    int ind;

    /*  More variables used in the computation.                               */
    int comps[3], splitComp, splitPos;

    /*  Base case, reached the bottom of the tree.                            */
    if (treeRoot > (1 << palette->bitDepth) - 1)
    {
        ind = treeRoot - (1 << palette->bitDepth);

        if (ind == kGifTransIndex)
            return;

        /*  Check whether this color is better than the current winner.       */
        r_err = red - ((int)palette->r[ind]);
        g_err = green - ((int)palette->g[ind]);
        b_err = blue - ((int)palette->b[ind]);
        diff = abs(r_err) + abs(g_err) + abs(b_err);

        if (diff < *bestDiff)
        {
            *bestInd = ind;
            *bestDiff = diff;
        }

        return;
    }

    /*  Take the appropriate color (r, g, or b) for this node of the k-d tree.*/
    comps[0] = red;
    comps[1] = green;
    comps[2] = blue;
    splitComp = comps[palette->treeSplitElt[treeRoot]];
    splitPos = palette->treeSplit[treeRoot];

    if (splitPos > splitComp)
    {
        /*  Check the left subtree.                                           */
        nf_gif_get_closest_palette_color(palette, red, green, blue,
                                         bestInd, bestDiff, 2*treeRoot);
        /*  Cannot prove that there is no better value in the right subtree,  *
         *  check this as well.                                               */
        if (*bestDiff > splitPos - splitComp)
            nf_gif_get_closest_palette_color(palette, red, green, blue,
                                             bestInd, bestDiff, 2*treeRoot + 1);
    }

    else
    {
        /*  Check the right subtree.                                          */
        nf_gif_get_closest_palette_color(palette, red, green, blue,
                                         bestInd, bestDiff, 2*treeRoot + 1);

        /*  Same idea as before but mirrored, check the left subtree.         */
        if (*bestDiff > splitComp - splitPos)
            nf_gif_get_closest_palette_color(palette, red, green, blue,
                                             bestInd, bestDiff, 2*treeRoot);
    }
}
/*  End of nf_gif_get_closest_palette_color.                                  */

NF_INLINE void
nf_swap_bytes(unsigned char *c0, unsigned char *c1)
{
    unsigned char tmp = *c0;
    *c0 = *c1;
    *c1 = tmp;
}

NF_INLINE void
nf_gif_swap_pixels(unsigned char *image, int pixA, int pixB)
{
    nf_swap_bytes(&image[pixA*4], &image[pixB*4]);
    nf_swap_bytes(&image[pixA*4 + 1], &image[pixB*4 + 1]);
    nf_swap_bytes(&image[pixA*4 + 2], &image[pixB*4 + 2]);
    nf_swap_bytes(&image[pixA*4 + 3], &image[pixB*4 + 3]);
}

/*  Just the partition operation from quicksort.                              */
NF_INLINE int
nf_gif_partition(unsigned char *image, const int left, const int right,
                 const int elt, int pivotIndex)
{
    const int pivotValue = image[(pivotIndex)*4 + elt];
    int storeIndex = left;
    nf_bool split = nf_false;
    int ii, arrayVal;
    nf_gif_swap_pixels(image, pivotIndex, right-1);

    for (ii = left; ii < right - 1; ++ii)
    {
        arrayVal = image[ii*4+elt];

        if (arrayVal < pivotValue)
        {
            nf_gif_swap_pixels(image, ii, storeIndex);
            ++storeIndex;
        }

        else if (arrayVal == pivotValue)
        {
            if (split)
            {
                nf_gif_swap_pixels(image, ii, storeIndex);
                ++storeIndex;
            }

            split = !split;
        }
    }

    nf_gif_swap_pixels(image, storeIndex, right - 1);
    return storeIndex;
}

/*  Perform an incomplete sort, finding all elements above and below the      *
 *  desired median.                                                           */
NF_INLINE void
nf_gif_partition_by_median(unsigned char *image, int left, int right,
                     int com, int neededCenter)
{
    /*  Variable used in the sort algorithm for the pivot.                    */
    int pivotIndex;

    if (left < right - 1)
    {
        pivotIndex = left + (right-left)/2;
        pivotIndex = nf_gif_partition(image, left, right, com, pivotIndex);

        /*  Only "sort" the section of the array that contains the median.    */
        if (pivotIndex > neededCenter)
            nf_gif_partition_by_median(image, left, pivotIndex,
                                       com, neededCenter);

        if (pivotIndex < neededCenter)
            nf_gif_partition_by_median(image, pivotIndex + 1, right,
                                       com, neededCenter);
    }
}

/*  Build a palette by creating a balanced k-d tree for all pixels.           */
NF_INLINE void
nf_gif_split_palette(unsigned char *image, int numPixels, int firstElt,
                     int lastElt, int splitElt, int splitDist, int treeNode,
                     nf_bool buildForDither, struct nf_gif_palette* pal)
{
    int ii;

    if (lastElt <= firstElt || numPixels == 0)
        return;

    /*  Base case, bottom of the tree.                                        */
    if (lastElt == firstElt + 1)
    {
        if (buildForDither)
        {
            /*  Dithering needs at least one color as dark as anything in the *
             *  image and at least one brightest color - otherwise it builds  *
             *  up error and produces strange artifacts.                      */
            if (firstElt == 1)
            {
                /*  Special case: the darkest color in the image.             */
                unsigned int r = 255U;
                unsigned int g = 255U;
                unsigned int b = 255U;

                for (ii = 0; ii < numPixels; ++ii)
                {
                    r = (unsigned int)nf_int_min((int)r, image[ii * 4 + 0]);
                    g = (unsigned int)nf_int_min((int)g, image[ii * 4 + 1]);
                    b = (unsigned int)nf_int_min((int)b, image[ii * 4 + 2]);
                }

                pal->r[firstElt] = (unsigned char)r;
                pal->g[firstElt] = (unsigned char)g;
                pal->b[firstElt] = (unsigned char)b;

                return;
            }

            if (firstElt == (1 << pal->bitDepth) - 1)
            {
                /*  Special case: the lightest color in the image.            */
                unsigned int r = 0;
                unsigned int g = 0;
                unsigned int b = 0;

                for (ii = 0; ii < numPixels; ++ii)
                {
                    r = (unsigned int)nf_int_max((int)r, image[ii * 4 + 0]);
                    g = (unsigned int)nf_int_max((int)g, image[ii * 4 + 1]);
                    b = (unsigned int)nf_int_max((int)b, image[ii * 4 + 2]);
                }

                pal->r[firstElt] = (unsigned char)r;
                pal->g[firstElt] = (unsigned char)g;
                pal->b[firstElt] = (unsigned char)b;

                return;
            }
        }

        /*  Otherwise, take the average of all colors in this subcube.        */
        unsigned long r = 0;
        unsigned long g = 0;
        unsigned long b = 0;

        for (ii = 0; ii < numPixels; ++ii)
        {
            r += image[ii*4+0];
            g += image[ii*4+1];
            b += image[ii*4+2];
        }

        /*  Round to nearest.                                                 */
        r += (unsigned long)numPixels / 2;
        g += (unsigned long)numPixels / 2;
        b += (unsigned long)numPixels / 2;

        r /= (unsigned long)numPixels;
        g /= (unsigned long)numPixels;
        b /= (unsigned long)numPixels;

        pal->r[firstElt] = (unsigned char)r;
        pal->g[firstElt] = (unsigned char)g;
        pal->b[firstElt] = (unsigned char)b;

        return;
    }

    /*  Find the axis with the largest range.                                 */
    int minR = 255, maxR = 0;
    int minG = 255, maxG = 0;
    int minB = 255, maxB = 0;

    for(ii = 0; ii < numPixels; ++ii)
    {
        int r = image[ii*4+0];
        int g = image[ii*4+1];
        int b = image[ii*4+2];

        if (r > maxR)
            maxR = r;

        if (r < minR)
            minR = r;

        if (g > maxG)
            maxG = g;

        if (g < minG)
            minG = g;

        if (b > maxB)
            maxB = b;

        if (b < minB)
            minB = b;
    }

    int rRange = maxR - minR;
    int gRange = maxG - minG;
    int bRange = maxB - minB;

    /*  And split along that axis. (incidentally, this means this isn't a     *
     *  "proper" k-d tree but I don't know what else to call it).             */
    int splitCom = 1;

    if (bRange > gRange)
        splitCom = 2;

    if (rRange > bRange && rRange > gRange)
        splitCom = 0;

    int subPixelsA = numPixels * (splitElt - firstElt) / (lastElt - firstElt);
    int subPixelsB = numPixels-subPixelsA;

    nf_gif_partition_by_median(image, 0, numPixels, splitCom, subPixelsA);

    pal->treeSplitElt[treeNode] = (unsigned char)splitCom;
    pal->treeSplit[treeNode] = image[subPixelsA*4+splitCom];

    nf_gif_split_palette(image, subPixelsA, firstElt, splitElt,
                         splitElt-splitDist, splitDist/2, treeNode*2,
                         buildForDither, pal);

    nf_gif_split_palette(image + subPixelsA*4, subPixelsB, splitElt, lastElt,
                         splitElt+splitDist, splitDist/2, treeNode*2 + 1,
                         buildForDither, pal);
}

/*  Finds all pixels that have changed from the previous image and moves them *
 *  to the fromt of th buffer. This allows us to build a palette optimized    *
 *  for the colors of the changed pixels only.                                */
NF_INLINE int
GifPickChangedPixels(const unsigned char *lastFrame,
                     unsigned char *frame, int numPixels)
{
    int numChanged = 0;
    unsigned char *writeIter = frame;
    int ii;

    for (ii = 0; ii < numPixels; ++ii)
    {
        if (lastFrame[0] != frame[0] ||
            lastFrame[1] != frame[1] ||
            lastFrame[2] != frame[2])
        {
            writeIter[0] = frame[0];
            writeIter[1] = frame[1];
            writeIter[2] = frame[2];
            ++numChanged;
            writeIter += 4;
        }

        lastFrame += 4;
        frame += 4;
    }

    return numChanged;
}

/*  Creates a palette by placing all the image pixels in a k-d tree and then  *
 *  averaging the blocks at the bottom. This is known as the "modified median *
 *  split" technique.                                                         */
NF_INLINE void
GifMakePalette(const unsigned char *lastFrame, const unsigned char *nextFrame,
               unsigned int width, unsigned int height, int bitDepth,
               nf_bool buildForDither, struct nf_gif_palette* pPal)
{
    pPal->bitDepth = bitDepth;

    /*  SplitPalette is destructive (it sorts the pixels by color) so         *
     *  we must create a copy of the image for it to destroy.                 */
    size_t imageSize = (size_t)(width * height * 4);
    unsigned char *destroyableImage = malloc(imageSize);
    int numPixels = (int)(width * height);
    const int lastElt = 1 << bitDepth;
    const int splitElt = lastElt/2;
    const int splitDist = splitElt/2;
    memcpy(destroyableImage, nextFrame, imageSize);

    if (lastFrame)
        numPixels = GifPickChangedPixels(lastFrame, destroyableImage, numPixels);

    nf_gif_split_palette(destroyableImage, numPixels, 1, lastElt,
                         splitElt, splitDist, 1, buildForDither, pPal);

    free(destroyableImage);

    /*  Add the bottom node for the transparency index.                       */
    pPal->treeSplit[1 << (bitDepth-1)] = 0;
    pPal->treeSplitElt[1 << (bitDepth-1)] = 0;
    pPal->r[0] = pPal->g[0] = pPal->b[0] = 0;
}

/*  Implements Floyd-Steinberg dithering, writes palette value to alpha.      */
NF_INLINE void
GifDitherImage(const unsigned char *lastFrame, const unsigned char *nextFrame,
               unsigned char *outFrame, unsigned int width, unsigned int height,
               struct nf_gif_palette* pPal)
{
    int numPixels = (int)(width * height);

    /*  quantPixels initially holds color*256 for all pixels. The extra 8     *
     *  bits of precision allow for sub-single-color error values to be       *
     *  propagated.                                                           */
    int *quantPixels = malloc(sizeof(*quantPixels) * (size_t)numPixels * 4);
    int ii;
    unsigned int xx, yy;

    for (ii = 0; ii < numPixels*4; ++ii)
    {
        unsigned char pix = nextFrame[ii];
        int pix16 = (int)(pix) * 256;
        quantPixels[ii] = pix16;
    }

    for (yy = 0U; yy < height; ++yy)
    {
        for (xx = 0U; xx < width; ++xx)
        {
            int *nextPix = quantPixels + 4*(yy*width + xx);
            const unsigned char *lastPix = lastFrame ? lastFrame + 4*(yy*width+xx) : NULL;

            /*  Compute the colors we want (rounding to nearest).             */
            int rr = (nextPix[0] + 127) / 256;
            int gg = (nextPix[1] + 127) / 256;
            int bb = (nextPix[2] + 127) / 256;

            /*  If it happens that we want the color from last frame, then    *
             *  just write out a transparent pixel.                           */
            if (lastFrame &&
                lastPix[0] == rr &&
                lastPix[1] == gg &&
                lastPix[2] == bb)
            {
                nextPix[0] = rr;
                nextPix[1] = gg;
                nextPix[2] = bb;
                nextPix[3] = kGifTransIndex;
                continue;
            }

            int bestDiff = 1000000;
            int bestInd = kGifTransIndex;

            /*  Search the palette.                                           */
            nf_gif_get_closest_palette_color(pPal, rr, gg, bb,
                                             &bestInd, &bestDiff, 1);

            /*  Write the result to the temp buffer.                          */
            int r_err = nextPix[0] - (int)(pPal->r[bestInd]) * 256;
            int g_err = nextPix[1] - (int)(pPal->g[bestInd]) * 256;
            int b_err = nextPix[2] - (int)(pPal->b[bestInd]) * 256;

            nextPix[0] = pPal->r[bestInd];
            nextPix[1] = pPal->g[bestInd];
            nextPix[2] = pPal->b[bestInd];
            nextPix[3] = bestInd;

            /*  Propagate the error to the four adjacent locations that we    *
             *  haven't touched yet.                                          */
            int quantloc_7 = (int)(yy * width + xx + 1);
            int quantloc_3 = (int)(yy * width + width + xx - 1);
            int quantloc_5 = (int)(yy * width + width + xx);
            int quantloc_1 = (int)(yy * width + width + xx + 1);

            if (quantloc_7 < numPixels)
            {
                int* pix7 = quantPixels+4*quantloc_7;
                pix7[0] += nf_int_max( -pix7[0], r_err * 7 / 16 );
                pix7[1] += nf_int_max( -pix7[1], g_err * 7 / 16 );
                pix7[2] += nf_int_max( -pix7[2], b_err * 7 / 16 );
            }

            if (quantloc_3 < numPixels)
            {
                int* pix3 = quantPixels+4*quantloc_3;
                pix3[0] += nf_int_max( -pix3[0], r_err * 3 / 16 );
                pix3[1] += nf_int_max( -pix3[1], g_err * 3 / 16 );
                pix3[2] += nf_int_max( -pix3[2], b_err * 3 / 16 );
            }

            if (quantloc_5 < numPixels)
            {
                int* pix5 = quantPixels+4*quantloc_5;
                pix5[0] += nf_int_max( -pix5[0], r_err * 5 / 16 );
                pix5[1] += nf_int_max( -pix5[1], g_err * 5 / 16 );
                pix5[2] += nf_int_max( -pix5[2], b_err * 5 / 16 );
            }

            if (quantloc_1 < numPixels)
            {
                int* pix1 = quantPixels+4*quantloc_1;
                pix1[0] += nf_int_max( -pix1[0], r_err / 16 );
                pix1[1] += nf_int_max( -pix1[1], g_err / 16 );
                pix1[2] += nf_int_max( -pix1[2], b_err / 16 );
            }
        }
    }

    /*  Copy the palettized result to the output buffer.                      */
    for (ii = 0; ii < numPixels*4; ++ii)
        outFrame[ii] = (unsigned char)quantPixels[ii];

    free(quantPixels);
}

/*  Pick palette colors for the image using simple thresholding, no dithering.*/
NF_INLINE void
GifThresholdImage(const unsigned char *lastFrame,
                  const unsigned char *nextFrame,
                  unsigned char *outFrame, unsigned int width,
                  unsigned int height, struct nf_gif_palette* pPal)
{
    unsigned int numPixels = width*height;
    unsigned int ii;

    for (ii = 0U; ii < numPixels; ++ii)
    {
        /*  if a previous color is available, and it matches the current      *
         *  color, set the pixel to transparent.                              */
        if(lastFrame &&
           lastFrame[0] == nextFrame[0] &&
           lastFrame[1] == nextFrame[1] &&
           lastFrame[2] == nextFrame[2])
        {
            outFrame[0] = lastFrame[0];
            outFrame[1] = lastFrame[1];
            outFrame[2] = lastFrame[2];
            outFrame[3] = kGifTransIndex;
        }
        else
        {
            /*  Palettize the pixel.                                          */
            int bestDiff = 1000000;
            int bestInd = 1;
            nf_gif_get_closest_palette_color(pPal, nextFrame[0],
                                             nextFrame[1], nextFrame[2],
                                             &bestInd, &bestDiff, 1);

            /*  Write the resulting color to the output buffer.               */
            outFrame[0] = pPal->r[bestInd];
            outFrame[1] = pPal->g[bestInd];
            outFrame[2] = pPal->b[bestInd];
            outFrame[3] = (unsigned char)bestInd;
        }

        if (lastFrame)
            lastFrame += 4;

        outFrame += 4;
        nextFrame += 4;
    }
}

/*  Insert a single bit.                                                      */
NF_INLINE void
GifWriteBit(struct nf_gif_bit_status* stat, unsigned int bit)
{
    bit = bit & 1;
    bit = bit << stat->bitIndex;
    stat->byte |= bit;

    ++stat->bitIndex;
    if (stat->bitIndex > 7)
    {
        /*  Move the newly-finished byte to the chunk buffer.                 */
        stat->chunk[stat->chunkIndex++] = stat->byte;

        /*  And start a new byte.                                             */
        stat->bitIndex = 0;
        stat->byte = 0;
    }
}

/*  Write all bytes so far to the file.                                       */
NF_INLINE void
GifWriteChunk(FILE* f, struct nf_gif_bit_status* stat)
{
    fputc((int)stat->chunkIndex, f);
    fwrite(stat->chunk, 1, stat->chunkIndex, f);

    stat->bitIndex = 0;
    stat->byte = 0;
    stat->chunkIndex = 0;
}

NF_INLINE void
GifWriteCode(FILE* f, struct nf_gif_bit_status* stat,
             unsigned int code, unsigned int length)
{
    unsigned int ii;
    for (ii = 0U; ii < length; ++ii)
    {
        GifWriteBit(stat, code);
        code = code >> 1;

        if (stat->chunkIndex == 255)
            GifWriteChunk(f, stat);
    }
}

/*  Write a 256-color (8-bit) image palette to the file.                      */
NF_INLINE void GifWritePalette( const struct nf_gif_palette* pPal, FILE* f)
{
    int ii;

    /*  First color: transparency.                                            */
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);

    for (ii = 1; ii < (1 << pPal->bitDepth); ++ii)
    {
        unsigned int r = pPal->r[ii];
        unsigned int g = pPal->g[ii];
        unsigned int b = pPal->b[ii];

        fputc((int)r, f);
        fputc((int)g, f);
        fputc((int)b, f);
    }
}

/*  Write the image header, LZW-compress and write out the image.             */
NF_INLINE void
GifWriteLzwImage(FILE* f, unsigned char *image, unsigned int left,
                 unsigned int top, unsigned int width, unsigned int height,
                 unsigned int delay, struct nf_gif_palette* pPal)
{
    unsigned int xx, yy;

    /*  Graphics control extension.                                           */
    fputc(0x21, f);
    fputc(0xf9, f);
    fputc(0x04, f);

    /*  Leave prev frame in place, this frame has transparency.               */
    fputc(0x05, f);
    fputc(delay & 0xff, f);
    fputc((delay >> 8) & 0xff, f);

    /*  Transparent color index.                                              */
    fputc(kGifTransIndex, f);
    fputc(0, f);

    /*  Image descriptor block.                                               */
    fputc(0x2c, f);

    /*  Corner of image in canvas space.                                      */
    fputc(left & 0xff, f);
    fputc((left >> 8) & 0xff, f);
    fputc(top & 0xff, f);
    fputc((top >> 8) & 0xff, f);

    /*  Width and height of image.                                            */
    fputc(width & 0xff, f);
    fputc((width >> 8) & 0xff, f);
    fputc(height & 0xff, f);
    fputc((height >> 8) & 0xff, f);

    /*  Local color table present, 2 ^ bitDepth entries.                      */
    fputc(0x80 + pPal->bitDepth-1, f);
    GifWritePalette(pPal, f);

    const int minCodeSize = pPal->bitDepth;
    const unsigned int clearCode = 1 << pPal->bitDepth;

    /*  min code size 8 bits.                                                 */
    fputc(minCodeSize, f);

    struct nf_gif_lz_node *codetree = calloc(sizeof(*codetree), 4096U);

    int curCode = -1;
    unsigned int codeSize = (unsigned int)minCodeSize + 1;
    unsigned int maxCode = clearCode+1;

    struct nf_gif_bit_status stat;
    stat.byte = 0;
    stat.bitIndex = 0;
    stat.chunkIndex = 0;

    /*  Start with a fresh LZW dictionary.                                    */
    GifWriteCode(f, &stat, clearCode, codeSize);

    for (yy = 0U; yy < height; ++yy)
    {
        for (xx = 0U; xx < width; ++xx)
        {
#ifdef GIF_FLIP_VERT
            /*  Bottom-left origin image (such as an OpenGL capture).         */
            unsigned char nextValue = image[((height-1-yy)*width+xx)*4+3];
#else
            /*  Top-left origin, like with PPM files.                         */
            unsigned char nextValue = image[(yy*width+xx)*4+3];
#endif

            /*  First value in a new run.                                     */
            if (curCode < 0)
                curCode = nextValue;

            /*  Current run already in the dictionary.                        */
            else if(codetree[curCode].m_next[nextValue])
                curCode = codetree[curCode].m_next[nextValue];

            else
            {
                /*  Finish the current run, write a code.                     */
                GifWriteCode(f, &stat, (unsigned int)curCode, codeSize);

                /*  Insert the new run into the dictionary.                   */
                codetree[curCode].m_next[nextValue] = (unsigned short int)++maxCode;

                /*  Dictionary entry count has broken a size barrier, we need *
                 *  more bits for codes.                                      */
                if (maxCode >= (1ul << codeSize))
                    codeSize++;

                if (maxCode == 4095)
                {
                    /*  The dictionary is full, clear it out and begin anew.  */
                    GifWriteCode(f, &stat, clearCode, codeSize);

                    memset(codetree, 0, sizeof(*codetree)*4096);
                    codeSize = (unsigned int)(minCodeSize + 1);
                    maxCode = clearCode+1;
                }

                curCode = nextValue;
            }
        }
    }

    /*  Compression footer.                                                   */
    GifWriteCode(f, &stat, (unsigned int)curCode, codeSize);
    GifWriteCode(f, &stat, clearCode, codeSize);
    GifWriteCode(f, &stat, clearCode + 1, (unsigned int)minCodeSize + 1);

    /*  Write out the last partial chunk.                                     */
    while (stat.bitIndex )
        GifWriteBit(&stat, 0);

    if (stat.chunkIndex)
        GifWriteChunk(f, &stat);

    /*  Image block terminator.                                               */
    fputc(0, f);

    free(codetree);
}

/*  Creates a gif file. The input GIF writer is assumed to be uninitialized.  *
 *  The delay value is the time between frames in hundredths of a second.     *
 *  Note that not all viewers pay much attention to this value.               */
NF_INLINE nf_bool
nf_gif_begin(struct nf_gif_writer* writer, const char* filename,
             unsigned int width, unsigned int height, unsigned int delay,
             unsigned int bitDepth, nf_bool dither)
{
    /*  Mute "Unused argument" warnings.                                      */
    (void)bitDepth;
    (void)dither;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
	  writer->f = 0;
    fopen_s(&writer->f, filename, "wb");
#else
    writer->f = fopen(filename, "wb");
#endif

    if(!writer->f)
        return nf_false;

    writer->firstFrame = nf_true;

    /*  Allocate.                                                             */
    writer->oldImage = malloc(width*height*4);
    fputs("GIF89a", writer->f);

    /*  Screen descriptor.                                                    */
    fputc(width & 0xff, writer->f);
    fputc((width >> 8) & 0xff, writer->f);
    fputc(height & 0xff, writer->f);
    fputc((height >> 8) & 0xff, writer->f);

    /*  There is an unsorted global color table of 2 entries.                 */
    fputc(0xF0, writer->f);

    /*  Background color.                                                     */
    fputc(0, writer->f);

    /*  Pixels are square (we need to specify this because it's 1989).        */
    fputc(0, writer->f);

    /*  Now the "global" palette (really just a dummy palette).               *
     *  color 0: black.                                                       */
    fputc(0, writer->f);
    fputc(0, writer->f);
    fputc(0, writer->f);

    /*  color 1: also black.                                                  */
    fputc(0, writer->f);
    fputc(0, writer->f);
    fputc(0, writer->f);

    if (delay != 0)
    {
        /*  Animation header. This is the extension.                          */
        fputc(0x21, writer->f);

        /*  Application specific.                                             */
        fputc(0xff, writer->f);

        /*  Length 11.                                                        */
        fputc(11, writer->f);

        /*  Yes, really.                                                      */
        fputs("NETSCAPE2.0", writer->f);

        /*  3 bytes of NETSCAPE2.0 data.                                      */
        fputc(3, writer->f);

        /*  JUST BECAUSE.                                                     */
        fputc(1, writer->f);

        /*  Loop infinitely (byte 0).                                         */
        fputc(0, writer->f);

        /*  Loop infinitely (byte 1).                                         */
        fputc(0, writer->f);

        /*  Block terminator.                                                 */
        fputc(0, writer->f);
    }

    return nf_true;
}
/*  End of nf_gif_begin.                                                      */

/*  Writes out a new frame to a GIF in progress. The GIF writer should have   *
 *  been created by GIFBegin. As far as I knot it is legal to use different   *
 *  bit depths for different frames of an image. This may be handy to save    *
 *  bits in animations that don't change much.                                */
NF_INLINE void
nf_gif_write_frame(struct nf_gif_writer *writer, const unsigned char *image,
                   unsigned int width, unsigned int height, unsigned int delay,
                   int bitDepth, nf_bool dither)
{
    struct nf_gif_palette pal;
    const unsigned char *old_image;

    if (!writer->f)
        return;

    if (writer->firstFrame)
        old_image = NULL;
    else
        old_image = writer->oldImage;

    writer->firstFrame = nf_false;

    if (dither)
        GifMakePalette(NULL, image, width, height, bitDepth, dither, &pal);
    else
        GifMakePalette(old_image, image, width, height, bitDepth, dither, &pal);

    if(dither)
        GifDitherImage(old_image, image, writer->oldImage, width, height, &pal);
    else
        GifThresholdImage(old_image, image, writer->oldImage, width, height, &pal);

    GifWriteLzwImage(writer->f, writer->oldImage, 0, 0, width, height, delay, &pal);
}

/*  Writes the EOF code, closes the file handle, and frees temp memory used   *
 *  by a GIF. Many if not most viewers will still display a GIF properly if   *
 *  the EOF code is missing, but it's still a good idea to write it out.      */
NF_INLINE void nf_gif_end(struct nf_gif_writer* writer)
{
    if (!writer->f)
        return;

    fputc(0x3b, writer->f);
    fclose(writer->f);
    free(writer->oldImage);

    writer->f = NULL;
    writer->oldImage = NULL;
}

#endif
/*  End of include guard.                                                     */
