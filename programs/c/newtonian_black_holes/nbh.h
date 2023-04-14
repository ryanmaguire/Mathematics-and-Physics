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
 *      Provides raytracing routines to render black holes.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/03                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_H
#define NBH_H

/*  malloc found here.                                                        */
#include <stdlib.h>

/*  Color struct for dealing with RGB colors.                                 */
#include "nbh_color.h"

/*  Euler's method for numerically solving ODEs.                              */
#include "nbh_euler.h"

/*  Function types for acceleration, stoppers, and raytracers here.           */
#include "nbh_function_types.h"

/*  PPM struct for creating and writing to PPM files.                         */
#include "nbh_ppm.h"

/*  The default parameters of the black hole are found here.                  */
#include "nbh_setup.h"

/*  Runge-Kutta solvers found here.                                           */
#include "nbh_rk.h"

/*  Basic vector struct for points in 3-dimensional space.                    */
#include "nbh_vec3.h"

/*  Basic vector struct for points in 6-dimensional space.                    */
#include "nbh_vec6.h"

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_run                                                               *
 *  Purpose:                                                                  *
 *      Runs the raytracing routines without parallelizing the computation.   *
 *  Arguments:                                                                *
 *      acc (acceleration):                                                   *
 *          Function describing the equation of motion.                       *
 *      stop (stopper):                                                       *
 *          Stopper function for determining when the photon stops moving.    *
 *      color (colorer):                                                      *
 *          Color function for coloring the detector.                         *
 *      path (raytracer):                                                     *
 *          The method of numerical raytracing. Options are Euler's method    *
 *          and fourth order Runge-Kutta.                                     *
 *      name (const char *):                                                  *
 *          The name of the output ppm file.                                  *
 ******************************************************************************/
NBH_INLINE void
nbh_run(acceleration acc, stopper stop, colorer color,
        raytracer path, const char *name)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    const struct nbh_vec3 v_start = nbh_vec3_rect(0.0, 0.0, -1.0);

    /*  The initial conditions of a particle of light.                        */
    struct nbh_vec6 u;

    /*  Variables for looping over the x and y coordinates of the detector.   */
    unsigned int x, y;

    /*  Factor used for printing a progress report.                           */
    const double prog_factor = 100.0 / (double)nbh_setup_ysize;

    /*  Variable for the color.                                               */
    struct nbh_color c;

    /*  Open the file and give it write permissions.                          */
    struct nbh_ppm PPM = nbh_ppm_create(name);

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (!PPM.fp)
        return;

    /*  Otherwise initialize the ppm with default values in "setup".          */
    nbh_ppm_init(&PPM);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential. If we wanted to *
     *  introduce parallel processing, we would need to store the colors in   *
     *  an array, and then create the PPM from that array. For the simplicity *
     *  of the code, this is not done.                                        */
    for (y = 0U; y < nbh_setup_ysize; ++y)
    {
        for (x = 0U; x < nbh_setup_xsize; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            u.p = nbh_pixel_to_point(x, y);

            /*  Set the starting velocity.                                    */
            u.v = v_start;

            /*  Raytrace where the photon that hit p came from.               */
            path(&u, acc, stop);

            /*  Get the color for the current pixel.                          */
            c = color(&u);

            /*  Write the color to the PPM file.                              */
            nbh_color_write_to_ppm(&c, &PPM);
        }
        /*  End of x for-loop.                                                */

        /*  Print a status update.                                            */
        if ((y % 20U) == 0U)
            fprintf(stderr, "Progress: %.4f%%  \r", prog_factor*y);
    }
    /*  End of y for-loop.                                                    */

    /*  Print a final progress report.                                        */
    fprintf(stderr, "Progress: 100.0000%%\nDone\n");

    /*  Close the file and return.                                            */
    nbh_ppm_close(&PPM);
    return;
}
/*  End of nbh_run.                                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_prun                                                              *
 *  Purpose:                                                                  *
 *      Runs the raytracing routines with parallelization.                    *
 *  Arguments:                                                                *
 *      acc (acceleration):                                                   *
 *          Function describing the equation of motion.                       *
 *      stop (stopper):                                                       *
 *          Stopper function for determining when the photon stops moving.    *
 *      color (colorer):                                                      *
 *          Color function for coloring the detector.                         *
 *      path (raytracer):                                                     *
 *          The method of numerical raytracing. Options are Euler's method    *
 *          and fourth order Runge-Kutta.                                     *
 *      name (const char *):                                                  *
 *          The name of the output ppm file.                                  *
 ******************************************************************************/
NBH_INLINE void
nbh_prun(acceleration acc, stopper stop, colorer color,
         raytracer path, const char *name)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    const struct nbh_vec3 v_start = nbh_vec3_rect(0.0, 0.0, -1.0);

    /*  Total number of pixels.                                               */
    const unsigned int size = nbh_setup_xsize * nbh_setup_ysize;

    /*  Variable for looping over the image.                                  */
    unsigned int n;

    /*  Variable for the color.                                               */
    struct nbh_color * const c = malloc(sizeof(*c)*size);

    /*  Open the file and give it write permissions.                          */
    struct nbh_ppm PPM = nbh_ppm_create(name);

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (!PPM.fp)
    {
        /*  If malloc also failed, we can just return. Nothing to free.       */
        if (!c)
            return;

        /*  Otherwise free the color pointer and abort.                       */
        free(c);
        return;
    }

    /*  If malloc failed for the color pointer abort the computation.         */
    else if (!c)
    {
        /*  Close the PPM file before exiting.                                */
        nbh_ppm_close(&PPM);
        return;
    }

    /*  Otherwise initialize the ppm with default values in "setup".          */
    nbh_ppm_init(&PPM);

    /*  We have malloc'd an array for the colors so we can parallelize this.  */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
    {
        /*  Variables for looping over the x and y coordinates.               */
        const unsigned int x = n % nbh_setup_xsize;
        const unsigned int y = n / nbh_setup_ysize;

        /*  The initial conditions of a particle of light.                    */
        const struct nbh_vec3 p = nbh_pixel_to_point(x, y);
        struct nbh_vec6 u = nbh_vec6_from_vectors(&p, &v_start);

        /*  Raytrace where the photon that hit p came from.                   */
        path(&u, acc, stop);

        /*  Get the color for the current pixel.                              */
        c[n] = color(&u);
    }

    /*  Loop over the PPM file and write the colors in order.                 */
    for (n = 0U; n < size; ++n)
        nbh_color_write_to_ppm(&c[n], &PPM);

    /*  Close the file, free the data, and return.                            */
    nbh_ppm_close(&PPM);
    free(c);
    return;
}
/*  End of nbh_prun.                                                          */

#endif
/*  End of include guard.                                                     */
