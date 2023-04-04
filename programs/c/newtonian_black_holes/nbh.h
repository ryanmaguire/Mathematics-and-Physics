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

/*  Basic vector struct for points in 3-dimensional space.                    */
#include "nbh_vec3.h"

/*  Basic vector struct for points in 6-dimensional space.                    */
#include "nbh_vec6.h"

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
/*  End of nbh::euler_run.                                                    */

#endif
