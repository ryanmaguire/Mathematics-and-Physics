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
 *      Provides routines for generating colors on the color wheel.           *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/20                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COLORERS_H
#define NF_COLORERS_H

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Struct for working with colors in RGB format.                             */
#include "nf_color.h"

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_from_angle                                                   *
 *  Purpose:                                                                  *
 *      Creates an RGB color from an angle between 0 and 2 pi.                *
 *  Arguments:                                                                *
 *      angle (double):                                                       *
 *          A real number between 0 and 2 pi.                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color in the spectrum blue-to-green-to-red given by the angle.*
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue from the angle given.           *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_from_angle(double angle)
{
    /*  There are 1024 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const double gradient_factor = 1023.0 / (2.0 * M_PI);

    /*  Scale the argument from (0, 2 pi) to (0, 1023).                       */
    double val = angle * gradient_factor;

    /*  Lastly, a color for the output.                                       */
    struct nf_color out;

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0)
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
    else
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 768.0;

        /*  Transition from yellow to red.                                    */
        out.red = 0xFFU;
        out.green = (unsigned char)(256.0 - val);
        out.blue = 0x00U;
    }

    return out;
}
/*  End of nf_color_from_angle.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_wheel_from_angle                                             *
 *  Purpose:                                                                  *
 *      Creates an RGB color from an angle between 0 and 2 pi.                *
 *  Arguments:                                                                *
 *      angle (double):                                                       *
 *          A real number between 0 and 2 pi.                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the angle on the color wheel.                  *
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue-to-red from the angle given.    *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_wheel_from_angle(double angle)
{
    /*  There are 1535 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const double gradient_factor = 1535.0 / (2.0 * M_PI);

    /*  Scale the argument from (0, 2 pi) to (0, 1535).                       */
    double val = angle * gradient_factor;

    /*  Lastly, a color for the output.                                       */
    struct nf_color out;

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0)
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

    /*  For 1024 <= val < 1280 transition from red to magenta.                */
    else if (val < 1280.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 1024.0;

        /*  Gradient from red to magenta.                                     */
        out.red = 0xFFU;
        out.green = 0x00U;
        out.blue = (unsigned char)val;
    }

    /*  Finally transition from magenta back to blue.                         */
    else
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 1280.0;

        /*  Transition from magenta to blue.                                  */
        out.red = (unsigned char)(256.0 - val);
        out.green = 0x00U;
        out.blue = 0xFFU;
    }

    return out;
}
/*  End of nf_color_wheel_from_angle.                                         */

#endif
/*  End of include guard.                                                     */
