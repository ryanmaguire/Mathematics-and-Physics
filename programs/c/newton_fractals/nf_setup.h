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
 *      Provides default parameters for complex plots.                        *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_SETUP_H
#define NF_SETUP_H

/*  NF_INLINE macro found here.                                               */
#include "nf_inline.h"

/*  User defined parameters for the fractals.                                 */
#define NF_XMIN (-2.0)
#define NF_XMAX (+2.0)
#define NF_YMIN (-2.0)
#define NF_YMAX (+2.0)
#define NF_XSIZE (1024U)
#define NF_YSIZE (1024U)
#define NF_MAX_ITERS (32U)

/*  Parameters for the plots of functions.                                    */
static const double nf_setup_xmin = NF_XMIN;
static const double nf_setup_xmax = NF_XMAX;
static const double nf_setup_ymin = NF_YMIN;
static const double nf_setup_ymax = NF_YMAX;

/*  The number of pixels in the x and y axes.                                 */
static const unsigned int nf_setup_xsize = NF_XSIZE;
static const unsigned int nf_setup_ysize = NF_YSIZE;

/*  Scale factors for converting from pixels to points on the plane.          */
static const double nf_setup_px_factor = (NF_XMAX - NF_XMIN) / NF_XSIZE;
static const double nf_setup_py_factor = (NF_YMAX - NF_YMIN) / NF_YSIZE;

/*  The epsilon, or desired precision, in Newton's method.                    */
static const double nf_setup_eps = 1.0E-8;
static const double nf_setup_eps_sq = 1.0E-16;

/*  The maximum number of iterations allowed in Newton's method.              */
static unsigned int nf_setup_max_iters = NF_MAX_ITERS;

/*  Color scale for darkening points based on the number of iterations needed.*/
static double nf_setup_color_scale = 1.0 / (double)NF_MAX_ITERS;

/******************************************************************************
 *  Function:                                                                 *
 *      nf_reset_max_iters                                                    *
 *  Purpose:                                                                  *
 *      Resets the maximum iterations allowed in Newton's method.             *
 *  Arguments:                                                                *
 *      iters (unsigned int):                                                 *
 *          The maximum iterations in Newton's method.                        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NF_INLINE void
nf_reset_max_iters(unsigned int iters)
{
    nf_setup_max_iters = iters;
    nf_setup_color_scale = 1.0 / (double)iters;
}

/*  Undefine all macros.                                                      */
#undef NF_XMIN
#undef NF_XMAX
#undef NF_YMIN
#undef NF_YMAX
#undef NF_XSIZE
#undef NF_YSIZE
#undef NF_MAX_ITERS

#endif
/*  End of include guard.                                                     */
