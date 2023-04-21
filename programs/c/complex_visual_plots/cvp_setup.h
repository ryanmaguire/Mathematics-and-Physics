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
 *  Date:   2023/04/21                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_SETUP_H
#define CVP_SETUP_H

/*  The plotting parameters for functions.                                    */
static const double cvp_setup_xmin = -2.0;
static const double cvp_setup_xmax = +2.0;
static const double cvp_setup_ymin = -2.0;
static const double cvp_setup_ymax = +2.0;

/*  The number of pixels in the x and y axes.                                 */
static const unsigned int cvp_setup_xsize = 1024U;
static const unsigned int cvp_setup_ysize = 1024U;

/*  Factors for converting from pixels to points in the plane.                */
static const double cvp_setup_pxfactor = 3.906250E-03;
static const double cvp_setup_pyfactor = 3.906250E-03;

#endif
/*  End of include guard.                                                     */
