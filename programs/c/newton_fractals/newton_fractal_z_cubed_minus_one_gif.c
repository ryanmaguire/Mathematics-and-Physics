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
 *      Generates a GIF for the Newton fractal of z^3 - 1.                    *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/09                                                        *
 ******************************************************************************/

/*  Routines for creating fractals here.                                      */
#include "nf.h"

/*  Creates a GIF of the Newton Fractal for z^3 - 1.                          */
int main(void)
{
    /*  Name of the output GIF.                                               */
    const char *name = "newton_fractal_z_cubed_minus_one.gif";

    /*  Coefficients for z^3 - 1.                                             */
    double coeffs[4] = {-1.0, 0.0, 0.0, 1.0};

    /*  The degree can be computed by the length of the array minus 1.        */
    const unsigned int degree = sizeof(coeffs)/sizeof(coeffs[0]) - 1U;

    /*  Create a polynomial from the given coefficients.                      */
    const struct nf_real_poly poly = {coeffs, degree};

    /*  Indices for the x and y axes of the GIF.                              */
    unsigned int x, y;

    /*  The number of frames in the GIF.                                      */
    const unsigned int number_of_frames = 200U;

    /*  Variable for looping over the frames of the GIF.                      */
    unsigned int frame;

    /*  Number of iterations needed in Newton's method.                       */
    unsigned int iters;

    /*  Variable for indexing over the roots.                                 */
    unsigned int ind;

    /*  Factor used for darkening colors based on the number iterations.      */
    double scale;

    /*  Factors for zooming in on the image.                                  */
    const double shrink_factor = 0.99;
    double shrink = 1.0;

    /*  Variable for treating a pixel in the PPM as a complex number.         */
    struct nf_complex z;

    /*  Struct for the roots of the given polynomial.                         */
    struct nf_complex_roots *roots;

    /*  Struct for the colors corresponding to the roots.                     */
    struct nf_color *colors;

    /*  Color for the given pixel.                                            */
    struct nf_color c;

    /*  Number of pixels in each frame.                                       */
    const unsigned int size = nf_setup_xsize * nf_setup_ysize;

    /*  Pointer for keeping track of the pixels of a given frame.             */
    unsigned char *pixel;

    /*  Variable for the GIF.                                                 */
    struct nf_gif_writer writer;

    /*  Array of pixels for the GIF.                                          */
    unsigned char *image = malloc(sizeof(*image) * size * 4U);

    /*  Check if malloc failed.                                               */
    if (!image)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Create the GIF.                                                       */
    nf_gif_begin(&writer, name, nf_setup_xsize, nf_setup_ysize, 2, 8, nf_true);

    /*  Find the roots for the polynomial.                                    */
    roots = nf_real_poly_roots(&poly);

    /*  Check if the root finding function failed.                            */
    if (!roots)
    {
        /*  Close the ppm file, print an error, and return.                   */
        puts("nf_complex_poly_roots returned NULL. Aborting.");
        nf_gif_end(&writer);
        free(image);
        return -1;
    }

    /*  It's possible malloc succeeded but the algorithm failed. Check this.  */
    else if (!roots->roots || roots->number_of_roots == 0U)
    {
        /*  Close the ppm, print an error, and destroy the root struct.       */
        puts("nf_complex_poly_roots failed to find roots. Aborting.");
        nf_complex_roots_destroy(&roots);
        nf_gif_end(&writer);
        free(image);
        return -1;
    }

    /*  Get an array of colors, one for each root.                            */
    colors = nf_complex_roots_get_colors(roots->number_of_roots);

    /*  The previous function calls malloc. Make sure it didn't fail.         */
    if (!colors)
    {
        /*  Close the ppm, print an error, and destroy the root struct.       */
        puts("nf_complex_roots_get_colors returned NULL. Aborting.");
        nf_gif_end(&writer);
        free(image);
        nf_complex_roots_destroy(&roots);
        return -1;
    }

    /*  Loop over the frames of the GIF.                                      */
    for (frame = 0U; frame < number_of_frames; ++frame)
    {
        /*  Loop over the y components of the frame.                          */
        for (y = 0U; y < nf_setup_ysize; ++y)
        {
            /*  Convert the y coordinate of the pixel to the imaginary part.  */
            const double imag = nf_setup_ymax - nf_setup_py_factor*(double)y;

            /*  Loop over the x coordindates.                                 */
            for (x = 0U; x < nf_setup_xsize; ++x)
            {
                /*  Compute the real part of the complex number z.            */
                const double real = nf_setup_xmin+nf_setup_px_factor*(double)x;

                /*  Treat the point (real, imag) as a complex number.         */
                z.real = real*shrink;
                z.imag = imag*shrink;

                /*  Perform Newton's method for poly with guess z0 = z.       */
                iters = nf_newton_real_poly(&poly, &z);

                /*  If Newton's method fails the default color is black.      */
                c = nf_black;

                /*  If Newton's method succeeded z should be close to a root. */
                for (ind = 0U; ind < roots->number_of_roots; ++ind)
                {
                    /*  If this distance is small, Newton's method converged. */
                    if (nf_complex_dist(&z, &roots->roots[ind]) < nf_setup_eps)
                    {
                        /*  Get the color corresponding to this root.         */
                        c = colors[ind];
                        break;
                    }
                }

                /*  Darken the color based on the number of iterations.       */
                scale = (double)(nf_setup_max_iters-iters)*nf_setup_color_scale;
                nf_color_scaleby(&c, scale);

                /*  Color this pixel of the frame in the GIF.                 */
                pixel = &image[(y*nf_setup_ysize + x)*4U];
                pixel[0] = c.red;
                pixel[1] = c.green;
                pixel[2] = c.blue;
                pixel[3] = 0xFF;
            }
        }

        /*  Zoom in a little more for the next frame.                         */
        shrink *= shrink_factor;

        /*  Write the current frame to the GIF and move on to the next one.   */
        printf("Writing frame %d...\n", frame);
        nf_gif_write_frame(&writer, image, nf_setup_xsize,
                           nf_setup_ysize, 2, 8, nf_true);
    }

    /*  Free all memory and close the GIF.                                    */
    nf_complex_roots_destroy(&roots);
    nf_gif_end(&writer);
    free(image);
    free(colors);
    return 0;
}
/*  End of main.                                                              */
