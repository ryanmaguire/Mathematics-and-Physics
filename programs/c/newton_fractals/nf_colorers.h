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
 *  Date:   2023/04/20                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COLORERS_H
#define NF_COLORERS_H

/*  atan function provided here.                                              */
#include <math.h>

/*  NF_INLINE macro given here.                                               */
#include "nf_inline.h"

/*  Complex struct defined here.                                              */
#include "nf_complex.h"

/*  Struct for working with colors in RGB format.                             */
#include "nf_color.h"

/*  Various multiples of Pi.                                                  */
#include "nf_pi.h"

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_from_angle                                                   *
 *  Purpose:                                                                  *
 *      Creates a color from an angle between -pi and pi.                     *
 *  Arguments:                                                                *
 *      angle (double):                                                       *
 *          The angle, between -pi and pi, for the color.                     *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color corresponding to the angle.                             *
 *  Notes:                                                                    *
 *      The input should be between -pi and pi. Values less than -pi will     *
 *      return blue, and values greater than pi yield red.                    *
 *  Method:                                                                   *
 *      Create a gradient blue-cyan-green-yellow-red.                         *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_from_angle(double angle)
{
    /*  There are 1024 possible colors given by the gradient. This scale      *
     *  factor helps normalize the angle.                                     */
    const double gradient_factor = 1023.0 / NF_TWO_PI;

    /*  Scale the angle from (-pi, pi) to (0, 1023).                          */
    double val = (angle + NF_PI) * gradient_factor;

    /*  Color struct for the output.                                          */
    struct nf_color out;

    /*  Values outside the legal range (angle < -pi). Return blue.            */
    if (val < 0.0)
        return nf_blue;

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

    /*  Values outside the legal range (angle > +pi). Return red.             */
    else
        return nf_red;

    return out;
}
/*  End of nf_color_from_angle.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_wheel_from_angle                                             *
 *  Purpose:                                                                  *
 *      Creates a color on the color wheel from an angle between -pi and pi.  *
 *  Arguments:                                                                *
 *      angle (double):                                                       *
 *          The angle, between -pi and pi, for the color.                     *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color corresponding to the angle.                             *
 *  Notes:                                                                    *
 *      The input should be between -pi and pi. Values outside this range     *
 *      return blue.                                                          *
 *  Method:                                                                   *
 *      Create a gradient blue-cyan-green-yellow-red-magenta-blue.            *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_wheel_from_angle(double angle)
{
    /*  There are 1535 possible colors given by the gradient. This scale      *
     *  factor helps normalize the angle.                                     */
    const double gradient_factor = 1535.0 / NF_TWO_PI;

    /*  Scale the angle from (-pi, pi) to (0, 1023).                          */
    double val = (angle + NF_PI) * gradient_factor;

    /*  Lastly, a color for the output.                                       */
    struct nf_color out;

    /*  Values outside the legal range (angle < -pi). Return blue.            */
    if (val < 0.0)
        return nf_blue;

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
    else if (val < 1536.0)
    {
        /*  Shift val back to the range (0, 256).                             */
        val -= 1280.0;

        /*  Transition from magenta to blue.                                  */
        out.red = (unsigned char)(256.0 - val);
        out.green = 0x00U;
        out.blue = 0xFFU;
    }

    /*  Values outside the legal range (angle > +pi). Return blue.            */
    else
        return nf_blue;

    return out;
}
/*  End of nf_color_wheel_from_angle.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_scale_factor_from_complex                                    *
 *  Purpose:                                                                  *
 *      Compresses the modulus of complex numbers from [0, inf] to [0, 1].    *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      scale (double):                                                       *
 *          Scale factor such that scale*|z| < 1.                             *
 *  Method:                                                                   *
 *      Use the atan function to compress |z| to a finite range.              *
 ******************************************************************************/
