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
            self.red = abs(int(red)) % 255
            self.green = abs(int(green)) % 255
            self.blue = abs(int(blue)) % 255

        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Cannot convert inputs to ints."
            ) from err
