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

/*  6D vector struct given here.                                              */
#include "nbh_vec6.hpp"

/*  Struct for working with PPM files found here.                             */
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

        /*  Operator for adding colors. We average the components.            */
        inline color operator + (nbh::color c);

        /*  Operator for adding colors.                                       */
        inline void operator += (nbh::color c);
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

    /*  Operator for adding colors. We take the average of the components.    */
    inline color color::operator + (color c)
    {
        /*  Cast the values to doubles and take the average, component-wise.  */
        const double x =
            0.5 * (static_cast<double>(red) + (static_cast<double>(c.red)));

        const double y =
            0.5 * (static_cast<double>(green) + static_cast<double>(c.green));

        const double z =
            0.5 * (static_cast<double>(blue)  + static_cast<double>(c.blue));

        /*  Cast the double back to unsigned char's and return.               */
        const unsigned char r = static_cast<unsigned char>(x);
        const unsigned char g = static_cast<unsigned char>(y);
        const unsigned char b = static_cast<unsigned char>(z);
        return color(r, g, b);
    }

    /*  Operator for adding colors. We take the average of the components.    */
    inline void color::operator += (color c)
    {
        /*  Cast the values to doubles and take the average, component-wise.  */
        const double x =
            0.5 * (static_cast<double>(red) + (static_cast<double>(c.red)));

        const double y =
            0.5 * (static_cast<double>(green) + static_cast<double>(c.green));

        const double z =
            0.5 * (static_cast<double>(blue)  + static_cast<double>(c.blue));

        /*  Cast the double back to unsigned char's and return.               */
        red = static_cast<unsigned char>(x);
        green = static_cast<unsigned char>(y);
        blue = static_cast<unsigned char>(z);
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

        inline color yellow(void)
        {
            return color(0xFFU, 0xFFU, 0x00U);
        }
    }
    /*  End of namespace "colors".                                            */

    /*  Function for creating a checker board pattern on the detector.        */
    inline color checker_board(const nbh::vec6 &u)
    {
        /*  Factor for darkening the checker board.                           */
        const double cfact = nbh::setup::z_detector_sq/u.p.normsq();

        /*  If the photon didn't make it, color the pixel black.              */
        if (u.p.z > nbh::setup::z_detector)
            return nbh::colors::black();

        /*  Otherwise use a bit-wise trick to color the plane.                */
        else if (static_cast<unsigned>(std::ceil(u.p.x)+std::ceil(u.p.y)) & 1U)
            return colors::white() * cfact;
        else
            return colors::red() * cfact;
    }

    /*  Brighter version of the previous checker board.                       */
    inline color bright_checker_board(const nbh::vec6 &u)
    {
        /*  Factor for darkening the checker board.                           */
        const double cfact = 0.5*(nbh::setup::z_detector_sq/u.p.normsq() + 1.0);

        /*  If the photon didn't make it, color the pixel black.              */
        if (u.p.z > nbh::setup::z_detector)
            return nbh::colors::black();

        /*  Otherwise use a bit-wise trick to color the plane.                */
        else if (static_cast<unsigned>(std::ceil(u.p.x)+std::ceil(u.p.y)) & 1U)
            return colors::white() * cfact;
        else
            return colors::red() * cfact;
    }

    /*  Function for creating a checker board pattern on the detector.        */
    inline color checker_board_four(const nbh::vec6 &u)
    {
        /*  Factor for darkening the checker board.                           */
        const double cfact = nbh::setup::z_detector_sq/u.p.normsq();

        /*  Integers that determines the color.                               */
        const unsigned int nx = static_cast<unsigned>(std::ceil(u.p.x)) & 1U;
        const unsigned int ny = static_cast<unsigned>(std::ceil(u.p.y)) & 1U;
        const unsigned int n = nx + (ny << 1U);

        /*  If the photon didn't make it, color the pixel black.              */
        if (u.p.z > nbh::setup::z_detector)
            return nbh::colors::black();

        /*  Otherwise use a bit-wise trick to color the plane.                */
        switch (n)
        {
            case 0:
                return colors::white() * cfact;
            case 1:
                return colors::yellow() * cfact;
            case 2:
                return colors::green() * cfact;
            default:
                return colors::red() * cfact;
        }
    }

    /*  Function for creating a checker board pattern on the detector.        */
    inline color checker_board_four_highlight(const nbh::vec6 &u)
    {
        /*  Factor for darkening the checker board.                           */
        const double cfact = nbh::setup::z_detector_sq/u.p.normsq();

        /*  Integers that determines the color.                               */
        const unsigned int nx = static_cast<unsigned>(std::ceil(u.p.x)) & 1U;
        const unsigned int ny = static_cast<unsigned>(std::ceil(u.p.y)) & 1U;
        const unsigned int n = nx + (ny << 1U);

        /*  If the photon didn't make it, color the pixel black.              */
        if (u.p.z > nbh::setup::z_detector)
            return nbh::colors::black();

        /*  If the center of the plane was hit, color blue.               */
        else if (u.p.rhosq() < nbh::setup::highlight_threshold)
            return nbh::colors::blue();

        /*  Otherwise use a bit-wise trick to color the plane.                */
        switch (n)
        {
            case 0:
                return colors::white() * cfact;
            case 1:
                return colors::yellow() * cfact;
            case 2:
                return colors::green() * cfact;
            default:
                return colors::red() * cfact;
        }
    }

    /*  Function for creating a checker board pattern on the detector.        */
    inline color checker_board_highlight(const nbh::vec6 &u)
    {
        const double color_factor = nbh::setup::z_detector_sq / u.p.normsq();
        if (u.p.z > nbh::setup::z_detector)
            return nbh::colors::black();

        /*  If the center of the plane was hit, color blue.               */
        else if (u.p.rhosq() < nbh::setup::highlight_threshold)
            return nbh::colors::blue();

        else if (static_cast<unsigned>(std::ceil(u.p.x)+std::ceil(u.p.y)) & 1U)
            return colors::white() * color_factor;

        else
            return colors::red() * color_factor;
    }

    /*  Function for creating a rainbow-gradient based on the angle the       *
     *  velocity vector makes with the detector.                              */
    inline color angle_gradient(const nbh::vec6 &u)
    {
        /*  Declare unsigned char's for computing the output color.           */
        unsigned char red, green, blue;

        /*  We want the zenith angle of the velocity vector. This can be      *
         *  computed using the cylindrical coordinates of the vector.         */
        const double angle = std::atan2(std::fabs(u.v.z), u.v.rho());

        /*  Scale the angle so that it falls between 0 and 255.               */
        const double scaled = 255.0 * angle / M_PI_2;

        /*  Use an RGB rainbow gradient to color the current pixel. We'll set *
         *  blue to correspond to the least value and red for the greatest,   *
         *  with a continuous gradient in between.                            */
        if (scaled < 64.0)
        {
            red   = 0x00U;
            green = static_cast<unsigned char>(4.0*scaled);
            blue  = 0xFFU;
        }
        else if (scaled < 128.0)
        {
            red   = 0x00U;
            green = 0xFFU;
            blue  = static_cast<unsigned char>(255.0 - 4.0*(scaled - 64.0));
        }
        else if (scaled < 192.0)
        {
            red   = static_cast<unsigned char>(4.0*(scaled - 128.0));
            green = 0xFFU;
            blue  = 0x00U;
        }
        else if (scaled < 255.0)
        {
            red   = 0xFFU;
            green = static_cast<unsigned char>(255.0 - 4.0*(scaled - 192.0));
            blue  = 0x00U;
        }
        else
        {
            red   = 0xFFU;
            green = 0x00U;
            blue  = 0x00U;
        }

        return color(red, green, blue);
    }

    /*  Function for creating a rainbow-gradient based on the angle the       *
     *  velocity vector makes with the detector with a checkerboard pattern.  */
    inline color color_gradient_checkerboard(const nbh::vec6 &u)
    {
        /*  Take the average of the checkerboard and the raindbow gradient.   */
        return bright_checker_board(u) + angle_gradient(u);
    }
}
/*  End of "nbh" namespace.                                                   */

#endif
/*  End of include guard.                                                     */