NF_INLINE double
nf_color_scale_factor_from_complex(const struct nf_complex *z)
{
    /*  Compute the modulus of the input complex number.                      */
    const double abs_z = nf_complex_abs(z);

    /*  The atan function compresses the intensity to prohibit arbitrarily    *
     *  bright points. This allows the drawing to fit into an actual PPM.     */
    return atan(5.0*abs_z) / NF_HALF_PI;
}
/*  End of nf_color_scale_factor_from_complex.                                */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_from_argument                                                *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The color corresponds to  *
 *      the argument of the input, which is the angle made with the x axis.   *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the argument of the input.                     *
 *  Method:                                                                   *
 *      Compute the argument and use nf_color_from_angle.                     *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_from_argument(const struct nf_complex *z)
{
    /*  Compute the angle made by the complex number and use this to color z. */
    const double arg_z = nf_complex_arg(z);
    return nf_color_from_angle(arg_z);
}
/*  End of nf_color_from_argument.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_wheel_from_argument                                          *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The color corresponds to  *
 *      the argument of the input.                                            *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the argument of the input.                     *
 *  Method:                                                                   *
 *      Compute the argument and use nf_color_wheel_from_angle.               *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_wheel_from_argument(const struct nf_complex *z)
{
    /*  Compute the angle made by the complex number and use this to color z. */
    const double arg_z = nf_complex_arg(z);
    return nf_color_wheel_from_angle(arg_z);
}
/*  End of nf_color_wheel_from_argument.                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_from_complex                                                 *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument and scale by t.                       */
    struct nf_color out = nf_color_from_argument(z);
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_color_from_complex.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_wheel_from_complex                                           *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red-to-blue from the argument of    *
 *      the input and then scale this by the magnitude.                       *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_wheel_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument and scale by t.                       */
    struct nf_color out = nf_color_wheel_from_argument(z);
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_color_wheel_from_complex.                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_normalized_color_from_complex                                      *
 *  Purpose:                                                                  *
 *      Creates a color from a complex number with normalized intensity.      *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_normalized_color_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument.                                      */
    struct nf_color out = nf_color_from_argument(z);

    /*  Normalize the intensity of the color to 255.                          */
    nf_color_normalizeself(&out);

    /*  Scale the color by the scale factor and return.                       */
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_normalized_color_from_complex.                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_normalized_color_wheel_from_complex                                *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red-to-blue from the argument of    *
 *      the input and then scale this by the magnitude.                       *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_normalized_color_wheel_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument.                                      */
    struct nf_color out = nf_color_wheel_from_argument(z);

    /*  Normalize the intensity of the color to 255.                          */
    nf_color_normalizeself(&out);

    /*  Scale the color by the scale factor and return.                       */
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_normalized_color_wheel_from_complex.                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_from_modulus                                                 *
 *  Purpose:                                                                  *
 *      Creates an RGB color from the modulus of a complex number.            *
 *  Arguments:                                                                *
 *      z (nf_complex):                                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus of the input.                      *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red from the modulus of the input.  *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_from_modulus(const struct nf_complex *z)
{
    /*  Compute the modulus of the input complex number.                      */
    const double abs_z = nf_complex_abs(z);

    /*  Transform the modulus to [-pi, pi].                                   */
    const double angle = atan(abs_z) * 4.0 - NF_PI;

    /*  Treat this number as an angle on the color wheel.                     */
    return nf_color_from_angle(angle);
}
/*  End of nf_color_from_modulus.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_color_wheel_from_modulus                                           *
 *  Purpose:                                                                  *
 *      Creates an RGB color on the color wheel from the modulus of a complex *
 *      number. The modulus is scaled and shift to (-pi, pi) and this value   *
 *      is treated as an angle on the color wheel.                            *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by z.                                             *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red-to-blue from the modulus of the *
 *      input and return.                                                     *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_color_wheel_from_modulus(const struct nf_complex *z)
{
    /*  Compute the modulus of the input complex number.                      */
    const double abs_z = nf_complex_abs(z);

    /*  Transform the modulus to [-pi, pi].                                   */
    const double angle = atan(abs_z) * 4.0 - NF_PI;

    /*  Compute the color from the angle given.                               */
    return nf_color_wheel_from_angle(angle);
}
/*  End of nf_color_wheel_from_modulus.                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_negative_color_wheel_from_complex                                  *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument. The  *
 *      channels of the final color are negated and returned.                 *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_negative_color_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument.                                      */
    struct nf_color out = nf_color_from_argument(z);

    /*  Negate each channel of the color.                                     */
    nf_color_negate(&out);

    /*  Scale the color by the scale factor and return.                       */
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_negative_color_from_complex.                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_negative_color_wheel_from_complex                                  *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument. The  *
 *      channels of the final color are negated and returned.                 *
 *  Arguments:                                                                *
 *      z (const struct nf_complex *):                                        *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (struct nf_color):                                                  *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient blue-to-red-to-blue from the argument of    *
 *      the input and then scale this by the magnitude.                       *
 ******************************************************************************/
NF_INLINE struct nf_color
nf_negative_color_wheel_from_complex(const struct nf_complex *z)
{
    /*  Scale factor to darken the color based on the magnitude of z.         */
    const double t = nf_color_scale_factor_from_complex(z);

    /*  Get the color from the argument.                                      */
    struct nf_color out = nf_color_wheel_from_argument(z);

    /*  Negate each channel of the color.                                     */
    nf_color_negate(&out);

    /*  Scale the color by the scale factor and return.                       */
    nf_color_scaleby(&out, t);
    return out;
}
/*  End of nf_negative_color_wheel_from_complex.                              */

#endif
/*  End of include guard.                                                     */
