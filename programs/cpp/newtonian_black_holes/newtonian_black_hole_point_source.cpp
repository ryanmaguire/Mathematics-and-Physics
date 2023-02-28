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
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/*  Needed for the FILE data type and fprintf function.                       */
#include <cstdio>

/*  All header files for nbh are including here.                              */
#include "nbh.hpp"

/*  Main function for performing the raytracing.                              */
int main(void)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    const nbh::vec3 v = nbh::vec3(0.0, 0.0, -1.0);

    /*  The position vector of a particle of light.                           */
    nbh::vec3 p;

    /*  Variables for looping over the x and y coordinates of the detector.   */
    unsigned int x, y;

    /*  Factor used for printing a progress report.                           */
    const double prog_factor = 100.0 / static_cast<double>(nbh::setup::ysize);

    /*  Variables for the color, and the colors scale factor for darkening.   */
    nbh::color c;
    double color_factor;

    /*  Open the file "black_hole.ppm" and give it write permissions.         */
    nbh::ppm PPM = nbh::ppm("newtonian_black_hole_point_source.ppm");

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (!PPM.fp)
        return -1;

    /*  Otherwise initialize the ppm with default values in "setup".          */
    PPM.init();

    /*  Set the radius to be really small to mimic a point source.            */
    nbh::setup::reset_radius(0.05);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential. If we wanted to *
     *  introduce parallel processing, we would need to store the colors in   *
     *  an array, and then create the PPM from that array. For the simplicity *
     *  of the code, this is not done.                                        */
    for (y = 0U; y < nbh::setup::ysize; ++y)
    {
        for (x = 0U; x < nbh::setup::xsize; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            p = nbh::pixel_to_point(x, y);

            /*  Raytrace where the photon that hit p came from.               */
            p = nbh::euler::path(p, v, nbh::gravity, nbh::stop);

            /*  Scale factor for darkening based on distance to center.       */
            color_factor = 0.5 * (1.0 + nbh::setup::z_detector_sq / p.normsq());

            /*  If the photon never made it to the detector, assume it was    *
             *  captured by the black hole and color the pixel black.         */
            if (p.z > nbh::setup::z_detector)
                c = nbh::colors::black();

            /*  Otherwise, color the detector with a checker board pattern.   */
            else
                c = nbh::checker_board_color(p) * color_factor;

            /*  Write the color to the PPM file.                              */
            c.write(PPM.fp);
        }
        /*  End of x for-loop.                                                */

        /*  Print a status update.                                            */
        if ((y % 20U) == 0U)
            std::fprintf(stderr, "Progress: %.4f%%  \r", prog_factor*y);
    }
    /*  End of y for-loop.                                                    */

    /*  Print a final progress report.                                        */
    std::fprintf(stderr, "Progress: 100.0000%%\nDone\n");

    /*  Close the file and return.                                            */
    PPM.close();
    return 0;
}
/*  End of main.                                                              */
