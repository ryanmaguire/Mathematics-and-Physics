"""
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
#       Draw the Barnsley fern.                                                #
#   Notes:                                                                     #
#       This file is an extra and is not part of the libtmpl library.          #
#       This is a modification of some ideas I found while browsing reddit.    #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 12, 2021.                                                     #
################################################################################
#   2021/08/30: Ryan Maguire                                                   #
#       Updated code to get rid of pylint warnings.                            #
################################################################################
"""

# Needed for random() which gives us a random number between 0 and 1.
import random

# Width and height, in pixels, of the output PPM file.
WIDTH = 720
HEIGHT = 720

# Factors determining the growth and spread of the fern in the fractal.
FACTOR = 0.5
GROW = (1.0 - (FACTOR - 1.0) ** 4) * 0.85

# Total number of iterations to be run.
TOTAL = WIDTH * HEIGHT * 50

# Number of iterations to be run before printing an update to the screen.
UPDATE = 1000000

# Function for computing the Barnsley fractal.
def compute_fern(verbose=False):
    """
        Function Name:
            compute_fern
        Purpose:
            Computes the values of the pixels for the Barnsley fern.
        Arguments:
            verbose:
                Boolean for determining if updates should print.
                Default is False (nothing will print).
        Outputs:
            data:
                A list that is WIDTH * HEIGHT long whose elements correspond
                to the intensity of the pixels of the image.
    """
    data = [0.0] * (WIDTH * HEIGHT)
    x_val = 0.0
    y_val = 1.0

    for current_iteration in range(TOTAL):
        random_value = random.random()*100.0
        x_new = x_val
        y_new = y_val

        if random_value < 1.0:
            x_val = 0.0
            y_val = 0.16*y_new
        elif random_value < 86.0:
            x_val = GROW*x_new + 0.04*y_new
            y_val = -0.04*x_new + 0.85*y_val + 1.6
        elif random_value < 93.0:
            x_val = 0.20*x_new - 0.26*y_new
            y_val = 0.23*x_new + 0.22*y_new + 1.6
        else:
            x_val = -0.15*x_new + 0.28*y_new
            y_val = 0.26*x_new + 0.24*y_new + 0.44

        x_coordinate = int(WIDTH * (0.45 + 0.195*x_val))
        y_coordinate = int(HEIGHT * (1.0 - 0.099*y_val))
        data[x_coordinate + y_coordinate*WIDTH] += 1.0

        if verbose:
            if current_iteration % UPDATE == 0:
                print("Current: %d Total: %d" % (current_iteration, TOTAL))

    return data

def write_file(data, filename):
    """
        Function Name:
            write_file
        Purpose:
            Creates a PPM file corresponding to the input data.
        Arguments:
            data:
                A list that has WIDTH * HEIGHT many elements. The values
                correspond to the intensity of a given pixel.
            filename:
                A string corresponding to the created file. It should end with
                .ppm since the function creates a PPM file.
        Outputs:
            None.
    """

    file = open(filename, "w")
    file.write("P3\n%u %u\n255\n" % (WIDTH, HEIGHT))

    for y_val in range(HEIGHT):
        for x_val in range(WIDTH):
            pixel = data[x_val + y_val*WIDTH]
            grey = max(0.0, (256.0 - pixel) / 256.0)
            val = 255*int(grey ** 6)
            file.write("%u %u %u\n" % (val, val, val))

    file.close()

if __name__ == "__main__":
    pixels = compute_fern(verbose=True)
    write_file(pixels, "tmpl_barnsley_fern.ppm")
