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
 *      Provides default parameters for drawings.                             *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/17                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef MSD_SETUP_H
#define MSD_SETUP_H

/*  User defined parameters for the fractals.                                 */
#define MSD_XMIN (-1.2)
#define MSD_XMAX (+1.2)
#define MSD_YMIN (-1.2)
#define MSD_YMAX (+1.2)
#define MSD_XSIZE (1024U)
#define MSD_YSIZE (1024U)

/*  Parameters for the plots.                                                 */
static const double msd_setup_xmin = MSD_XMIN;
static const double msd_setup_xmax = MSD_XMAX;
static const double msd_setup_ymin = MSD_YMIN;
static const double msd_setup_ymax = MSD_YMAX;

/*  The number of pixels in the x and y axes.                                 */
static const unsigned int msd_setup_xsize = MSD_XSIZE;
static const unsigned int msd_setup_ysize = MSD_YSIZE;

/*  Scale factors for converting from pixels to points on the plane.          */
static const double msd_setup_px_factor = (MSD_XMAX - MSD_XMIN) / MSD_XSIZE;
static const double msd_setup_py_factor = (MSD_YMAX - MSD_YMIN) / MSD_YSIZE;

/*  Undefine all macros.                                                      */
#undef MSD_XMIN
#undef MSD_XMAX
#undef MSD_YMIN
#undef MSD_YMAX
#undef MSD_XSIZE
#undef MSD_YSIZE

#endif
/*  End of include guard.                                                     */
