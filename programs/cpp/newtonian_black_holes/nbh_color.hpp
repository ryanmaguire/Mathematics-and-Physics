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
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/* Include guard to prevent including this file twice.                        */
#ifndef NBH_COLOR_HPP
#define NBH_COLOR_HPP

/*  File data type found here.                                                */
#include <cstdio>

#include "nbh_vector.hpp"
#include "nbh_ppm.hpp"

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  Simple struct for working with colors in a PPM file.                  */
    struct color {

        /*  A color is given by its RGB values.                               */
        unsigned char red, green, blue;

        /*  Empty constructor.                                                */
        color(void);

        /*  Constructor from three color values, RGB.                         */
        color(unsigned char r, unsigned char g, unsigned char b);

        /*  Write function, writes the color to a PPM file.                   */
        inline void write(FILE *fp) const;

        /*  Write function, writes directly to a PPM struct.                  */
        inline void write(nbh::ppm &PPM) const;

        /*  Scale a color by a positive real number. Used for darkening.      */
        inline color operator * (double t) const;

        /*  Scale a color by a positive real number.                          */
        inline void operator *= (double t);
    };

    /*  Empty constructor, just return.                                       */
    color::color(void)
    {
        return;
    }

    /*  Constructor from three chars. Set the values for each color.          */
    color::color(unsigned char r, unsigned char g, unsigned char b)
    {
        red = r;
        green = g;
        blue = b;
    }

    /*  Function for writing a color to a PPM file.                           */
    inline void color::write(FILE *fp) const
    {
        std::fputc(int(red), fp);
        std::fputc(int(green), fp);
        std::fputc(int(blue), fp);
    }

    /*  Function for writing directly to a PPM struct.                        */
    inline void color::write(nbh::ppm &PPM) const
    {
        write(PPM.fp);
    }

    /*  Scale a color by a positive real number. Used for darkening.          */
    inline color color::operator * (double t) const
    {
        const unsigned char r = static_cast<unsigned char>(t*red);
        const unsigned char g = static_cast<unsigned char>(t*green);
        const unsigned char b = static_cast<unsigned char>(t*blue);
        return color(r, g, b);
    }

    /*  Scale a color by a positive real number. Used for darkening.          */
    inline void color::operator *= (double t)
    {
        red = static_cast<unsigned char>(t*red);
        green = static_cast<unsigned char>(t*green);
        blue = static_cast<unsigned char>(t*blue);
    }

    /*  Constant colors that are worth having.                                */
    namespace colors {
        inline color white(void)
        {
            return color(0xFFU, 0xFFU, 0xFFU);
        }

        inline color black(void)
        {
            return color(0x00U, 0x00U, 0x00U);
        }

        inline color red(void)
        {
            return color(0xFFU, 0x00U, 0x00U);
        }

        inline color green(void)
        {
            return color(0x00U, 0xFFU, 0x00U);
        }

        inline color blue(void)
        {
            return color(0x00U, 0x00U, 0xFFU);
        }
    }
    /*  End of namespace "colors".                                            */

    /*  Function for creating a checker board pattern on the detector.        */
    inline color checker_board_color(const nbh::vec3 &v)
    {
        if (static_cast<unsigned>(std::ceil(v.x) + std::ceil(v.y)) & 1)
            return colors::white();
        else
            return colors::red();
    }
}
/*  End of "nbh" namespace.                                                   */

#endif
/*  End of include guard.                                                     */
