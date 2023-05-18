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
 *      Provides a struct for working with PPM files.                         *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/17                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef MSD_PPM_H
#define MSD_PPM_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  MSD_INLINE macro found here.                                              */
#include "msd_inline.h"

/*  Basic constants for the setup of the plots given here.                    */
#include "msd_setup.h"

/*  Struct for working with PPM files.                                        */
struct msd_ppm {

    /*  The "data" of the PPM is just a FILE pointer.                         */
    FILE *fp;
};

/******************************************************************************
 *  Function:                                                                 *
 *      msd_ppm_create                                                        *
 *  Purpose:                                                                  *
 *      Creates a PPM file with a given file name.                            *
 *  Arguments:                                                                *
 *      name (const char *):                                                  *
 *          The file name of the output PPM (ex. "newton_fractal.ppm").       *
 *  Outputs:                                                                  *
 *      PPM (struct msd_ppm):                                                 *
 *          A PPM struct whose FILE pointer points to a ppm file that has     *
 *          been given write permissions.                                     *
 *  Notes:                                                                    *
 *      fopen returns NULL on failure. This function will print a warning if  *
 *      fopen fails. It is the callers responsibility to inspect the FILE     *
 *      pointer before trying to use it.                                      *
 ******************************************************************************/
MSD_INLINE struct msd_ppm
msd_ppm_create(const char *name)
{
    /*  Declare a variable for the PPM file.                                  */
    struct msd_ppm PPM;

    /*  Open the file and give it write permissions.                          */
    PPM.fp = fopen(name, "w");

    /*  Warn the caller if fopen failed.                                      */
    if (!PPM.fp)
        puts("ERROR: fopen failed and returned NULL.");

    return PPM;
}
/*  End of msd_ppm_create.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_ppm_init_from_vals                                                *
 *  Purpose:                                                                  *
 *      Print the preamble to the PPM file. A PPM file wants Pn followed by   *
 *      three numbers. P6 means we're encoding an RGB image in binary format. *
 *      The first two numbers are the number of pixels in the x and y axes.   *
 *      The last number is the size of our color spectrum, which is 255.      *
 *  Arguments:                                                                *
 *      PPM (struct msd_ppm *):                                               *
 *          A pointer to a PPM struct. This pointers FILE pointer will be     *
 *          edited with the preamble for the PPM.                             *
 *      x (unsigned int):                                                     *
 *          The number of pixels in the x axis.                               *
 *      y (unsigned int):                                                     *
 *          The number of pixels in the y axis.                               *
 *      type (int):                                                           *
 *          The type of the PPM, options are 1 through 6.                     *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
MSD_INLINE void
msd_ppm_init_from_vals(struct msd_ppm *PPM, unsigned x, unsigned y, int type)
{
    /*  For integers between 1 and 5 we can pass the value to the preamble.   */
    if (0 < type && type < 5)
        fprintf(PPM->fp, "P%d\n%u %u\n255\n", type, x, y);

    /*  The only other legal value is 6. All illegal values default to 6.     */
    else
        fprintf(PPM->fp, "P6\n%u %u\n255\n", x, y);
}
/*  End of msd_ppm_init_from_vals.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_ppm_init                                                          *
 *  Purpose:                                                                  *
 *      Initialize a PPM using the values in "setup".                         *
 *  Arguments:                                                                *
 *      PPM (struct msd_ppm *):                                               *
 *          A pointer to the PPM that is to be initialized.                   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Pass the default parameters in msd_setup.h to msd_ppm_init_from_vals. *
 ******************************************************************************/
MSD_INLINE void
msd_ppm_init(struct msd_ppm *PPM)
{
    msd_ppm_init_from_vals(PPM, msd_setup_xsize, msd_setup_ysize, 6);
}
/*  End of msd_ppm_init.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      msd_ppm_close                                                         *
 *  Purpose:                                                                  *
 *      Closes the file pointer in a PPM struct.                              *
 *  Arguments:                                                                *
 *      PPM (struct msd_ppm *):                                               *
 *          A pointer to the PPM struct that is to be closed.                 *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
MSD_INLINE void
msd_ppm_close(struct msd_ppm *PPM)
{
    /*  Ensure the pointer is not NULL before trying to close it.             */
    if (!PPM->fp)
        return;

    fclose(PPM->fp);
}
/*  End of msd_ppm_close.                                                     */

#endif
/*  End of include guard.                                                     */
