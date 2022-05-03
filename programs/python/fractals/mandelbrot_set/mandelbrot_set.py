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
#       Draw the mandelbrot set.                                               #
#   Notes:                                                                     #
#       This file is an extra and is not part of the libtmpl library.          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 1, 2021.                                                      #
################################################################################

# The width and height of the PPM file.
width = 1024;
height = 1024;

# The maximum number of iterations allowed while computing the fractal.
max_iters = 256;

# The maximum radius that will automatically be considered divergent.
radius = 4.0;

# The values of the rectangle that will be drawn.
x_min = -3.0;
x_max = 1.0;
y_min = -2.0;
y_max = 2.0;

# Factors for transforming a pixel to the corresponding point in the plane.
x_factor = (x_max - x_min)/(width - 1.0);
y_factor = (y_max - y_min)/(height - 1.0);

# Open the PPM file and give it write permissions.
fp = open("tmpl_mandelbrot_set.ppm", "w");

# Write the preamble to the PPM file. We'll use P3, which is text based, to
# ensure that this file renders properly on Windows.
fp.write("P3\n%d %d\n255\n" % (width, height));

# Loop over the y axis
for y in range(height):

    # Compute the corresponding y coordinate in the plane.
    c_y = y_max - y_factor*y;

    # Loop over the x pixels.
    for x in range(width):

        # Compute the corresponding x coordinate in the plane.
        c_x = x_min + x_factor*x;

        # Compute the complex number c_x + c_y i.
        c = complex(c_x, c_y);

        # Reset z back to zero and start the iteration.
        z = 0.0;

        # Perform the Mandelbrot iteration and see if the point diverges.
        for its in range(max_iters):
            z = z*z + c;

            if abs(z) >= radius:
                break;

        # If we never diverged, this point is part of the Mandelbrot set.
        if (its == max_iters - 1):
            red = 0;
            green = 0;
            blue = 0;

        # Otherwise, give a gradient to represent how many iterations it took
        # for the iteration to diverge.
        elif (its < 64):
            red = 4*its;
            green = 4*its;
            blue = 255 - 4*its;

        # Color points that take a very long time to diverge yellow.
        else:
            red = 255;
            green = 255;
            blue = 0;

        # Write this color to the PPM file
        fp.write("%u %u %u\n" % (red, green, blue));

    # End of x for-loop.
# End of y for-loop.

# Close the file and end the routine.
fp.close();

