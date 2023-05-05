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
 *      Provides routines for generating Newton fractals.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/13                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_H
#define NF_H

/*  NF_INLINE macro given here.                                               */
#include "nf_inline.h"

/*  Struct for working with colors in RGB format.                             */
#include "nf_color.h"

/*  Functions for creating colors from angles on the color wheel.             */
#include "nf_colorers.h"

/*  Struct for working with complex numbers.                                  */
#include "nf_complex.h"

/*  Struct for dealing with polynomials with complex coefficients.            */
#include "nf_complex_poly.h"

/*  Struct for storing the complex roots of a real or complex polynomial.     */
#include "nf_complex_roots.h"

/*  Functions and structs for creating GIF files and writing to them.         */
#include "nf_gif.h"

/*  Routines for performing the Newton-Raphson method on functions.           */
#include "nf_newton.h"

/*  Struct for creating and writing to PPM files.                             */
#include "nf_ppm.h"

/*  Struct for working with polynomials with real coefficients.               */
#include "nf_real_poly.h"

/*  Basic setup parameters for the fractals provided here.                    */
#include "nf_setup.h"

/*  Macro for creating Newton fractals from complex polynomials.              */
#define NF_COMPLEX_NEWTON_FRACTAL(coeffs, name)                                \
                                                                               \
    /*  The degree can be computed by the length of the array minus 1.       */\
    const unsigned int degree = sizeof(coeffs)/sizeof(coeffs[0]) - 1U;         \
                                                                               \
    /*  Create a polynomial from the given coefficients.                     */\
    const struct nf_complex_poly poly = {coeffs, degree};                      \
                                                                               \
    /*  Indices for the x and y axes of the PPM file.                        */\
    unsigned int x, y;                                                         \
                                                                               \
    /*  Number of iterations needed in Newton's method.                      */\
    unsigned int iters;                                                        \
                                                                               \
    /*  Variable for indexing over the roots.                                */\
    unsigned int ind;                                                          \
                                                                               \
    /*  Factor used for darkening colors based on the number iterations.     */\
    double scale;                                                              \
                                                                               \
    /*  Variable for treating a pixel in the PPM as a complex number.        */\
    struct nf_complex z;                                                       \
                                                                               \
    /*  Struct for the roots of the given polynomial.                        */\
    struct nf_complex_roots *roots;                                            \
                                                                               \
    /*  Struct for the colors corresponding to the roots.                    */\
    struct nf_color *colors;                                                   \
                                                                               \
    /*  Color for the given pixel.                                           */\
    struct nf_color c;                                                         \
                                                                               \
    /*  Create a PPM file with the given name.                               */\
    struct nf_ppm ppm = nf_ppm_create(name);                                   \
                                                                               \
    /*  Initialize the PPM using the default values.                         */\
    nf_ppm_init(&ppm);                                                         \
                                                                               \
    /*  Check if the init function failed.                                   */\
    if (!ppm.fp)                                                               \
    {                                                                          \
        puts("nf_ppm_init failed and return NULL for FILE pointer. Abort.");   \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Find the roots for the polynomial.                                   */\
    roots = nf_complex_poly_roots(&poly);                                      \
                                                                               \
    /*  Check if the root finding function failed.                           */\
    if (!roots)                                                                \
    {                                                                          \
        /*  Close the ppm file, print an error, and return.                  */\
        puts("nf_complex_poly_roots returned NULL. Aborting.");                \
        nf_ppm_close(&ppm);                                                    \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  It's possible malloc succeeded but the algorithm failed. Check this. */\
    else if (!roots->roots || roots->number_of_roots == 0U)                    \
    {                                                                          \
        /*  Close the ppm, print an error, and destroy the root struct.      */\
        puts("nf_complex_poly_roots failed to find roots. Aborting.");         \
        nf_complex_roots_destroy(&roots);                                      \
        nf_ppm_close(&ppm);                                                    \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Get an array of colors, one for each root.                           */\
    colors = nf_complex_roots_get_colors(roots->number_of_roots);              \
                                                                               \
    /*  The previous function calls malloc. Make sure it didn't fail.        */\
    if (!colors)                                                               \
    {                                                                          \
        /*  Close the ppm, print an error, and destroy the root struct.      */\
        puts("nf_complex_roots_get_colors returned NULL. Aborting.");          \
        nf_ppm_close(&ppm);                                                    \
        nf_complex_roots_destroy(&roots);                                      \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Loop over the y components of the PPM file.                          */\
    for (y = 0U; y < nf_setup_ysize; ++y)                                      \
    {                                                                          \
        /*  Convert the y coordinate of the pixel to the imaginary part of z.*/\
        const double imag = nf_setup_ymax - nf_setup_py_factor*(double)y;      \
                                                                               \
        /*  Loop over the x coordindates.                                    */\
        for (x = 0U; x < nf_setup_xsize; ++x)                                  \
        {                                                                      \
            /*  Compute the real part of the complex number z from the pixel.*/\
            const double real = nf_setup_xmin + nf_setup_px_factor*(double)x;  \
                                                                               \
            /*  Treat the point (real, imag) as a complex number.            */\
            z.real = real;                                                     \
            z.imag = imag;                                                     \
                                                                               \
            /*  Perform Newton's method for poly with guess z0 = z.          */\
            iters = nf_newton_complex_poly(&poly, &z);                         \
                                                                               \
            /*  If Newton's method fails the default color is black.         */\
            c = nf_black;                                                      \
                                                                               \
            /*  If Newton's method succeeded z should now be close to a root.*/\
            for (ind = 0U; ind < roots->number_of_roots; ++ind)                \
            {                                                                  \
                /*  If this distance is small, Newton's method converged.    */\
                if (nf_complex_dist(&z, &roots->roots[ind]) < nf_setup_eps)    \
                {                                                              \
                    /*  Get the color corresponding to this root.            */\
                    c = colors[ind];                                           \
                    break;                                                     \
                }                                                              \
            }                                                                  \
                                                                               \
            /*  Darken the color based on the number of iterations required. */\
            scale = (double)(nf_setup_max_iters - iters)*nf_setup_color_scale; \
            nf_color_scaleby(&c, scale);                                       \
                                                                               \
            /*  Lastly, write this color to the ppm file.                    */\
            nf_color_write_to_ppm(&c, &ppm);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*  Close the PPM, destroy the root struct, and free the color array.    */\
    nf_ppm_close(&ppm);                                                        \
    nf_complex_roots_destroy(&roots);                                          \
                                                                               \
    /*  This line does not get a semi-colon since this is a macro. The user  */\
    /*  will add a semi-colon at the end of the call to this macro.          */\
    free(colors)                                                               \

/*  Macro for creating Newton fractals from real polynomials.                 */
#define NF_REAL_NEWTON_FRACTAL(coeffs, name)                                   \
                                                                               \
    /*  The degree can be computed by the length of the array minus 1.       */\
    const unsigned int degree = sizeof(coeffs)/sizeof(coeffs[0]) - 1U;         \
                                                                               \
    /*  Create a polynomial from the given coefficients.                     */\
    const struct nf_real_poly poly = {coeffs, degree};                         \
                                                                               \
    /*  Indices for the x and y axes of the PPM file.                        */\
    unsigned int x, y;                                                         \
                                                                               \
    /*  Number of iterations needed in Newton's method.                      */\
    unsigned int iters;                                                        \
                                                                               \
    /*  Variable for indexing over the roots.                                */\
    unsigned int ind;                                                          \
                                                                               \
    /*  Factor used for darkening colors based on the number iterations.     */\
    double scale;                                                              \
                                                                               \
    /*  Variable for treating a pixel in the PPM as a complex number.        */\
    struct nf_complex z;                                                       \
                                                                               \
    /*  Struct for the roots of the given polynomial.                        */\
    struct nf_complex_roots *roots;                                            \
                                                                               \
    /*  Struct for the colors corresponding to the roots.                    */\
    struct nf_color *colors;                                                   \
                                                                               \
    /*  Color for the given pixel.                                           */\
    struct nf_color c;                                                         \
                                                                               \
    /*  Create a PPM file with the given name.                               */\
    struct nf_ppm ppm = nf_ppm_create(name);                                   \
                                                                               \
    /*  Initialize the PPM using the default values.                         */\
    nf_ppm_init(&ppm);                                                         \
                                                                               \
    /*  Check if the init function failed.                                   */\
    if (!ppm.fp)                                                               \
    {                                                                          \
        puts("nf_ppm_init failed and return NULL for FILE pointer. Abort.");   \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Find the roots for the polynomial.                                   */\
    roots = nf_real_poly_roots(&poly);                                         \
                                                                               \
    /*  Check if the root finding function failed.                           */\
    if (!roots)                                                                \
    {                                                                          \
        /*  Close the ppm file, print an error, and return.                  */\
        puts("nf_complex_poly_roots returned NULL. Aborting.");                \
        nf_ppm_close(&ppm);                                                    \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  It's possible malloc succeeded but the algorithm failed. Check this. */\
    else if (!roots->roots || roots->number_of_roots == 0U)                    \
    {                                                                          \
        /*  Close the ppm, print an error, and destroy the root struct.      */\
        puts("nf_complex_poly_roots failed to find roots. Aborting.");         \
        nf_complex_roots_destroy(&roots);                                      \
        nf_ppm_close(&ppm);                                                    \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Get an array of colors, one for each root.                           */\
    colors = nf_complex_roots_get_colors(roots->number_of_roots);              \
                                                                               \
    /*  The previous function calls malloc. Make sure it didn't fail.        */\
    if (!colors)                                                               \
    {                                                                          \
        /*  Close the ppm, print an error, and destroy the root struct.      */\
        puts("nf_complex_roots_get_colors returned NULL. Aborting.");          \
        nf_ppm_close(&ppm);                                                    \
        nf_complex_roots_destroy(&roots);                                      \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    /*  Loop over the y components of the PPM file.                          */\
    for (y = 0U; y < nf_setup_ysize; ++y)                                      \
    {                                                                          \
        /*  Convert the y coordinate of the pixel to the imaginary part of z.*/\
        const double imag = nf_setup_ymax - nf_setup_py_factor*(double)y;      \
                                                                               \
        /*  Loop over the x coordindates.                                    */\
        for (x = 0U; x < nf_setup_xsize; ++x)                                  \
        {                                                                      \
            /*  Compute the real part of the complex number z from the pixel.*/\
            const double real = nf_setup_xmin + nf_setup_px_factor*(double)x;  \
                                                                               \
            /*  Treat the point (real, imag) as a complex number.            */\
            z.real = real;                                                     \
            z.imag = imag;                                                     \
                                                                               \
            /*  Perform Newton's method for poly with guess z0 = z.          */\
            iters = nf_newton_real_poly(&poly, &z);                            \
                                                                               \
            /*  If Newton's method fails the default color is black.         */\
            c = nf_black;                                                      \
                                                                               \
            /*  If Newton's method succeeded z should now be close to a root.*/\
            for (ind = 0U; ind < roots->number_of_roots; ++ind)                \
            {                                                                  \
                /*  If this distance is small, Newton's method converged.    */\
                if (nf_complex_dist(&z, &roots->roots[ind]) < nf_setup_eps)    \
                {                                                              \
                    /*  Get the color corresponding to this root.            */\
                    c = colors[ind];                                           \
                    break;                                                     \
                }                                                              \
            }                                                                  \
                                                                               \
            /*  Darken the color based on the number of iterations required. */\
            scale = (double)(nf_setup_max_iters - iters)*nf_setup_color_scale; \
            nf_color_scaleby(&c, scale);                                       \
                                                                               \
            /*  Lastly, write this color to the ppm file.                    */\
            nf_color_write_to_ppm(&c, &ppm);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*  Close the PPM, destroy the root struct, and free the color array.    */\
    nf_ppm_close(&ppm);                                                        \
    nf_complex_roots_destroy(&roots);                                          \
                                                                               \
    /*  This line does not get a semi-colon since this is a macro. The user  */\
    /*  will add a semi-colon at the end of the call to this macro.          */\
    free(colors)

#endif
/*  End of include guard.                                                     */
