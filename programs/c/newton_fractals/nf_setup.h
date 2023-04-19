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

/*  Parameters for the plots of functions.                                    */
static const double nf_setup_xmin = -2.0;
static const double nf_setup_xmax = +2.0;
static const double nf_setup_ymin = -2.0;
static const double nf_setup_ymax = +2.0;

/*  The number of pixels in the x and y axes.                                 */
static const unsigned int nf_setup_xsize = 1024U;
static const unsigned int nf_setup_ysize = 1024U;

/*  Scale factors for converting from pixels to points on the plane.          */
static const double nf_setup_px_factor = 3.906250E-03;
static const double nf_setup_py_factor = 3.906250E-03;

/*  The epsilon, or desired precision, in Newton's method.                    */
static const double nf_setup_eps = 1.0E-8;
static const double nf_setup_eps_sq = 1.0E-16;

/*  The maximum number of iterations allowed in Newton's method.              */
static const unsigned int nf_setup_max_iters = 32U;

/*  Color scale for darkening points based on the number of iterations needed.*/
static const double nf_setup_color_scale = 0.03125;

#endif
/*  End of include guard.                                                     */
