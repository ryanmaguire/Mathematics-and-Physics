"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of Mathematics-and-Physics.                              #
#                                                                              #
#   Mathematics-and-Physics is free software: you can redistribute it and/or   #
#   modify it under the terms of the GNU General Public License as published   #
#   by the Free Software Foundation, either version 3 of the License, or       #
#   (at your option) any later version.                                        #
#                                                                              #
#   Mathematics-and-Physics is distributed in the hope that it will be useful, #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with Mathematics-and-Physics.  If not, see                           #
#   <https://www.gnu.org/licenses/>.                                           #
################################################################################
#   Purpose:                                                                   #
#       Provides a routine for raytracing the path of a particle.              #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

from . import vec3
from . import vec6
from . import setup
from . import ppm

def run(acc, stop, color, path, name):
    """
        Function:
            run
        Purpose:
            raytraces the path of a particle in a given system of motion.
        Arguments:
            acc (function):
                The function describing the equation of motion.
            stop (function):
                Function that determines when the raytracing stops.
            color (function):
                Function for coloring the image based on the result of
                the raytracing. This is usually a color pattern for a detector.
            path (function):
                The method of numerical raytracing. Usually Euler's method
                or fourth order Runge-Kutta.
            name (str):
                The name of the PPM file to be created.
        Outputs:
            None.
    """

    # Factor used for printing a progress report.
    prog_factor = 100.0 / float(setup.Y_SIZE)

    # Open the file and give it write permissions.
    ppm_file = ppm.PPM(name)

    # Initialize the ppm with default values in "setup".
    ppm_file.init()

    # Loop over each pixel for the PPM file.
    for y_ind in range(setup.Y_SIZE):

        # Loop over the x coordinates.
        for x_ind in range(setup.X_SIZE):

            # We're incrementing p across our detector.
            pos = setup.pixel_to_point(x_ind, y_ind)

            # Set the starting velocity.
            vel = vec3.Vec3(0.0, 0.0, -1.0)

            # Create the 6D vector from the position and velocity.
            phase_vec = vec6.Vec6(pos, vel)

            # Raytrace where the photon that hit p came from.
            path(phase_vec, acc, stop)

            # Get the color for the current pixel.
            col = color(phase_vec)

            # Write the color to the PPM file.
            col.write(ppm_file.file)

        # Print a status update.
        if y_ind % 20 == 0:
            print("Progress: %.4f%%  \r" % (prog_factor*y_ind), end = "")

    # Print a final progress report.
    print("Progress: 100.0000%%\nDone\n")

    # Close the file.
    ppm_file.close()
