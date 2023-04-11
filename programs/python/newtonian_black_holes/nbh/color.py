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
#       Provides a class for working with colors in RGB format.                #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

# File type TextIOWrapper given here.
import io

# Ceiling function given here.
import math

# 3D vector class provided here.
from . import vec3

# 6D vectors found here.
from . import vec6

# Default parameters given here.
from . import setup

# Class for working with colors.
class Color:
    """
        Class:
            Color
        Purpose:
            Basic color class for working with colors in RGB format.
    """

    # Constructor from the red, green, and blue components.
    def __init__(self, red, green, blue):
        """
            Function:
                __init__
            Purpose:
                Creates a Color class from RGB values.
            Arguments:
                red (int):
                    The red component of the color.
                green (int):
                    The green component of the color.
                blue (int):
                    The blue component of the color.
            Outputs:
                The color with RGB components given by the inputs.
        """

        # The inputs should be representable as integers. Try to convert.
        try:
            # Colors are 8-bit integers. Reduce mod 2^8 = 256 (0xFF = 255).
            self.red = abs(int(red)) & 0xFF
            self.green = abs(int(green)) & 0xFF
            self.blue = abs(int(blue)) & 0xFF

        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Cannot convert inputs to ints."
            ) from err

    # Writes a color to a PPM file.
    def write(self, file):
        """
            Function:
                write
            Purpose:
                Writes a color to a file.
            Arguments:
                file (io.TextIOWrapper):
                    The file the color is being written to.
        """
        if not isinstance(file, io.TextIOWrapper):
            raise TypeError(
                "\nError: Color\n"
                "    Can only write a Color instance to a file."
            )

        file.write("%u %u %u\n" % (self.red, self.green, self.blue))

    # Scales a color by a real number. Used for darkening.
    def __mul__(self, scale):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                scaled_color (Color):
                    self scaled by the scale factor.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        red = int(abs(scale_factor * self.red))
        green = int(abs(scale_factor * self.green))
        blue = int(abs(scale_factor * self.blue))
        return Color(red, green, blue)

    # Scales a color by a real number. Used for darkening.
    def __rmul__(self, scale):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                scaled_color (Color):
                    self scaled by the scale factor.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        red = int(abs(scale_factor * self.red))
        green = int(abs(scale_factor * self.green))
        blue = int(abs(scale_factor * self.blue))
        return Color(red, green, blue)

    # Scales a color by a real number. Used for darkening.
    def __imul__(self, scale):
        """
            Operator:
                Multiplication (*=).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                None.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        self.red = int(abs(scale_factor * self.red))
        self.green = int(abs(scale_factor * self.green))
        self.blue = int(abs(scale_factor * self.blue))
        return self

    # Add two colors by averaging over the components.
    def __add__(self, other):
        """
            Operator:
                Addition (+).
            Purpose:
                Adds two colors by averaging the RGB components.
            Arguments:
                other (Color):
                    The color being added to self.
            Outputs:
                sum (Color):
                    The sum of self and other.
        """

        # We can only add a color to another color.
        if not isinstance(other, Color):
            raise TypeError(
                "\nError: Color\n"
                "    Trying to add a Color to an object\n"
                "    that is not a Color."
            )

        # Average over the components.
        red = int(0.5*(self.red + other.red))
        green = int(0.5*(self.green + other.green))
        blue = int(0.5*(self.blue + other.blue))
        return Color(red, green, blue)

    # Add two colors by averaging over the components.
    def __iadd__(self, other):
        """
            Operator:
                Addition (+=).
            Purpose:
                Adds two colors by averaging the RGB components.
            Arguments:
                other (Color):
                    The color being added to self.
            Outputs:
                None.
        """

        # We can only add a color to another color.
        if not isinstance(other, Color):
            raise TypeError(
                "\nError: Color\n"
                "    Trying to add a Color to an object\n"
                "    that is not a Color."
            )

        # Average over the components.
        self.red = int(0.5*(self.red + other.red))
        self.green = int(0.5*(self.green + other.green))
        self.blue = int(0.5*(self.blue + other.blue))
        return self

# Constant colors that are useful.
RED = Color(0xFF, 0x00, 0x00)
GREEN = Color(0x00, 0xFF, 0x00)
BLUE = Color(0x00, 0x00, 0xFF)
WHITE = Color(0xFF, 0xFF, 0xFF)
BLACK = Color(0x00, 0x00, 0x00)

def checker_board(vec):
    """
        Function:
            checker_board
        Purpose:
            Creates a checker board pattern from a vector.
        Arguments:
            vec (Vec3 or Vec6):
                A 6D vector representing position and velocity or a
                3D vector representing position.
        Outputs:
            col (Color):
                The color given by the checker board pattern.
    """

    # Check if the type is a 6D vector.
    if not isinstance(vec, vec6.Vec6) and not isinstance(vec, vec3.Vec3):
        raise TypeError(
            "\nError: checker_board\n"
            "    Input must be a 3D or 6D vector."
        )

    # If the photon didn't make it, color the pixel black.
    if vec.pos.z_val > setup.Z_DETECTOR:
        return BLACK

    # Standard bit trick to get a red-white checker board pattern.
    if isinstance(vec, vec6.Vec6):
        checker = int(math.ceil(vec.pos.x_val) + math.ceil(vec.pos.y_val))
    else:
        checker = int(math.ceil(vec.x_val) + math.ceil(vec.y_val))

    # Factor for darkening the checker board.
    cfact = setup.Z_DETECTOR_SQ/vec.pos.norm_sq()

    # Use the bit-trick to color the board.
    if checker & 1:
        return RED*cfact
    return WHITE*cfact
