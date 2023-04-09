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
 *      Provides function types that are commonly used.                       *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/05                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_FUNCTION_TYPES_H
#define NBH_FUNCTION_TYPES_H

/*  Booleans found here.                                                      */
#include "nbh_bool.h"

/*  3D vectors found here.                                                    */
#include "nbh_vec3.h"

/*  6D vectors defined here.                                                  */
#include "nbh_vec6.h"

/*  Colors for working with PPM files provided here.                          */
#include "nbh_color.h"

/*  Functions for describing equations of motion.                             */
typedef struct nbh_vec3 (*acceleration)(const struct nbh_vec3 *);

/*  Functions for determining if a photon is still in motion.                 */
typedef nbh_bool (*stopper)(const struct nbh_vec3 *);

/*  Functions that color the plane behind the black hole.                     */
typedef struct nbh_color (*colorer)(const struct nbh_vec6 *);

/*  Functions for raytracing the path of light.                               */
typedef void (*raytracer)(struct nbh_vec6 *, acceleration, stopper);

#endif
/*  End of include guard.                                                     */
