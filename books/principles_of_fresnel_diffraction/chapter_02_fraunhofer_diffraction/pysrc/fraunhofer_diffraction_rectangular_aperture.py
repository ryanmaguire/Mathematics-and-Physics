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
#       Makes a visual for Fraunhofer diffraction with a rectangular aperture. #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       March 20, 2025.                                                #
################################################################################
"""
# pylint wants all of the variables to be SCREAMING_CASE. Ignore this.
# pylint: disable = invalid-name

# Note: ALL UNITS ARE IN METERS.
import numpy
import matplotlib.pyplot as plt
import tmpyl

# Parameters for the monochromatic wave.
# Wavelength (lambda) is set to red, in the visible spectrum.
wavelength = 6.5E-07

# The initial intensity is the "I0" term that appears in
# the Fraunhofer equation. We can set it to 1 for simplicity.
initial_intensity = 1.0

# We'll clip the colors a bit so we can see the pattern more clearly.
clip = 0.025 * initial_intensity

# Parameters for the aperture. It is rectangular and
# centered about the origin. We only need a width and height.
# Visible light (which is what we are working with)
# diffracts through millimeter apertures (try this out yourself!),
# so if we set W and H to 10^-3 we should expect a nice pattern.
width = 1.0E-03
height = 1.0E-03

# Distance between the aperture and the screen.
# This is the "z" factor in the Fraunhofer equation.
# For Fraunhofer to hold, this should be much larger than
# width and height.
distance = 5.0E-01

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

# Multiplication is faster than division.
# Compute 1 / (lambda z) and store it as a new variable.
lambda_z = wavelength * distance
rcpr_lambda_z = 1.0 / lambda_z

# The Fraunhofer integral splits into two parts, x and y, and can
# be handled individually. The output for a rectangular aperture is the
# square of the normalized sinc function, given by sin(pi x) / (pi x)
# for non-zero x, and 1 at the origin.
x_term = numpy.square(tmpyl.sincpi(width * x_vals * rcpr_lambda_z))
y_term = numpy.square(tmpyl.sincpi(height * y_vals * rcpr_lambda_z))

# The intensity map for the (x, y) pixel is the product of sinc^2 for the
# x component and sinc^2 for the y component. All together, this is the
# "outer product" of the x and y arrays. Inner products take in two vectors
# and return a number, whereas outer products take in two vectors and
# return a matrix.
intensity = initial_intensity * numpy.outer(x_term, y_term)

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
axes.set_title("Fraunhofer Diffraction: Rectangular Aperture")

# We have significantly compressed the color scale so that
# darker regions appear far brighter. Indicate this on the plot.
figure.colorbar(image, ax = axes)

# Render the image and save it to a PNG file. The output PNG file will have the
# same file name as this file, but with the ".png" extension instead of ".py".
plt.savefig(__file__.rsplit('.', 1)[0] + ".png")
