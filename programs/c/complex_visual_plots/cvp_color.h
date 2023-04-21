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
 *  Date:   2023/04/21                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_COLOR_H
#define CVP_COLOR_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  CVP_INLINE macro found here.                                              */
#include "cvp_inline.h"

/*  Struct for working with PPM files found here.                             */
#include "cvp_ppm.h"

/*  Simple struct for working with colors in a PPM file.                      */
struct cvp_color {

    /*  A color is defined by its RGB values.                                 */
    unsigned char red, green, blue;
};

/*  Constant colors that are frequently used.                                 */
static const struct cvp_color cvp_white = {0xFFU, 0xFFU, 0xFFU};
static const struct cvp_color cvp_black = {0x00U, 0x00U, 0x00U};
static const struct cvp_color cvp_red = {0xFFU, 0x00U, 0x00U};
static const struct cvp_color cvp_green = {0x00U, 0xFFU, 0x00U};
static const struct cvp_color cvp_blue = {0x00U, 0x00U, 0xFFU};
static const struct cvp_color cvp_yellow = {0xFFU, 0xFFU, 0x00U};
static const struct cvp_color cvp_cyan = {0x00U, 0xFFU, 0xFFU};
static const struct cvp_color cvp_magenta = {0xFFU, 0x00U, 0xFFU};

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_color_create                                                      *
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
 *      c (struct cvp_color):                                                 *
 *          The color (r, g, b) in 24-bit RGB color space.                    *
 ******************************************************************************/
CVP_INLINE struct cvp_color
cvp_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    /*  Declare a variable for the output color.                              */
    struct cvp_color c;

    /*  Set the individual components and return.                             */
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}
/*  End of cvp_color_create.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_color_write_to_file                                               *
 *  Purpose:                                                                  *
 *      Writes a color to a FILE pointer.                                     *
 *  Arguments:                                                                *
 *      c (const struct cvp_color *):                                         *
 *          A pointer to a color.                                             *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
CVP_INLINE void
cvp_color_write_to_file(const struct cvp_color *c, FILE *fp)
{
    fputc(c->red, fp);
    fputc(c->green, fp);
    fputc(c->blue, fp);
}
/*  End of cvp_color_write_to_file.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_color_write_to_ppm                                                *
 *  Purpose:                                                                  *
 *      Writes a color to a ppm pointer.                                      *
 *  Arguments:                                                                *
 *      c (const struct cvp_color *):                                         *
 *          A pointer to a color.                                             *
 *      PPM (struct cvp_ppm *):                                               *
 *          A pointer to the ppm the color is being written to.               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
CVP_INLINE void
cvp_color_write_to_ppm(const struct cvp_color *c, struct cvp_ppm *PPM)
{
    cvp_color_write_to_file(c, PPM->fp);
}
/*  End of cvp_color_write_to_ppm.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_color_scale                                                       *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (const struct cvp_color *):                                         *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (struct cvp_color):                                          *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
CVP_INLINE struct cvp_color
cvp_color_scale(const struct cvp_color *c, double t)
{
    const unsigned char r = (unsigned char)(t * c->red);
    const unsigned char g = (unsigned char)(t * c->green);
    const unsigned char b = (unsigned char)(t * c->blue);
    return cvp_color_create(r, g, b);
}
/*  End of cvp_color_scale.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_color_scaleby                                                     *
 *  Purpose:                                                                  *
 *      Scales a color by a real number and stores the result in the input.   *
 *  Arguments:                                                                *
 *      c (struct cvp_color *):                                               *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
CVP_INLINE void
cvp_color_scaleby(struct cvp_color *c, double t)
{
    c->red = (unsigned char)(t * c->red);
    c->green = (unsigned char)(t * c->green);
    c->blue = (unsigned char)(t * c->blue);
}
/*  End of cvp_color_scaleby.                                                 */

#endif
/*  End of include guard.                                                     */
