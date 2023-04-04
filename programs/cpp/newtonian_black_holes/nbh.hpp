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
 *      Header file that includes all other headers for nbh.                  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_HPP
#define NBH_HPP

/*  malloc found here.                                                        */
#include <cstdlib>

/*  Color struct for dealing with RGB colors.                                 */
#include "nbh_color.hpp"

/*  Euler's method for numerically solving ODEs.                              */
#include "nbh_euler.hpp"

/*  PPM struct for creating and writing to PPM files.                         */
#include "nbh_ppm.hpp"

/*  The default parameters of the black hole are found here.                  */
#include "nbh_setup.hpp"

/*  Basic vector struct for points in 3-dimensional space.                    */
#include "nbh_vec3.hpp"

/*  Basic vector struct for points in 6-dimensional space.                    */
#include "nbh_vec6.hpp"

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  Template for running the programs.                                    */
    template <typename Tacc, typename Tstop, typename Tcolor>
    inline void euler_run(Tacc acc, Tstop stop, Tcolor color, const char *name);

    /*  Template for running the programs with parallel processing.           */
    template <typename Tacc, typename Tstop, typename Tcolor>
    inline void
    parallel_euler_run(Tacc acc, Tstop stop, Tcolor color, const char *name);
}
/*  End of "nbh" namespace.                                                   */

/*  Template for running the programs.                                        */
template <typename Tacc, typename Tstop, typename Tcolor>
inline void nbh::euler_run(Tacc acc, Tstop stop, Tcolor color, const char *name)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    const nbh::vec3 v_start = nbh::vec3(0.0, 0.0, -1.0);

    /*  The initial conditions of a particle of light.                        */
    nbh::vec6 u;

    /*  Variables for looping over the x and y coordinates of the detector.   */
    unsigned int x, y;

    /*  Factor used for printing a progress report.                           */
    const double prog_factor = 100.0 / static_cast<double>(nbh::setup::ysize);

    /*  Variable for the color.                                               */
    nbh::color c;

    /*  Open the file and give it write permissions.                          */
    nbh::ppm PPM = nbh::ppm(name);

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (!PPM.fp)
        return;

    /*  Otherwise initialize the ppm with default values in "setup".          */
    PPM.init();

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
            u.p = nbh::pixel_to_point(x, y);

            /*  Set the starting velocity.                                    */
            u.v = v_start;

            /*  Raytrace where the photon that hit p came from.               */
            nbh::euler::path(u, acc, stop);

            /*  Get the color for the current pixel.                          */
            c = color(u);

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
    return;
}
/*  End of nbh::euler_run.                                                    */

/*  Template for running the programs with parallel processing.               */
template <typename Tacc, typename Tstop, typename Tcolor>
inline void
nbh::parallel_euler_run(Tacc acc, Tstop stop, Tcolor color, const char *name)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    const nbh::vec3 v_start = nbh::vec3(0.0, 0.0, -1.0);

    /*  Total number of pixels.                                               */
    const unsigned int size = nbh::setup::xsize * nbh::setup::ysize;

    /*  Variable for looping over the image.                                  */
    unsigned int n;

    /*  Variable for the color.                                               */
    nbh::color * const c =
        static_cast<nbh::color *>(std::malloc(sizeof(*c)*size));

    /*  Open the file and give it write permissions.                          */
    nbh::ppm PPM = nbh::ppm(name);

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (!PPM.fp)
    {
        /*  If malloc also failed, we can just return. Nothing to free.       */
        if (!c)
            return;

        /*  Otherwise free the color pointer and abort.                       */
        std::free(c);
        return;
    }

    /*  If malloc failed for the color pointer abort the computation.         */
    else if (!c)
    {
        /*  Close the PPM file before exiting.                                */
        PPM.close();
        return;
    }

    /*  Otherwise initialize the ppm with default values in "setup".          */
    PPM.init();

    /*  We have malloc'd an array for the colors so we can parallelize this.  */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
    {
        /*  Variables for looping over the x and y coordinates.               */
        const unsigned int x = n % nbh::setup::xsize;
        const unsigned int y = n / nbh::setup::ysize;

        /*  The initial conditions of a particle of light.                    */
        nbh::vec6 u = nbh::vec6(nbh::pixel_to_point(x, y), v_start);

        /*  Raytrace where the photon that hit p came from.                   */
        nbh::euler::path(u, acc, stop);

        /*  Get the color for the current pixel.                              */
        c[n] = color(u);
    }

    /*  Loop over the PPM file and write the colors in order.                 */
    for (n = 0U; n < size; ++n)
        c[n].write(PPM.fp);

    /*  Close the file, free the data, and return.                            */
    PPM.close();
    std::free(c);
    return;
}
/*  End of nbh::parallel_euler_run.                                           */

#endif
/*  End of include guard.                                                     */
