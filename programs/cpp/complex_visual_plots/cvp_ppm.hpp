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
 *      Provides a class for working with PPM files.                          *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/16                                                        *
 ******************************************************************************/

/* Include guard to prevent including this file twice.                        */
#ifndef CVP_PPM_HPP
#define CVP_PPM_HPP

/*  FILE data type found here.                                                */
#include <cstdio>

/*  Basic constants for the setup of the experiments given here.              */
#include "cvp_setup.hpp"

/*  Namespace for the mini-project. "Complex Visual Plots."                   */
namespace cvp {

    /*  Struct for working with PPM files.                                    */
    class ppm {
        public:
            /*  The "data" of the PPM is just a FILE pointer.                 */
            FILE *fp;

            /*  Constructor from a name, the name of the file.                */
            ppm(const char *name);

            /*  Method for initializing the PPM using arbitrary values.       */
            inline void init(unsigned int x, unsigned int y, int type);

            /*  Method for initializing the PPM using the values in "setup".  */
            inline void init(void);

            /*  Method for closing the file pointer for the PPM.              */
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
        /*  For values 1 to 5, print normally.                                */
        if (0 < type && type < 6)
            std::fprintf(fp, "P%d\n%u %u\n255\n", x, y, type);

        /*  The only other legal value is 6. All illegal values default to 6. */
        else
            std::fprintf(fp, "P6\n%u %u\n255\n", x, y);
    }

    /*  Initialize using the values in "setup".                               */
    inline void ppm::init(void)
    {
        init(cvp::setup::xsize, cvp::setup::ysize, 6);
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
/*  End of namespace cvp.                                                     */

#endif
/*  End of include guard.                                                     */
