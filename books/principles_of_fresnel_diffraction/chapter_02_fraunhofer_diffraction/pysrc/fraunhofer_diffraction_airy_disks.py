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
#       Creates a visual for Fraunhofer diffraction with a circular aperture.  #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       December 21, 2025.                                             #
################################################################################
"""
# pylint wants all of the variables to be SCREAMING_CASE. Ignore this.
# pylint: disable = invalid-name

# Note: ALL UNITS ARE IN METERS.
import numpy
import matplotlib.pyplot as plt
import tmpyl

# Set I0 to 1 for simplicity.
initial_intensity = 1.0

# Clip to make dark colors a little brighter.
clip = 0.025 * initial_intensity

# We again use red light.
wavelength = 6.5E-07

# Parameters for the aperture.
# It is circular, we only need the radius.
radius = 5.0E-04

# Distance between the aperture and the screen.
# This must be much larger than the radius.
distance = 5.0E-01

# Scale factor for the independent variable.
factor = 2.0 * numpy.pi * radius / (distance * wavelength)

# Parameters for the image.
x_size = 5.0E-03
y_size = 5.0E-03
x_pixels = 2048
y_pixels = 2048
plot_boundaries = [-x_size, x_size, -y_size, y_size]

# Step sizes used for sampling the x and y axes.
x_displacement = 2.0 * x_size / float(x_pixels)
y_displacement = 2.0 * y_size / float(y_pixels)

# Arrays for the two axes.
x_vals = numpy.arange(-x_size, x_size, x_displacement)
y_vals = numpy.arange(-y_size, y_size, y_displacement)

# Parameters for the image.
x_grid, y_grid = numpy.meshgrid(x_vals, y_vals)
plane_vals = numpy.sqrt(x_grid**2 + y_grid**2)
arg = factor * plane_vals

intensity = initial_intensity * numpy.array(
    [numpy.square(tmpyl.airy_j1(arr)) for arr in arg]
)

# Make the plots.
figure, axes = plt.subplots()

image = axes.imshow(
    intensity,
    extent = plot_boundaries,
    cmap = 'hot',
    vmin = 0.0,
    vmax = clip
)

# Add labels for the axes and the plot.
axes.set_xlabel("x (meters)")
axes.set_ylabel("y (meters)")
axes.set_title("Fraunhofer Diffraction: Circular Aperture")
figure.colorbar(image, ax = axes)

# Render the plot.
plt.savefig(__file__.rsplit('.', 1)[0] + ".png")
