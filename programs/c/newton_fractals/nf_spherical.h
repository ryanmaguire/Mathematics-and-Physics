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
 *      Provides routines for spherical geometry.                             *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/08                                                        *
 ******************************************************************************/

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Basic 2D vector struct and routines.                                      */
#include "nf_vec2.h"

/*  3D Euclidean geometry and 3D vectors.                                     */
#include "nf_vec3.h"

/*  Computes the stereographic projection about a point on a sphere.          */
NF_INLINE struct nf_vec2
nf_stereographic_projection(const struct nf_vec3 *u)
{
    struct nf_vec2 out;

    const double denom = 1.0 / (1.0 - u->z);

    out.x = u->x * denom;
    out.y = u->y * denom;
    return out;
}

NF_INLINE struct nf_vec3
nf_inverse_orthographic_projection(const struct nf_vec2 *p,
                                   const struct nf_vec3 *u)
{
    struct nf_vec3 out, X, Y;
    const double z = sqrt(1.0 - nf_vec2_normsq(p));

    if (u->x == 0.0)
    {
        X.x = 1.0;
        X.y = 0.0;
        X.z = 0.0;
    }
    else
    {
        if (u->y == 0.0)
        {
            X.x = 0.0;
            X.y = 1.0;
            X.z = 0.0;
        }
        else
        {
            X.x = 1.0;
            X.y = -u->y /u->x;
            X.z = 0.0;
        }

        nf_vec3_normalizeself(&X);
    }

    Y = nf_vec3_cross_product(&X, u);

    out.x = p->x*X.x + p->y*Y.x + z*u->x;
    out.y = p->x*X.y + p->y*Y.z + z*u->y;
    out.z = p->x*X.z + p->y*Y.y + z*u->z;

    return out;
}
