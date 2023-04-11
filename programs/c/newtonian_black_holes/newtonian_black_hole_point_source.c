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
 *      Basic test of the nbh routines. Generates a single black hole.        *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/09                                                        *
 ******************************************************************************/

/*  All header files for nbh are including here.                              */
#include "nbh.h"

/*  Main function for performing the raytracing.                              */
int main(void)
{
    /*  Name of the output ppm file.                                          */
    const char *name = "newtonian_black_hole_point_source.ppm";

    /*  Reset the number of maximum iterations to something much higher.      */
    nbh_euler_reset_max_iters(1000000U);

    /*  Reset the radius of the black hole to be a point.                     */
    nbh_setup_reset_radius(0.01);

    /*  Use the template function to render the image.                        */
#ifdef _OPENMP
    nbh_prun(nbh_gravity, nbh_stop, nbh_bright_checker_board,
             nbh_euler_path, name);
#else
    nbh_run(nbh_gravity, nbh_stop, nbh_bright_checker_board,
            nbh_euler_path, name);
#endif
    return 0;
}
/*  End of main.                                                              */