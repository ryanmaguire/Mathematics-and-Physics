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
 *  Date:   2023/04/04                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_COLOR_H
#define NBH_COLOR_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  NBH_INLINE macro found here.                                              */
#include "nbh_inline.h"

/*  6D vector struct given here.                                              */
#include "nbh_vec6.h"

/*  Struct for working with PPM files found here.                             */
#include "nbh_ppm.h"

/*  Constants used throughout the project defined here.                       */
#include "nbh_setup.h"

/*  ceil and atan functions provided here.                                    */
#include <math.h>

/*  Simple struct for working with colors in a PPM file.                      */
struct nbh_color {

    /*  A color is defined by its RGB values.                                 */
    unsigned char red, green, blue;
};

/*  Constant colors that are frequently used.                                 */
static const struct nbh_color nbh_white = {0xFFU, 0xFFU, 0xFFU};
static const struct nbh_color nbh_black = {0x00U, 0x00U, 0x00U};
static const struct nbh_color nbh_red = {0xFFU, 0x00U, 0x00U};
static const struct nbh_color nbh_green = {0x00U, 0xFFU, 0x00U};
static const struct nbh_color nbh_blue = {0x00U, 0x00U, 0xFFU};
static const struct nbh_color nbh_yellow = {0xFFU, 0xFFU, 0x00U};
static const struct nbh_color nbh_cyan = {0x00U, 0xFFU, 0xFFU};
static const struct nbh_color nbh_magenta = {0xFFU, 0x00U, 0xFFU};

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_create                                                      *
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
 *      c (struct nbh_color):                                                 *
 *          The color (r, g, b) in 24-bit RGB color space.                    *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    /*  Declare a variable for the output color.                              */
    struct nbh_color c;

    /*  Set the individual components and return.                             */
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}
/*  End of nbh_color_create.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_write_to_file                                               *
 *  Purpose:                                                                  *
 *      Writes a color to a FILE pointer.                                     *
 *  Arguments:                                                                *
 *      c (const struct nbh_color *):                                         *
 *          A pointer to a color.                                             *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NBH_INLINE void
nbh_color_write_to_file(const struct nbh_color *c, FILE *fp)
{
    fputc(c->red, fp);
    fputc(c->green, fp);
    fputc(c->blue, fp);
}
/*  End of nbh_color_write_to_file.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_write_to_ppm                                                *
 *  Purpose:                                                                  *
 *      Writes a color to a ppm pointer.                                      *
 *  Arguments:                                                                *
 *      c (const struct nbh_color *):                                         *
 *          A pointer to a color.                                             *
 *      PPM (struct nbh_ppm *):                                               *
 *          A pointer to the ppm the color is being written to.               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NBH_INLINE void
nbh_color_write_to_ppm(const struct nbh_color *c, struct nbh_ppm *PPM)
{
    nbh_color_write_to_file(c, PPM->fp);
}
/*  End of nbh_color_write_to_ppm.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_scale                                                       *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (const struct nbh_color *):                                         *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (struct nbh_color):                                          *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_color_scale(const struct nbh_color *c, double t)
{
    const unsigned char r = (unsigned char)(t * c->red);
    const unsigned char g = (unsigned char)(t * c->green);
    const unsigned char b = (unsigned char)(t * c->blue);
    return nbh_color_create(r, g, b);
}
/*  End of nbh_color_scale.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_scaleby                                                     *
 *  Purpose:                                                                  *
 *      Scales a color by a real number and stores the result in the input.   *
 *  Arguments:                                                                *
 *      c (struct nbh_color *):                                               *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NBH_INLINE void
nbh_color_scaleby(struct nbh_color *c, double t)
{
    c->red = (unsigned char)(t * c->red);
    c->green = (unsigned char)(t * c->green);
    c->blue = (unsigned char)(t * c->blue);
}
/*  End of nbh_color_scaleby.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_add                                                         *
 *  Purpose:                                                                  *
 *      Adds two colors by averaging over their components.                   *
 *  Arguments:                                                                *
 *      c0 (const struct nbh_color *):                                        *
 *          A pointer to the first color.                                     *
 *      c1 (const struct nbh_color *):                                        *
 *          A pointer to the second color.                                    *
 *  Outputs:                                                                  *
 *      sum (struct nbh_color):                                               *
 *          The sum of the two colors.                                        *
 *  Method:                                                                   *
 *      Convert the components to doubles and take their average.             *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_color_add(const struct nbh_color *c0, const struct nbh_color *c1)
{
    /*  Declare a variable for the output.                                    */
    struct nbh_color sum;

    /*  Avoid overflow by converting to doubles and then taking the average.  */
    const double r = 0.5*((double)c0->red + (double)c1->red);
    const double g = 0.5*((double)c0->green + (double)c1->green);
    const double b = 0.5*((double)c0->blue + (double)c1->blue);

    /*  Convert back to unsigned char's and store these in the color.         */
    sum.red = (unsigned char)r;
    sum.green = (unsigned char)g;
    sum.blue = (unsigned char)b;
    return sum;
}
/*  End of nbh_color_add.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_addto                                                       *
 *  Purpose:                                                                  *
 *      Adds two colors by averaging over their components.                   *
 *  Arguments:                                                                *
 *      c0 (struct nbh_color *):                                              *
 *          A pointer to the first color.                                     *
 *      c1 (const struct nbh_color *):                                        *
 *          A pointer to the second color.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Convert the components to doubles and take their average.             *
 ******************************************************************************/
