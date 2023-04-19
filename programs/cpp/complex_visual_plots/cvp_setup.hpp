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
 *  Date:   2023/04/16                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_SETUP_HPP
#define CVP_SETUP_HPP

/*  Namespace for this mini-project. "Complex Visual Plots."                  */
namespace cvp {

    /*  Another namespace to avoid name conflicts with other constants.       */
    namespace setup {

        /*  The plotting parameters for functions.                            */
        const double xmin = -2.0;
        const double xmax = +2.0;
        const double ymin = -2.0;
        const double ymax = +2.0;

        /*  The number of pixels in the x and y axes.                         */
        const unsigned int xsize = 1024U;
        const unsigned int ysize = 1024U;

        /*  Factors for converting from pixels to points in the plane.        */
        const double pxfactor = (xmax - xmin) / static_cast<double>(xsize);
        const double pyfactor = (ymax - ymin) / static_cast<double>(ysize);
    }
    /*  End of namespace "setup".                                             */
}
/*  End of namespace "cvp".                                                   */

#endif
/*  End of include guard.                                                     */
