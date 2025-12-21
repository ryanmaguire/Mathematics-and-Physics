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
# pylint wants all of the variables to be SCREAMING_CASE. Ignore this.
# pylint: disable = invalid-name

# Note: ALL UNITS ARE IN METERS.
import numpy
import tmpyl
import common
from fresnel_integral import fresnel_integral

# Parameters for the aperture and observer.
width = 1.0E-03
height = 1.0E-03
distance = 1.0

# Produce of the wavelength and the distance, which appears in the formula.
lambda_z = common.wavelength * distance
factor = tmpyl.sqrt(2.0 / lambda_z)

# Compute the x and y integrals using the Fresnel integral.
x_term = fresnel_integral(common.x_vals, width, factor)
y_term = fresnel_integral(common.y_vals, height, factor)

# The intensity map is computed from the outer product of the
# x and y integrals. This is because these respective integrals
# are independent of each other, similar to what we saw in the
# Fraunhofer limit.
intensity = common.initial_intensity * numpy.outer(y_term, x_term)

# Make the plot and save it to a PNG file.
common.make_plots(intensity, __file__)