NBH_INLINE void
nbh_color_addto(struct nbh_color *c0, const struct nbh_color *c1)
{
    /*  Avoid overflow by converting to doubles and then averaging.           */
    const double r = 0.5*((double)c0->red + (double)c1->red);
    const double g = 0.5*((double)c0->green + (double)c1->green);
    const double b = 0.5*((double)c0->blue + (double)c1->blue);

    /*  Convert back to unsigned char and store the result in the first color.*/
    c0->red = (unsigned char)r;
    c0->green = (unsigned char)g;
    c0->blue = (unsigned char)b;
}
/*  End of nbh_color_addto.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_checker_board                                                     *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector.                      *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_checker_board(const struct nbh_vec6 *u)
{
    /*  Factor for darkening the checker board.                               */
    const double cfact = nbh_setup_z_detector_sq / nbh_vec3_normsq(&u->p);

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    else if ((unsigned)(ceil(u->p.x) + ceil(u->p.y)) & 1U)
        return nbh_color_scale(&nbh_white, cfact);
    else
        return nbh_color_scale(&nbh_red, cfact);
}
/*  End of nbh_checker_board.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_bright_checker_board                                              *
 *  Purpose:                                                                  *
 *      Creates a brighter checker-board pattern on the detector.             *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_bright_checker_board(const struct nbh_vec6 *u)
{
    /*  Factor for darkening the checker board.                               */
    const double cfact =
        0.5*(nbh_setup_z_detector_sq/nbh_vec3_normsq(&u->p) + 1.0);

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    else if ((unsigned)(ceil(u->p.x) + ceil(u->p.y)) & 1U)
        return nbh_color_scale(&nbh_white, cfact);
    else
        return nbh_color_scale(&nbh_red, cfact);
}
/*  End of nbh_bright_checker_board.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_checker_board_four                                                *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector with four colors.     *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_checker_board_four(const struct nbh_vec6 *u)
{
    /*  Factor for darkening the checker board.                               */
    const double cfact = nbh_setup_z_detector_sq / nbh_vec3_normsq(&u->p);

    /*  Integers that determine the color.                                    */
    const unsigned int nx = (unsigned)(ceil(u->p.x)) & 1U;
    const unsigned int ny = (unsigned)(ceil(u->p.y)) & 1U;
    const unsigned int n = nx + (ny << 1U);

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    switch (n)
    {
        case 0:
            return nbh_color_scale(&nbh_white, cfact);
        case 1:
            return nbh_color_scale(&nbh_yellow, cfact);
        case 2:
            return nbh_color_scale(&nbh_green, cfact);
        default:
            return nbh_color_scale(&nbh_red, cfact);
    }
}
/*  End of nbh_checker_board_four.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_checker_board_four_highlight                                      *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector with four colors and  *
 *      highlights the origin blue.                                           *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_checker_board_four_highlight(const struct nbh_vec6 *u)
{
    /*  Factor for darkening the checker board.                               */
    const double cfact = nbh_setup_z_detector_sq / nbh_vec3_normsq(&u->p);

    /*  Integers that determine the color.                                    */
    const unsigned int nx = (unsigned)(ceil(u->p.x)) & 1U;
    const unsigned int ny = (unsigned)(ceil(u->p.y)) & 1U;
    const unsigned int n = nx + (ny << 1U);

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  If the center of the plane was hit, color blue.                       */
    else if (nbh_vec3_rhosq(&u->p) < nbh_setup_highlight_threshold)
        return nbh_blue;

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    switch (n)
    {
        case 0:
            return nbh_color_scale(&nbh_white, cfact);
        case 1:
            return nbh_color_scale(&nbh_yellow, cfact);
        case 2:
            return nbh_color_scale(&nbh_green, cfact);
        default:
            return nbh_color_scale(&nbh_red, cfact);
    }
}
/*  End of nbh_checker_board_four_highlight.                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_checker_board_highlight                                           *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector and highlights the    *
 *      origin blue.                                                          *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_checker_board_highlight(const struct nbh_vec6 *u)
{
    /*  Factor for darkening the checker board.                               */
    const double cfact = nbh_setup_z_detector_sq / nbh_vec3_normsq(&u->p);

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  If the center of the plane was hit, color blue.                       */
    else if (nbh_vec3_rhosq(&u->p) < nbh_setup_highlight_threshold)
        return nbh_blue;

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    else if ((unsigned)(ceil(u->p.x) + ceil(u->p.y)) & 1U)
        return nbh_color_scale(&nbh_white, cfact);
    else
        return nbh_color_scale(&nbh_red, cfact);
}
/*  End of nbh_checker_board_highlight.                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_angle_gradient                                                    *
 *  Purpose:                                                                  *
 *      Creates a rainbow gradient of color based on the angle the velocity   *
 *      vector of the particle makes with the detector on impact.             *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_angle_gradient(const struct nbh_vec6 *u)
{
    /*  Declare unsigned char's for computing the output color.               */
    unsigned char red, green, blue;

    /*  We want the zenith angle of the velocity vector. This can be          *
     *  computed using the cylindrical coordinates of the vector.             */
    const double angle = atan2(fabs(u->v.z), nbh_vec3_rho(&u->v));

    /*  Scale the angle so that it falls between 0 and 255.                   */
    const double scaled = 255.0 * angle / M_PI_2;

    /*  Use an RGB rainbow gradient to color the current pixel. We'll set     *
     *  blue to correspond to the least value and red for the greatest,       *
     *  with a continuous gradient in between. First blue to cyan.            */
    if (scaled < 64.0)
    {
        red = 0x00U;
        green = (unsigned char)(4.0*scaled);
        blue = 0xFFU;
    }

    /*  Next, cyan to green.                                                  */
    else if (scaled < 128.0)
    {
        red = 0x00U;
        green = 0xFFU;
        blue = (unsigned char)(255.0 - 4.0*(scaled - 64.0));
    }

    /*  Green to yellow.                                                      */
    else if (scaled < 192.0)
    {
        red = (unsigned char)(4.0*(scaled - 128.0));
        green = 0xFFU;
        blue = 0x00U;
    }

    /*  Yellow to red.                                                        */
    else if (scaled < 255.0)
    {
        red = 0xFFU;
        green = (unsigned char)(255.0 - 4.0*(scaled - 192.0));
        blue = 0x00U;
    }

    /*  And lastly, red.                                                      */
    else
    {
        red = 0xFFU;
        green = 0x00U;
        blue = 0x00U;
    }

    return nbh_color_create(red, green, blue);
}
/*  End of nbh_angle_gradient.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_color_gradient_checkerboard                                       *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector and adds the rainbow  *
 *      gradient defined in nbh_angle_gradient.                               *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (struct nbh_color):                                                 *
 *          The color given on the detector.                                  *
 ******************************************************************************/
NBH_INLINE struct nbh_color
nbh_color_gradient_checkerboard(const struct nbh_vec6 *u)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_color rainbow, checker_board;

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u->p.z > nbh_setup_z_detector)
        return nbh_black;

    /*  Take the average of the checkerboard and the raindbow gradient.       */
    rainbow = nbh_angle_gradient(u);
    checker_board = nbh_bright_checker_board(u);
    return nbh_color_add(&checker_board, &rainbow);
}
/*  End of nbh_color_gradient_checkerboard.                                   */

#endif
/*  End of include guard.                                                     */
