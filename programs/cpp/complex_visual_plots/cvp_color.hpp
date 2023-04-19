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
 *      Provides a class for using colors.                                    *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/18                                                        *
 ******************************************************************************/

/* Include guard to prevent including this file twice.                        */
#ifndef CVP_COLOR_HPP
#define CVP_COLOR_HPP

/*  File data type found here.                                                */
#include <cstdio>

/*  Basic class for creating and writing to PPM files.                        */
#include "cvp_ppm.hpp"

/*  Namespace for the mini-project. "Complex Visual Plots."                   */
namespace cvp {

    /*  Simple struct for working with colors in a PPM file.                  */
    class color {
        public:
            /*  A color is given by its RGB values.                           */
            unsigned char red, green, blue;

            /*  Empty constructor.                                            */
            color(void);

            /*  Constructor from three color values, RGB.                     */
            color(unsigned char r, unsigned char g, unsigned char b);

            /*  Write function, writes the color to a PPM file.               */
            inline void write(FILE *fp) const;

            /*  Write function, writes directly to a PPM struct.              */
            inline void write(cvp::ppm &PPM) const;

            /*  Scale a color by a positive real number. Used for darkening.  */
            inline color operator * (double t) const;

            /*  Scale a color by a positive real number.                      */
            inline void operator *= (double t);

            /*  Operator for adding colors. We average the components.        */
            inline color operator + (const cvp::color &c) const;

            /*  Operator for adding colors.                                   */
            inline void operator += (const cvp::color &c);
    };

    /*  Constant colors that are worth having.                                */
    namespace colors {
        inline color white(double t);
        inline color black(void);
        inline color red(double t);
        inline color green(double t);
        inline color blue(double t);
        inline color yellow(double t);
    }
    /*  End of namespace "colors".                                            */
}
/*  End of namespace "cvp".                                                   */

/*  Empty constructor, just return.                                           */
cvp::color::color(void)
{
    return;
}

/*  Constructor from three chars. Set the values for each color.              */
cvp::color::color(unsigned char r, unsigned char g, unsigned char b)
{
    red = r;
    green = g;
    blue = b;
}

/*  Function for writing a color to a PPM file.                               */
inline void cvp::color::write(FILE *fp) const
{
    std::fputc(int(red), fp);
    std::fputc(int(green), fp);
    std::fputc(int(blue), fp);
}

/*  Function for writing directly to a PPM struct.                            */
inline void cvp::color::write(cvp::ppm &PPM) const
{
    write(PPM.fp);
}

/*  Scale a color by a positive real number. Used for darkening.              */
inline cvp::color cvp::color::operator * (double t) const
{
    const unsigned char r = static_cast<unsigned char>(t*red);
    const unsigned char g = static_cast<unsigned char>(t*green);
    const unsigned char b = static_cast<unsigned char>(t*blue);
    return color(r, g, b);
}

/*  Scale a color by a positive real number. Used for darkening.              */
inline void cvp::color::operator *= (double t)
{
    red = static_cast<unsigned char>(t*red);
    green = static_cast<unsigned char>(t*green);
    blue = static_cast<unsigned char>(t*blue);
}

/*  Operator for adding colors. We take the average of the components.        */
inline cvp::color cvp::color::operator + (const cvp::color &c) const
{
    /*  Cast the values to doubles and take the average, component-wise.      */
    const double x =
        0.5 * (static_cast<double>(red) + (static_cast<double>(c.red)));

    const double y =
        0.5 * (static_cast<double>(green) + static_cast<double>(c.green));

    const double z =
        0.5 * (static_cast<double>(blue)  + static_cast<double>(c.blue));

    /*  Cast the double back to unsigned char's and return.                   */
    const unsigned char r = static_cast<unsigned char>(x);
    const unsigned char g = static_cast<unsigned char>(y);
    const unsigned char b = static_cast<unsigned char>(z);
    return color(r, g, b);
}

/*  Operator for adding colors. We take the average of the components.        */
inline void cvp::color::operator += (const cvp::color &c)
{
    /*  Cast the values to doubles and take the average, component-wise.      */
    const double x =
        0.5 * (static_cast<double>(red) + (static_cast<double>(c.red)));

    const double y =
        0.5 * (static_cast<double>(green) + static_cast<double>(c.green));

    const double z =
        0.5 * (static_cast<double>(blue)  + static_cast<double>(c.blue));

    /*  Cast the double back to unsigned char's and return.                   */
    red = static_cast<unsigned char>(x);
    green = static_cast<unsigned char>(y);
    blue = static_cast<unsigned char>(z);
}

/*  Function for creating a black-to-white gradient.                          */
inline cvp::color cvp::colors::white(double t)
{
    unsigned char val = static_cast<unsigned char>(255.0 * t);
    return cvp::color(val, val, val);
}

/*  Returns the color black in RGB format.                                    */
inline cvp::color cvp::colors::black(void)
{
    return color(0x00U, 0x00U, 0x00U);
}

/*  Returns the color red, scaled by the input t (0 <= t <= 1).               */
inline cvp::color cvp::colors::red(double t)
{
    unsigned char val = static_cast<unsigned char>(255.0 * t);
    return cvp::color(val, 0x00U, 0x00U);
}

/*  Returns the color green, scaled by the input t (0 <= t <= 1).             */
inline cvp::color cvp::colors::green(double t)
{
    unsigned char val = static_cast<unsigned char>(255.0 * t);
    return color(0x00U, val, 0x00U);
}

/*  Returns the color blue, scaled by the input t (0 <= t <= 1).              */
inline cvp::color cvp::colors::blue(double t)
{
    unsigned char val = static_cast<unsigned char>(255.0 * t);
    return color(0x00U, 0x00U, val);
}

/*  Returns the color yellow, scaled by the input t (0 <= t <= 1).            */
inline cvp::color cvp::colors::yellow(double t)
{
    unsigned char val = static_cast<unsigned char>(255.0 * t);
    return cvp::color(val, val, 0x00U);
}

#endif
/*  End of include guard.                                                     */
