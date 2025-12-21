"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of newtonian_black_holes.                                #
#                                                                              #
#   newtonian_black_holes is free software: you can redistribute it and/or     #
#   modify it under the terms of the GNU General Public License as published   #
#   by the Free Software Foundation, either version 3 of the License, or       #
#   (at your option) any later version.                                        #
#                                                                              #
#   newtonian_black_holes is distributed in the hope that it will be useful,   #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with newtonian_black_holes.  If not, see                             #
#   <https://www.gnu.org/licenses/>.                                           #
################################################################################
#   Purpose:                                                                   #
#       Makes a visual for Fresnel diffraction with a rectangular aperture.    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       December 21, 2025.                                             #
################################################################################
"""
import tmpyl

# Fresnel diffraction is computed using the Fresnel sine and cosine
# functions. These are provided by tmpyl.
def fresnel_integral(arg, length, factor):
    """
        Evaluates the Fresnel integrals
        the appear in the diffraction formula
        for a rectangular aperture.
    """
    # Parameters for the Fresnel integrals.
    left = factor * (arg - length)
    right = factor * (arg + length)

    # The integral of the real part of the formula.
    cright = tmpyl.normalized_fresnel_cos(right)
    cleft = tmpyl.normalized_fresnel_cos(left)
    carg = cright - cleft

    # The integral of the imaginary part.
    sright = tmpyl.normalized_fresnel_sin(right)
    sleft = tmpyl.normalized_fresnel_sin(left)
    sarg = sright - sleft

    # Normalize the output to 1.
    integral = carg + 1.0j * sarg
    abs_integral = abs(integral)
    peak = max(abs_integral)
    return (abs_integral / peak) ** 2
