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
 *      Provides routines for coloring complex functions.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/18                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_COLORERS_HPP
#define CVP_COLORERS_HPP

/*  atan function provided here.                                              */
#include <cmath>

/*  Complex class defined here.                                               */
#include "cvp_complex.hpp"

/*  Class for working with colors in RGB format.                              */
#include "cvp_color.hpp"

/*  Namespace for this mini-project. "Complex Visual Plots."                  */
namespace cvp {
    inline cvp::color color_from_complex(cvp::complex z);
    inline cvp::color color_wheel_from_complex(cvp::complex z);
}

/******************************************************************************
 *  Function:                                                                 *
 *      color_from_complex                                                    *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (cvp::complex):                                                     *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (cvp::color):                                                       *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
inline cvp::color cvp::color_from_complex(cvp::complex z)
{
    /*  There are 1024 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const double gradient_factor = 1023.0 / M_2_PI;

    /*  Compute the argument and modulus of the input complex number.         */
    const double arg_z = z.arg();
    const double abs_z = z.abs();

    /*  Scale the argument from (-pi, pi) to (0, 1023).                       */
    double val = (arg_z + M_PI) * gradient_factor;

    /*  The atan function compresses the intensity to prohibit arbitrarily    *
     *  bright points. This allows the drawing to fit into an actual PPM.     */
    const double t = std::atan(5.0*abs_z) / M_PI_2;

    /*  Lastly, a color for the output.                                       */
    cvp::color out;

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = static_cast<unsigned char>(val);
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
        out.blue = static_cast<unsigned char>(256.0 - val);
    }

    /*  For 512 <= val < 768 transition from green to yellow.                 */
    else if (val < 768.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 512.0;

        /*  Transition from green to yellow.                                  */
        out.red = static_cast<unsigned char>(val);
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
        out.green = static_cast<unsigned char>(256.0 - val);
        out.blue = 0x00U;
    }

    /*  Scale the color by the atan factor and return.                        */
    return out * t;
}
/*  End of color_from_complex.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      color_wheel_from_complex                                              *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (cvp::complex):                                                     *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (cvp::color):                                                       *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
inline cvp::color cvp::color_wheel_from_complex(cvp::complex z)
{
    /*  There are 1535 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const double gradient_factor = 1535.0 / (2.0 * M_PI);

    /*  Compute the argument and modulus of the input complex number.         */
    const double arg_z = z.arg();
    const double abs_z = z.abs();

    /*  Scale the argument from (-pi, pi) to (0, 1535).                       */
    double val = (arg_z + M_PI) * gradient_factor;

    /*  The atan function compresses the intensity to prohibit arbitrarily    *
     *  bright points. This allows the drawing to fit into an actual PPM.     */
    const double t = std::atan(5.0*abs_z) / (0.5 * M_PI);

    /*  Lastly, a color for the output.                                       */
    cvp::color out;

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = static_cast<unsigned char>(val);
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
        out.blue = static_cast<unsigned char>(256.0 - val);
    }

    /*  For 512 <= val < 768 transition from green to yellow.                 */
    else if (val < 768.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 512.0;

        /*  Transition from green to yellow.                                  */
        out.red = static_cast<unsigned char>(val);
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
        out.green = static_cast<unsigned char>(256.0 - val);
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
        out.blue = static_cast<unsigned char>(val);
    }

    /*  Finally transition from magenta back to blue.                         */
    else
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 1280.0;

        /*  Transition from magenta to blue.                                  */
        out.red = static_cast<unsigned char>(256.0 - val);
        out.green = 0x00U;
        out.blue = 0xFFU;
    }

    /*  Scale the color by the atan factor and return.                        */
    return out * t;
}
/*  End of color_wheel_from_complex.                                          */

#endif
/*  End of include guard.                                                     */
