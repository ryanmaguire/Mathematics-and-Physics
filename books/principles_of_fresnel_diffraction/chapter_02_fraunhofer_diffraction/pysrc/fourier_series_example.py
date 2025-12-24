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
#       Simple example of using the Fourier expansion for a smooth function.   #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       December 19, 2025.                                             #
################################################################################
"""
# pylint wants all of the variables to be SCREAMING_CASE. Ignore this.
# pylint: disable = invalid-name

import numpy
import matplotlib.pyplot as plt

# The constant factor we found in our computation.
FOURIER_FACTOR = 4 / numpy.pi ** 3

def fourier_coeff(index):
    """
        Computes the nth coefficients for the
        Fourier expansion of x(1-x) on the interval [0, 1].
    """
    numer = 1 - (-1)**index
    denom = index**3

    return FOURIER_FACTOR * numer / denom

def fourier_expansion(x_val, degree):
    """
        Computes the Fourier expansion of x(1-x)
        up to a user-provided degree.

        Note:
            The even degree contributions are all zero.
            That is, degree = 2n and degree = 2n - 1
            will produce the same approximation.
    """
    out = 0

    # Perform the sum iteratively.
    for index in range(1, degree + 1):

        # The wavelength of the current wave is given by the
        # index and the length of the interval. Since we are
        # working on the unit interval [0, 1], the scale
        # factor is n*pi. That is, the current wave is
        # described by sin(n*pi*x).
        wave = numpy.sin(index * numpy.pi * x_val)

        # The amplitudes of the waves must decay for the
        # Fourier series to be valid (this is the Riemann-Lebesgue theorem).
        coeff = fourier_coeff(index)

        # Update our approximation with the damped wave.
        out += coeff * wave

    return out

x_array = numpy.arange(0, 1, 1.0E-2)
y_array = x_array * (1.0 - x_array)

plt.subplot(2, 1, 1)
plt.plot(x_array, y_array, label = "Initial Condition")
plt.xlabel("Horizontal Coordinate (Meters)")
plt.ylabel("Temperature (Celcius)")
plt.title("Fourier Expansion")

plt.subplot(2, 1, 2)
plt.xlabel("Horizontal Coordinate (Meters)")
plt.ylabel("Temperature (Celcius)")
plt.title("Degree 1, 3, and 5 Approximation Error")

for ind in range(1, 4):
    f_array = fourier_expansion(x_array, 2*ind - 1)
    plt.plot(x_array, f_array - y_array, label = f"Degree {2*ind - 1} Error")

plt.legend()

plt.subplot(2, 1, 1)
f_array = fourier_expansion(x_array, 3)

plt.plot(x_array, f_array, label = "Degree 3 Fourier Approximation")
plt.legend()
plt.tight_layout()
plt.savefig(__file__.rsplit('.', 1)[0] + ".png")
