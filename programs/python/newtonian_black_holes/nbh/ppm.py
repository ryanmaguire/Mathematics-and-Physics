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
#       Provides a class for working with PPM files.                           #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

# Default parameters given here.
from . import setup

# Basic class for dealing with PPM files.
class PPM:
    """
        Class:
            PPM
        Purpose:
            Provides routines for creating and working with PPM files.
    """

    # Constructore from a string, the name of the file.
    def __init__(self, name):
        """
            Function:
                __init__
            Purpose:
                Creates a PPM file with the given name.
            Arguments:
                name (str):
                    The name of the PPM file.
        """

        # The input should be a string.
        if not isinstance(name, str):
            raise TypeError(
                "\nError: PPM\n"
                "    Input must be a string, the name of the file."
            )

        # Otherwise open the file and give it write permissions.
        self.file = open(name, "w")

    # Initializes the PPM file with the given values.
    def init_from_vals(self, x_size, y_size):
        """
            Function:
                init_from_vals
            Purpose:
                Creates the preamble of the PPM file.
            Arguments:
                x_size (int):
                    The number of pixels in the x direction.
                y_size (int):
                    The number of pixels in the y direction.
            Outputs:
                None.
        """

        # The two inputs should be representable as ints. Try to convert.
        try:
            x_pixels = abs(int(x_size))
            y_pixels = abs(int(y_size))

        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: PPM\n"
                "    Input values must be representable as ints."
            ) from err

        # Create the preamble.
        self.file.write("P3\n%u %u\n255\n" % (x_pixels, y_pixels))

    # Initialize using the default parameters in setup.py.
    def init(self):
        """
            Function:
                init
            Purpose:
                Creates the preamble using the values in setup.py.
            Arguments:
                None.
            Outputs:
                None.
        """

        # Pass the values in setup.py to init_from_vals.
        self.init_from_vals(setup.X_SIZE, setup.Y_SIZE)

    # Closes the PPM file.
    def close(self):
        """
            Function:
                close
            Purpose:
                Closes the PPM file.
            Arguments:
                None.
            Outputs:
                None.
        """

        # The file type has a close method. Use this.
        self.file.close()
