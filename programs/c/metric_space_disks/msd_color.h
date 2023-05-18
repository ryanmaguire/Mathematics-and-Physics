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
 *  Date:   2023/05/17                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef MSD_COLOR_H
#define MSD_COLOR_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  MSD_INLINE macro found here.                                              */
#include "msd_inline.h"

/*  Struct for working with PPM files found here.                             */
#include "msd_ppm.h"

/*  Constants used throughout the project defined here.                       */
#include "msd_setup.h"

/*  sqrt function provided here.                                              */
#include <math.h>

/*  Simple struct for working with colors in a PPM file.                      */
struct msd_color {

    /*  A color is defined by its RGB values.                                 */
    unsigned char red, green, blue;
};

/*  Constant colors that are frequently used.                                 */
static const struct msd_color msd_white = {0xFFU, 0xFFU, 0xFFU};
static const struct msd_color msd_black = {0x00U, 0x00U, 0x00U};
static const struct msd_color msd_red = {0xFFU, 0x00U, 0x00U};
static const struct msd_color msd_green = {0x00U, 0xFFU, 0x00U};
static const struct msd_color msd_blue = {0x00U, 0x00U, 0xFFU};
static const struct msd_color msd_yellow = {0xFFU, 0xFFU, 0x00U};
static const struct msd_color msd_cyan = {0x00U, 0xFFU, 0xFFU};
static const struct msd_color msd_magenta = {0xFFU, 0x00U, 0xFFU};

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_create                                                      *
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
 *      c (struct msd_color):                                                 *
 *          The color (r, g, b) in 24-bit RGB color space.                    *
 ******************************************************************************/
MSD_INLINE struct msd_color
msd_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    /*  Declare a variable for the output color.                              */
    struct msd_color c;

    /*  Set the individual components and return.                             */
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}
/*  End of msd_color_create.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_write_to_file                                               *
 *  Purpose:                                                                  *
 *      Writes a color to a FILE pointer.                                     *
 *  Arguments:                                                                *
 *      c (const struct msd_color *):                                         *
 *          A pointer to a color.                                             *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
MSD_INLINE void
msd_color_write_to_file(const struct msd_color *c, FILE *fp)
{
    fputc(c->red, fp);
    fputc(c->green, fp);
    fputc(c->blue, fp);
}
/*  End of msd_color_write_to_file.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_write_to_ppm                                                *
 *  Purpose:                                                                  *
 *      Writes a color to a ppm pointer.                                      *
 *  Arguments:                                                                *
 *      c (const struct msd_color *):                                         *
 *          A pointer to a color.                                             *
 *      PPM (struct msd_ppm *):                                               *
 *          A pointer to the ppm the color is being written to.               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
MSD_INLINE void
msd_color_write_to_ppm(const struct msd_color *c, struct msd_ppm *PPM)
{
    msd_color_write_to_file(c, PPM->fp);
}
/*  End of msd_color_write_to_ppm.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_scale                                                       *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (const struct msd_color *):                                         *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (struct msd_color):                                          *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
MSD_INLINE struct msd_color
msd_color_scale(const struct msd_color *c, double t)
{
    const unsigned char r = (unsigned char)(t * c->red);
    const unsigned char g = (unsigned char)(t * c->green);
    const unsigned char b = (unsigned char)(t * c->blue);
    return msd_color_create(r, g, b);
}
/*  End of msd_color_scale.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_scaleby                                                     *
 *  Purpose:                                                                  *
 *      Scales a color by a real number and stores the result in the input.   *
 *  Arguments:                                                                *
 *      c (struct msd_color *):                                               *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
MSD_INLINE void
msd_color_scaleby(struct msd_color *c, double t)
{
    c->red = (unsigned char)(t * c->red);
    c->green = (unsigned char)(t * c->green);
    c->blue = (unsigned char)(t * c->blue);
}
/*  End of msd_color_scaleby.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_normalize                                                   *
 *  Purpose:                                                                  *
 *      Normalizes the intensity of a color to 255.                           *
 *  Arguments:                                                                *
 *      c (const struct msd_color *):                                         *
 *          A pointer to the color to be normalized.                          *
 *  Outputs:                                                                  *
 *      normalized (struct msd_color):                                        *
 *          The color c normalized to intensity 255.                          *
 *  Method:                                                                   *
 *      Treat the ordered triple (r, g, b) as a vector and normalize.         *
 ******************************************************************************/
