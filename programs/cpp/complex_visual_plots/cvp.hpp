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
 *      Provides routines for plotting complex functions.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/18                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_HPP
#define CVP_HPP

/*  malloc and free are given here.                                           */
#include <cstdlib>

/*  Complex class provided here.                                              */
#include "cvp_complex.hpp"

/*  Class for working with colors in RGB format.                              */
#include "cvp_color.hpp"

/*  Class for creating and writing to PPM files.                              */
#include "cvp_ppm.hpp"

/*  Basic setup parameters for plotting functions provided here.              */
#include "cvp_setup.hpp"

/*  Functions for converting complex numbers into colors given here.          */
#include "cvp_colorers.hpp"

/*  Namespace for this mini-project. "Complex Visual Plots."                  */
namespace cvp {

    /*  Template for creating complex plots.                                  */
    template <typename Tfunc, typename Tcolor>
    inline void
    complex_plot(Tfunc cfunc, Tcolor color, const char *name);

    /*  Template for plotting iterative calls to complex functions.           */
    template <typename Tfunc, typename Tcolor>
    inline void
    iters_plot(Tfunc cfunc, unsigned int iters, Tcolor color, const char *name);

    /*  Template for plotting Mandelbrot iterations of functions.             */
    template <typename Tfunc, typename Tcolor>
    inline void
    mandelbrot_plot(Tfunc cfunc, unsigned int iters,
                    Tcolor color, const char *name);

    /*  Template for creating complex plots with parallelization.             */
    template <typename Tfunc, typename Tcolor>
    inline void
    pcomplex_plot(Tfunc cfunc, Tcolor color, const char *name);
}
/*  End of namespace "cvp".                                                   */

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
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the ppm file.                                                   */
    PPM.close();
}
/*  End of cvp::complex_plot.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp::iters_plot                                                       *
 *  Purpose:                                                                  *
 *      Creates a plot from repeated evaluation of a complex function.        *
 *  Arguments:                                                                *
 *      cfunc (Tfunc):                                                        *
 *          A complex-valued function of a complex variable.                  *
 *      iters (unsigned int):                                                 *
 *          The number of times to call the function.                         *
 *      color (Tcolor):                                                       *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
template <typename Tfunc, typename Tcolor>
inline void
cvp::iters_plot(Tfunc cfunc, unsigned int iters, Tcolor color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    unsigned int x, y;

    /*  Variable for keeping tracks of the number of iterations performed.    */
    unsigned int ind;

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

            /*  Repeatedly call the function.                                 */
            for (ind = 0U; ind < iters; ++ind)
                z = cfunc(z);

            /*  Get the color corresponding to this pixel.                    */
            c = color(z);

            /*  Write the color to the ppm file.                              */
            c.write(PPM);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the ppm file.                                                   */
    PPM.close();
}
/*  End of cvp::iters_plot.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp::mandelbrot_plot                                                  *
 *  Purpose:                                                                  *
 *      Creates a plot of the Mandelbrot iterations of functions.             *
 *  Arguments:                                                                *
 *      cfunc (Tfunc):                                                        *
 *          A complex-valued function of a complex variable.                  *
 *      iters (unsigned int):                                                 *
 *          The number of times to call the function.                         *
 *      color (Tcolor):                                                       *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
template <typename Tfunc, typename Tcolor>
inline void
cvp::mandelbrot_plot(Tfunc cfunc, unsigned int iters,
                     Tcolor color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    unsigned int x, y;

    /*  Variable for keeping tracks of the number of iterations performed.    */
    unsigned int ind;

    /*  Variables for the real and imaginary parts of a given complex number. */
    double z_re, z_im;

    /*  Variable for the complex number z_re + i*z_im.                        */
    cvp::complex z;

    /*  Variable for computing the Mandelbrot iterations.                     */
    cvp::complex w;

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

            /*  Set the first iteration to the input.                         */
            w = z;

            /*  Repeatedly call the function.                                 */
            for (ind = 0U; ind < iters; ++ind)
                w = cfunc(w) + z;

            /*  Get the color corresponding to this pixel.                    */
            c = color(w);

            /*  Write the color to the ppm file.                              */
            c.write(PPM);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the ppm file.                                                   */
    PPM.close();
}
/*  End of cvp::mandelbrot_plot.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp::pcomplex_plot                                                    *
 *  Purpose:                                                                  *
 *      Creates a plot of a complex function using parallel computing.        *
 *  Arguments:                                                                *
 *      cfunc (Tfunc):                                                        *
 *          A complex-valued function of a complex variable.                  *
 *      color (Tcolor):                                                       *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Notes:                                                                    *
 *      Unless you're rendering at a very high resolution image, this         *
 *      function is actually slower than the default.                         *
 ******************************************************************************/
template <typename Tfunc, typename Tcolor>
inline void cvp::pcomplex_plot(Tfunc cfunc, Tcolor color, const char *name)
{
    /*  Total number of pixels in the PPM file.                               */
    const unsigned int size = cvp::setup::xsize * cvp::setup::ysize;

    /*  Index for looping over the pixels of the file.                        */
    unsigned int n;

    /*  Color array for the color of each pixel in the PPM.                   */
    cvp::color *c = static_cast<cvp::color *>(std::malloc(sizeof(*c)*size));

    /*  Variable for the ppm file.                                            */
    cvp::ppm PPM = cvp::ppm(name);

    /*  Check if the constructor failed.                                      */
    if (!PPM.fp)
    {
        /*  If malloc failed there is nothing to free. Return to caller.      */
        if (!c)
            return;

        /*  Otherwise free the data before returning.                         */
        std::free(c);
        return;
    }

    /*  Similarly check if malloc failed.                                     */
    if (!c)
    {
        /*  If it did close the PPM file and return.                          */
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
/*  End of cvp::pcomplex_plot.                                                */

#endif
