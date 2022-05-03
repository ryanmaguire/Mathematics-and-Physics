################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Purpose:                                                                   #
#       Draw the "SwipeCat fractal." This a variant of the Mandelbrot set      #
#       posted by user SwipeCat on Reddit that I decided to take a crack at.   #
#       This code uses very little of the Python standard library, and runs    #
#       with both Python 2 and Python 3. The output is a PPM file.             #
#   Notes:                                                                     #
#       This file is an extra and is not compiled as part of libtmpl.          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 1, 2021.                                                      #
################################################################################

# The natural logarithm function is found here.
import math;

# And complex exponentiation is found here.
import cmath;

# The width and height of the PPM file.
width = 1200;
height = 960;

# The maximum number of iterations allowed while computing the fractal.
imax = 100;

# The maximum radius such that points will automatically be consider divergent.
zmax = 150;

# The values of the rectangle that will be drawn.
x_min = -6.6;
x_max = -0.4;
y_min = -3.095;
y_max = 3.105;

# Factors for transforming a pixel to the corresponding point in the plane.
x_factor = (x_max - x_min)/(width - 1.0);
y_factor = (y_max - y_min)/(height - 1.0);

# Open the PPM file and give it write permissions.
fp = open("swipecat_fractal.ppm", "w");

# Write the preamble to the PPM file. We'll use P3, which is text based, to
# ensure that this file renders properly on Windows.
fp.write("P3\n%d %d\n255\n" % (width, height));

for y in range(height):
    z_y = y_max - y_factor*y;
    for x in range(width):
        z_x = x_min + x_factor*x;
        c = complex(z_x, z_y);
        z = 0.0;
        backgnd = 0.0;
        for its in range(imax):
            z = 0.5*math.pi * (cmath.exp(z) - z) + c;
            if abs(z.real) >= zmax:
                backgnd = math.log(math.log(abs(z.real) + 1.0) * 0.33333333333);
                backgnd = math.log(abs(its - backgnd)) * 0.3076923076923077;
                break;

        val = max(0.0, 1.0 - abs(1.0 - backgnd));
        if (backgnd <= 1.0):
            r = int(255.0 * val**4);
            g = int(255.0 * val**2.5);
            b = int(255.0 * val);
        else:
            r = int(255.0 * val);
            g = int(255.0 * val**1.5);
            b = int(255.0 * val**3);

        fp.write("%u %u %u\n" % (r, g, b));
fp.close();

