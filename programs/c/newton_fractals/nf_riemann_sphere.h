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
 *      Routines for mixing the complex plane with the 2-sphere.              *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/08                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_RIEMANN_SPHERE_H
#define NF_RIEMANN_SPHERE_H

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Struct for working with complex numbers.                                  */
#include "nf_complex.h"

/*  Spherical geometry routines.                                              */
#include "nf_spherical.h"

/*  2D Euclidean geometry and vector routines.                                */
#include "nf_vec2.h"

/*  3D Euclidean geometry and vector routines.                                */
#include "nf_vec3.h"

NF_INLINE void
nf_complex_unit_disk_to_plane(struct nf_complex *z, const struct nf_vec3 *u)
{
    const struct nf_vec2 p = {z->real, z->imag};
    const struct nf_vec3 s = nf_inverse_orthographic_projection(&p, u);
    const struct nf_vec2 proj_s = nf_stereographic_projection(&s);
    z->real = proj_s.x;
    z->imag = proj_s.y;
}

#endif
/*  End of include guard.                                                     */