MSD_INLINE struct msd_color
msd_color_normalize(const struct msd_color *c)
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
        struct msd_color out;

        /*  Scale the RGB components of the input and return.                 */
        out.red = (unsigned char)(factor * x);
        out.green = (unsigned char)(factor * y);
        out.blue = (unsigned char)(factor * z);
        return out;
    }
}
/*  End of msd_color_normalize.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_normalize                                                   *
 *  Purpose:                                                                  *
 *      Normalizes the intensity of a color to 255.                           *
 *  Arguments:                                                                *
 *      c (struct msd_color *):                                               *
 *          A pointer to the color to be normalized.                          *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Treat the ordered triple (r, g, b) as a vector and normalize.         *
 ******************************************************************************/
MSD_INLINE void
msd_color_normalizeself(struct msd_color *c)
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
/*  End of msd_color_normalizeself.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_negate_channel                                                    *
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
MSD_INLINE void
msd_negate_channel(unsigned char *channel)
{
    /*  Negating black does nothing since -0 = 0. Set to 255.                 */
    if (*channel == 0x00U)
        *channel = 0xFFU;

    /*  All other colors can be safely negated.                               */
    else
      *channel = -*channel;
}
/*  End of msd_negate_channel.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_color_negate                                                      *
 *  Purpose:                                                                  *
 *      Negates all channels of a color.                                      *
 *  Arguments:                                                                *
 *      c (struct msd_color *):                                               *
 *          The color to be negated.                                          *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Negate the red, green, and blue channels of the color.                *
 ******************************************************************************/
MSD_INLINE void
msd_color_negate(struct msd_color *c)
{
    /*  Negate each channel in the color.                                     */
    msd_negate_channel(&c->red);
    msd_negate_channel(&c->green);
    msd_negate_channel(&c->blue);
}
/*  End of msd_color_negate.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_linear_rainbow_gradient                                           *
 *  Purpose:                                                                  *
 *      Creates a linear rainbow gradient.                                    *
 *  Arguments:                                                                *
 *      x_val (double):                                                       *
 *          The value for the color.                                          *
 *      min_val (double):                                                     *
 *          The minimum allowed value for the gradient.                       *
 *      max_val (double):                                                     *
 *          The maximum allowed value for the gradient.                       *
 *  Outputs:                                                                  *
 *      c (struct msd_color):                                                 *
 *          The color corresponding to val.                                   *
 ******************************************************************************/
MSD_INLINE struct msd_color
msd_linear_rainbow_gradient(double x_val, double min_val, double max_val)
{
    /*  Scale [min_val, max_val] to [0, 1024].                                */
    double val = 1024.0 * (x_val - min_val) / (max_val - min_val);

    /*  Color struct for the output.                                          */
    struct msd_color out;

    /*  Values outside the legal range. Return blue.                          */
    if (val < 0.0)
        return msd_blue;

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    else if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = (unsigned char)val;
        out.blue = 0xFFU;
    }

    /*  For 256 <= val < 512 transition from cyan to green.                   */
    else if (val < 512.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 256.0;

        /*  Transition from cyan to green.                                    */
        out.red = 0x00U;
        out.green = 0xFFU;
        out.blue = (unsigned char)(256.0 - val);
    }

    /*  For 512 <= val < 768 transition from green to yellow.                 */
    else if (val < 768.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 512.0;

        /*  Transition from green to yellow.                                  */
        out.red = (unsigned char)val;
        out.green = 0xFFU;
        out.blue = 0x00U;
    }

    /*  For 768 <= val < 1024 transition from yellow to red.                  */
    else if (val < 1024.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 768.0;

        /*  Transition from yellow to red.                                    */
        out.red = 0xFFU;
        out.green = (unsigned char)(256.0 - val);
        out.blue = 0x00U;
    }

    /*  Values outside the legal range. Return red.                           */
    else
        return msd_red;

    return out;
}
/*  End of msd_linear_rainbow_gradient.                                       */

#endif
/*  End of include guard.                                                     */
