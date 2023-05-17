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
 *      Provides a struct for using colors.                                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/13                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COLOR_H
#define NF_COLOR_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  NF_INLINE macro found here.                                               */
#include "nf_inline.h"

/*  Struct for working with PPM files found here.                             */
#include "nf_ppm.h"

/*  Constants used throughout the project defined here.                       */
#include "nf_setup.h"

/*  ceil and atan functions provided here.                                    */
#include <math.h>

/*  Simple struct for working with colors in a PPM file.                      */
struct nf_color {

    /*  A color is defined by its RGB values.                                 */
    unsigned char red, green, blue;
};

/*  Constant colors that are frequently used.                                 */
static const struct nf_color nf_white = {0xFFU, 0xFFU, 0xFFU};
static const struct nf_color nf_black = {0x00U, 0x00U, 0x00U};
static const struct nf_color nf_red = {0xFFU, 0x00U, 0x00U};
static const struct nf_color nf_green = {0x00U, 0xFFU, 0x00U};
static const struct nf_color nf_blue = {0x00U, 0x00U, 0xFFU};
static const struct nf_color nf_yellow = {0xFFU, 0xFFU, 0x00U};
static const struct nf_color nf_cyan = {0x00U, 0xFFU, 0xFFU};
static const struct nf_color nf_magenta = {0xFFU, 0x00U, 0xFFU};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_create                                                       *
 *  Purpose:                                                                  *
 *      Creates a color struct from three unsigned values.                    *
 *  Arguments:                                                                *
 *      r (unsigned char):                                                    *
 *          The red component of the color.                                   *
 *      g (unsigned char):                                                    *
 *          The green component of the color.                                 *
 *      b (unsigned char):                                                    *
 *          The blue component of the color.                                  *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color (r, g, b) in 24-bit RGB color space.                    *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    /*  Declare a variable for the output color.                              */
    struct nf_color c;

    /*  Set the individual components and return.                             */
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}
/*  End of nf_color_create.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_write_to_file                                                *
 *  Purpose:                                                                  *
 *      Writes a color to a FILE pointer.                                     *
 *  Arguments:                                                                *
 *      c (const struct nf_color *):                                          *
 *          A pointer to a color.                                             *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NF_INLINE void
nf_color_write_to_file(const struct nf_color *c, FILE *fp)
{
    fputc(c->red, fp);
    fputc(c->green, fp);
    fputc(c->blue, fp);
}
/*  End of nf_color_write_to_file.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_write_to_ppm                                                 *
 *  Purpose:                                                                  *
 *      Writes a color to a ppm pointer.                                      *
 *  Arguments:                                                                *
 *      c (const struct nf_color *):                                          *
 *          A pointer to a color.                                             *
 *      PPM (struct nf_ppm *):                                                *
 *          A pointer to the ppm the color is being written to.               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NF_INLINE void
nf_color_write_to_ppm(const struct nf_color *c, struct nf_ppm *PPM)
{
    nf_color_write_to_file(c, PPM->fp);
}
/*  End of nf_color_write_to_ppm.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_scale                                                        *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (const struct nf_color *):                                          *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (struct nf_color):                                           *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_scale(const struct nf_color *c, double t)
{
    const unsigned char r = (unsigned char)(t * c->red);
    const unsigned char g = (unsigned char)(t * c->green);
    const unsigned char b = (unsigned char)(t * c->blue);
    return nf_color_create(r, g, b);
}
/*  End of nf_color_scale.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_scaleby                                                      *
 *  Purpose:                                                                  *
 *      Scales a color by a real number and stores the result in the input.   *
 *  Arguments:                                                                *
 *      c (struct nf_color *):                                                *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NF_INLINE void
nf_color_scaleby(struct nf_color *c, double t)
{
    c->red = (unsigned char)(t * c->red);
    c->green = (unsigned char)(t * c->green);
    c->blue = (unsigned char)(t * c->blue);
}
/*  End of nf_color_scaleby.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_normalize                                                    *
 *  Purpose:                                                                  *
 *      Normalizes the intensity of a color to 255.                           *
 *  Arguments:                                                                *
 *      c (const struct nf_color *):                                          *
 *          A pointer to the color to be normalized.                          *
 *  Outputs:                                                                  *
 *      normalized (struct nf_color):                                         *
 *          The color c normalized to intensity 255.                          *
 *  Method:                                                                   *
 *      Treat the ordered triple (r, g, b) as a vector and normalize.         *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_normalize(const struct nf_color *c)
{
    /*  Treat the color (r, g, b) as a three dimensional vector.              */
    const double x = (double)c->red;
    const double y = (double)c->green;
    const double z = (double)c->blue;

    /*  We normalize by using the reciprocal of the norm. Compute ||c||^2.    */
    const double norm_sq = x*x + y*y + z*z;

    /*  If the square of the norm is zero the input is black. Return black.   */
    if (norm_sq == 0.0)
        return *c;

    /*  Otherwise normalize the color to intensity 255.                       */
    else
    {
        /*  We normalize to intensity 255 so that red, green, and blue are    *
         *  treated as "unit" colors. Normalizing them does nothing.          */
        const double factor = 255.0 / sqrt(norm_sq);

        /*  color struct for the output.                                      */
        struct nf_color out;

        /*  Scale the RGB components of the input and return.                 */
        out.red = (unsigned char)(factor * x);
        out.green = (unsigned char)(factor * y);
        out.blue = (unsigned char)(factor * z);
        return out;
    }
}
/*  End of nf_color_normalize.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_normalize                                                    *
 *  Purpose:                                                                  *
 *      Normalizes the intensity of a color to 255.                           *
 *  Arguments:                                                                *
 *      c (struct nf_color *):                                                *
 *          A pointer to the color to be normalized.                          *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Treat the ordered triple (r, g, b) as a vector and normalize.         *
 ******************************************************************************/
