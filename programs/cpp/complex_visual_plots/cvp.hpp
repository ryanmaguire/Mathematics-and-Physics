#ifndef CVP_HPP
#define CVP_HPP

#include <cstdlib>
#include "cvp_complex.hpp"
#include "cvp_color.hpp"
#include "cvp_ppm.hpp"
#include "cvp_setup.hpp"
#include "cvp_colorers.hpp"

namespace cvp {
    /*  Template for creating complex plots.                                  */
    template <typename Tfunc, typename Tcolor>
    inline void
    complex_plot(Tfunc cfunc, Tcolor color, const char *name);

    /*  Template for creating complex plots with parallelization.             */
    template <typename Tfunc, typename Tcolor>
    inline void
    pcomplex_plot(Tfunc cfunc, Tcolor color, const char *name);
}

/******************************************************************************
 *  Function:                                                                 *
 *      cvp::complex_plot                                                     *
 *  Purpose:                                                                  *
 *      Creates a plot from a complex function based on argument and modulus. *
 *  Arguments:                                                                *
 *      cfunc (Tfunc):                                                        *
 *          A complex-valued function of a complex variable.                  *
 *      color (Tcolor):                                                       *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
template <typename Tfunc, typename Tcolor>
inline void cvp::complex_plot(Tfunc cfunc, Tcolor color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    unsigned int x, y;

    /*  Variables for the real and imaginary parts of a given complex number. */
    double z_re, z_im;

    /*  Variable for the complex number z_re + i*z_im.                        */
    cvp::complex z;

    /*  Color for the pixel corresponding to z.                               */
    cvp::color c;

    /*  Variable for the ppm file.                                            */
    cvp::ppm PPM = cvp::ppm(name);

    /*  Check if the constructor failed.                                      */
    if (!PPM.fp)
        return;

    /*  Initialize the ppm file to the default values.                        */
    PPM.init();

    /*  Loop over the y coordinates of the ppm file.                          */
    for (y = 0U; y < cvp::setup::ysize; y++)
    {
        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = cvp::setup::ymax - cvp::setup::pyfactor*y;

        /*  Loop over the x coordinates of the ppm file.                      */
        for (x = 0U; x < cvp::setup::xsize; x++)
        {
            /*  Compute the corresponding x coordinate.                       */
            z_re = cvp::setup::xmin + cvp::setup::pxfactor*x;

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z = cvp::complex(z_re, z_im);

            /*  Get the color corresponding to this pixel.                    */
            c = color(cfunc(z));

            /*  Write the color to the ppm file.                              */
            c.write(PPM);
        }
    }

    /*  Close the ppm file.                                                   */
    PPM.close();
}
/*  End of cvp::complex_plot.                                                 */

template <typename Tfunc, typename Tcolor>
inline void cvp::pcomplex_plot(Tfunc cfunc, Tcolor color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    const unsigned int size = cvp::setup::xsize * cvp::setup::ysize;
    unsigned int n;

    /*  Color for the pixel corresponding to z.                               */
    cvp::color *c = static_cast<cvp::color *>(std::malloc(sizeof(*c)*size));

    /*  Variable for the ppm file.                                            */
    cvp::ppm PPM = cvp::ppm(name);

    /*  Check if the constructor failed.                                      */
    if (!PPM.fp)
    {
        if (!c)
            return;

        std::free(c);
        return;
    }

    if (!c)
    {
        PPM.close();
        return;
    }

    /*  Initialize the ppm file to the default values.                        */
    PPM.init();

    /*  Loop over the y coordinates of the ppm file.                          */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
    {
        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        const unsigned int x = n % cvp::setup::xsize;
        const unsigned int y = n / cvp::setup::ysize;
        const double z_im = cvp::setup::ymax - cvp::setup::pyfactor*y;
        const double z_re = cvp::setup::xmin + cvp::setup::pxfactor*x;
        cvp::complex z = cvp::complex(z_re, z_im);
        c[n] = color(cfunc(z));
    }

    for (n = 0U; n < size; ++n)
        c[n].write(PPM);

    /*  Close the ppm file.                                                   */
    PPM.close();
}
/*  End of cvp::complex_plot.                                                 */

#endif
