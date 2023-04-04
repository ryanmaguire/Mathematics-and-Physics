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

/* Include guard to prevent including this file twice.                        */
#ifndef NBH_PPM_H
#define NBH_PPM_H

/*  File data type found here.                                                */
#include <stdio.h>

/*  NBH_INLINE macro found here.                                              */
#include "nbh_inline.h"

/*  Basic constants for the setup of the experiments given here.              */
#include "nbh_setup.h"

/*  Struct for working with PPM files.                                        */
struct nbh_ppm {

    /*  The "data" of the PPM is just a FILE pointer.                         */
    FILE *fp;
};

/*  Constructor from a name.                                                  */
NBH_INLINE struct nbh_ppm
nbh_ppm_create(const char *name)
{
    /*  Declare a variable for the PPM file.                                  */
    struct nbh_ppm PPM;

    /*  Open the file and give it write permissions.                          */
    PPM.fp = fopen(name, "w");

    /*  Warn the caller is fopen failed.                                      */
    if (!PPM.fp)
        puts("ERROR: fopen failed and returned NULL.");

    return PPM;
}
/*  End of nbh_ppm_create.                                                    */

/*  Print the preamble to the PPM file. A PPM file wants Pn followed by       *
 *  three numbers. P6 means we're encoding an RGB image in binary format.     *
 *  The first two numbers are the number of pixels in the x and y axes.       *
 *  The last number is the size of our color spectrum, which is 255.          */
NBH_INLINE void
nbh_init_ppm_from_vals(struct nbh_ppm *PPM, unsigned x, unsigned y, int type)
{
    switch (type)
    {
        case 1:
            fprintf(PPM->fp, "P1\n%u %u\n255\n", x, y);
            return;
        case 2:
            fprintf(PPM->fp, "P2\n%u %u\n255\n", x, y);
            return;
        case 3:
            fprintf(PPM->fp, "P3\n%u %u\n255\n", x, y);
            return;
        case 4:
            fprintf(PPM->fp, "P4\n%u %u\n255\n", x, y);
            return;
        case 5:
            fprintf(PPM->fp, "P5\n%u %u\n255\n", x, y);
            return;
        default:
            fprintf(PPM->fp, "P6\n%u %u\n255\n", x, y);
    }
}
/*  End of nbh_init_ppm_from_vals.                                            */

/*  Initialize using the values in "setup".                                   */
NBH_INLINE void
nbh_ppm_init(struct nbh_ppm *PPM)
{
    nbh_init_ppm_from_vals(PPM, nbh_setup_xsize, nbh_setup_ysize, 6);
}
/*  End of nbh_ppm_init.                                                      */

/*  Method for closing the file pointer for the PPM.                          */
NBH_INLINE void
nbh_ppm_close(struct nbh_ppm *PPM)
{
    /*  Ensure the pointer is not NULL before trying to close it.             */
    if (!PPM->fp)
        return;

    fclose(PPM->fp);
}
/*  End of nbh_ppm_close.                                                     */

#endif
/*  End of include guard.                                                     */