NF_INLINE void
nf_color_normalizeself(struct nf_color *c)
{
    /*  Treat the color (r, g, b) as a three dimensional vector.              */
    const double x = (double)c->red;
    const double y = (double)c->green;
    const double z = (double)c->blue;

    /*  We normalize by using the reciprocal of the norm. Compute ||c||^2.    */
    const double norm_sq = x*x + y*y + z*z;

    /*  If the square of the norm is zero the input is black. Return black.   */
    if (norm_sq == 0.0)
        return;

    /*  Otherwise normalize the color to intensity 255.                       */
    else
    {
        /*  We normalize to intensity 255 so that red, green, and blue are    *
         *  treated as "unit" colors. Normalizing them does nothing.          */
        const double factor = 255.0 / sqrt(norm_sq);

        /*  Scale the RGB components of the input and return.                 */
        c->red = (unsigned char)(factor * x);
        c->green = (unsigned char)(factor * y);
        c->blue = (unsigned char)(factor * z);
    }
}
/*  End of nf_color_normalizeself.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_negate_channel                                                     *
 *  Purpose:                                                                  *
 *      Negates a color channel. Black maps to white, white maps to black.    *
 *  Arguments:                                                                *
 *      channel (unsigned char *):                                            *
 *          A color channel for a color. Red, green, or blue.                 *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      For non-zero colors, negate the input. For zero set to 255.           *
 ******************************************************************************/
NF_INLINE void
nf_negate_channel(unsigned char *channel)
{
    /*  Negating black does nothing since -0 = 0. Set to 255.                 */
    if (*channel == 0x00U)
        *channel = 0xFFU;

    /*  All other colors can be safely negated.                               */
    else
      *channel = -*channel;
}
/*  End of nf_negate_channel.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_negate                                                       *
 *  Purpose:                                                                  *
 *      Negates all channels of a color.                                      *
 *  Arguments:                                                                *
 *      c (struct nf_color *):                                                *
 *          The color to be negated.                                          *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Negate the red, green, and blue channels of the color.                *
 ******************************************************************************/
NF_INLINE void
nf_color_negate(struct nf_color *c)
{
    /*  Negate each channel in the color.                                     */
    nf_negate_channel(&c->red);
    nf_negate_channel(&c->green);
    nf_negate_channel(&c->blue);
}
/*  End of nf_color_negate.                                                   */

#endif
/*  End of include guard.                                                     */
