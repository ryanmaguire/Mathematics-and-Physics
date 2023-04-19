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
 *      Implementation of Hubbard, Schleicher, and Sutherland's algorithm for *
 *      finding all roots of a complex polynomial.                            *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COMPLEX_ROOTS_H
#define NF_COMPLEX_ROOTS_H

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Complex number struct given here.                                         */
#include "nf_complex.h"

/*  Polynomials with real coefficients provided here.                         */
#include "nf_real_poly.h"

/*  Polynomials with complex coefficients given here.                         */
#include "nf_complex_poly.h"

/*  Struct for the roots of a real or complex polynomial.                     */
struct nf_complex_roots {

    /*  Array for the roots of a polynomial.                                  */
    struct nf_complex *roots;

    /*  The number of elements in the above array.                            */
    unsigned int number_of_roots;
};

#endif
/*  End of include guard.                                                     */
