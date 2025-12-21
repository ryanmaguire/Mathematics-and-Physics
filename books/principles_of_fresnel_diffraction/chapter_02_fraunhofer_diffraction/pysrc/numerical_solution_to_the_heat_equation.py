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
#       Simple numerical PDE methods applied to the heat equation.             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       December 21, 2025.                                             #
################################################################################
"""
# pylint wants all of the variables to be SCREAMING_CASE. Ignore this.
# pylint: disable = invalid-name

import numpy
from matplotlib import pyplot as plt

def update(temp, time, point, factor):
    """
        Compute the update for the heat equation
        using the finite difference method.
    """
    forward = temp[time, point + 1]
    backward = temp[time, point - 1]
    center = temp[time, point]
    shift = forward - 2.0*center + backward
    return factor * shift + center

# Boundary conditions for heat.
temp_left = 1.0E+00
temp_right = 0.0E+00

# The variable alpha from the heat equation.
heat_coeff = 0.25

# Parameters for the bar.
length = 1.0E+00
displacement = 1.0E-02

# Parameters for the duration of the experiment.
total_time = 1.0E-02
time_increment = 1.0E-04

# Scale factor used in the finite-difference method.
scale = heat_coeff * time_increment / (displacement ** 2)

# Total number of elements used in space and time.
number_of_time_steps = int(total_time / time_increment)
number_of_spatial_steps = int(length / displacement)

# Array for plotting the solution.
x_array = numpy.linspace(0.0, length, number_of_spatial_steps)

# Initialize an array for the solution to the heat equation.
# We will fill this in using the finite-difference method.
heat = numpy.zeros([number_of_time_steps, number_of_spatial_steps])

# The initial condition is f(x) = 1 for x <= 1/2, and 0 otherwise.
heat[0:, 0:number_of_spatial_steps >> 1] = temp_left

# The boundary conditions requires u(0, t) = 1 and u(L, t) = 0.
heat[:, 0] = temp_left
heat[:, -1] = temp_right

# Loop through the heat array and fill in the values using
# finite-difference method.
for t_index in range(number_of_time_steps - 1):
    for x_index in range(1, number_of_spatial_steps - 1):
        heat[t_index + 1, x_index] = update(heat, t_index, x_index, scale)

# Plot the result.
plt.plot(x_array, heat[-1])
plt.ylabel("Temperature (Celcius)")
plt.xlabel("Distance (Meters)")
plt.savefig(__file__.rsplit('.', 1)[0] + ".png")
