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
#ifndef NBH_PPM_HPP
#define NBH_PPM_HPP

/*  File data type found here.                                                */
#include <cstdio>

#include "nbh_setup.hpp"

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  Struct for working with PPM files.                                    */
    struct ppm {

        /*  The "data" of the PPM is just a FILE pointer.                     */
        FILE *fp;

        /*  Constructor from a name, the name of the file.                    */
        ppm(const char *name);

        /*  Method for initializing the PPM using arbitrary values.           */
        inline void init(void);

        /*  Method for initializing the PPM using the values in "setup".      */
        inline void init(unsigned int x, unsigned int y, int type);

        /*  Method for closing the file pointer for the PPM.                  */
        inline void close(void);
    };

    /*  Constructor from a name.                                              */
    ppm::ppm(const char *name)
    {
        fp = std::fopen(name, "w");

        /*  Warn the caller is fopen failed.                                  */
        if (!fp)
            std::puts("ERROR: fopen failed and returned NULL.");
    }

    /*  Print the preamble to the PPM file. A PPM file wants Pn followed by   *
     *  three numbers. P6 means we're encoding an RGB image in binary format. *
     *  The first two numbers are the number of pixels in the x and y axes.   *
     *  The last number is the size of our color spectrum, which is 255.      */
    inline void ppm::init(unsigned int x, unsigned int y, int type)
    {
        switch (type)
        {
            case 1:
                std::fprintf(fp, "P1\n%u %u\n255\n", x, y);
                return;
            case 2:
                std::fprintf(fp, "P2\n%u %u\n255\n", x, y);
                return;
            case 3:
                std::fprintf(fp, "P3\n%u %u\n255\n", x, y);
                return;
            case 4:
                std::fprintf(fp, "P4\n%u %u\n255\n", x, y);
                return;
            case 5:
                std::fprintf(fp, "P5\n%u %u\n255\n", x, y);
                return;
            default:
                std::fprintf(fp, "P6\n%u %u\n255\n", x, y);
        }
    }

    /*  Initialize using the values in "setup".                               */
    inline void ppm::init(void)
    {
        init(nbh::setup::xsize, nbh::setup::ysize, 6);
    }

    /*  Method for closing the file pointer for the PPM.                      */
    inline void ppm::close(void)
    {
        /*  Ensure the pointer is not NULL before trying to close it.         */
        if (!fp)
            return;

        std::fclose(fp);
    }
}
/*  End of namespace nbh.                                                     */

#endif
/*  End of include guard.                                                     */
