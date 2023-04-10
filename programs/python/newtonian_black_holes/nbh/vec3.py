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
#       Provides a class for working with vectors in R^3.                      #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 10, 2023.                                                #
################################################################################
"""

# sqrt function provided here.
import math

# Basic Python class for dealing with vectors in R^3.
class Vec3:
    """
        Class:
            nbh.Vec3
        Purpose:
            Three dimensional Euclidean vector class with vector arithmetic and
            basic geometrical properties included.
        Methods:
            norm_sq:
                Computes the square of the Euclidean norm.
            norm:
                Computes the Euclidean norm.
    """

    # Initialize a 3D vector from three floats, the rectangular coordinates.
    def __init__(self, x_val, y_val, z_val):
        """
            Function:
                __init__
            Purpose:
                Initializes a vector with the given Cartesian values.
            Arguments:
                x_val (float / int):
                    The x-coordinate of the vector.
                y_val (float / int):
                    The y-coordinate of the vector.
                z_val (float / int):
                    The z-coordinate of the vector.
            Outputs:
                vec (nbh.Vec3):
                    The vector with Cartesian coordinates (x_val, y_val, z_val).
        """

        # We only set objects that can be converted to floats. Try this.
        try:
            self.x_val = float(x_val)
            self.y_val = float(y_val)
            self.z_val = float(z_val)
        except TypeError as err:
            raise TypeError(
                "Error: nbh.Vec3\n"
                "    Inputs could not be converted to floats."
            ) from err

    # + operator for vector addition.
    def __add__(self, other):
        """
            Operator:
                Addition (+):
            Purpose:
                Performs vector addition in R^3.
            Arguments:
                other (nbh.Vec3):
                    The vector being added to self.
            Outputs:
                sum (nbh.Vec3):
                    The vector sum of self and other.
            Method:
                Add the vectors component-wise. If self and other are
                represented as v = (vx, vy, vz) and w = (wx, wy, wz),
                respectively, the sum is then:

                    v + w = (vx, vy, vz) + (wx, wy, wz)
                          = (vx + wx, vy + wy, vz + wz)

                That is, vector addition is done component-wise.
        """

        # It is only valid to add another Vec3 class to the vector.
        if not isinstance(other, Vec3):
            raise TypeError(
                "Error: nbh.Vec3\n"
                "    Trying to sum a Vec3 instance with an object that is"
                "    not of type nbh.Vec3."
            )

        # Vector addition is performed component-wise.
        x_sum = self.x_val + other.x_val
        y_sum = self.y_val + other.y_val
        z_sum = self.z_val + other.z_val
        return Vec3(x_sum, y_sum, z_sum)

    # += operator for vector addition.
    def __iadd__(self, other):
        """
            Operator:
                Addition (+=):
            Purpose:
                Performs vector addition in R^3.
            Arguments:
                other (nbh.Vec3):
                    The vector being added to self.
            Outputs:
                None
            Method:
                Perform vector addition component-wise and store
                the result in self.
        """

        # It is only valid to add another Vec3 class to the vector.
        if not isinstance(other, Vec3):
            raise TypeError(
                "Error: nbh.Vec3\n"
                "    Trying to sum a Vec3 instance with an object that"
                "    is not of type nbh.Vec3."
            )

        # Vector addition is performed component-wise.
        self.x_val += other.x_val
        self.y_val += other.y_val
        self.z_val += other.z_val

    # Computes the square of the length of the vector.
    def norm_sq(self):
        """
            Function:
                norm_sq
            Purpose:
                Computes the square of the Euclidean norm of the vector.
            Arguments:
                None.
            Outputs:
                abs_sq (float):
                    The square of the magnitude of the vector.
            Method:
                Use the Pythagorean formula and compute. If the vector v is
                represented as v = (x, y, z), then:

                    ||v||^2 = x^2 + y^2 + z^2

                This is computed and the sum is returned.
        """

        # Using Pythagoras, compute the squares of the computes.
        x_sq = self.x_val*self.x_val
        y_sq = self.y_val*self.y_val
        z_sq = self.z_val*self.z_val

        # Return the sum of the squares.
        return x_sq + y_sq + z_sq

    # Computes the length of the vector.
    def norm(self):
        """
            Function:
                norm
            Purpose:
                Computes the Euclidean norm of the vector.
            Arguments:
                None.
            Outputs:
                abs (float):
                    The magnitude of the vector.
            Method:
                Use the Pythagorean formula and compute. If the vector v is
                represented as v = (x, y, z), then:

                    ||v|| = sqrt(x^2 + y^2 + z^2)

                This is computed and the magnitude is returned.
        """
        return math.sqrt(self.norm_sq())

    # Also computes the length of the vector.
    def __abs__(self):
        """
            Function:
                __abs__
            Purpose:
                Computes the Euclidean norm of the vector.
            Arguments:
                None.
            Outputs:
                abs (float):
                    The magnitude of the vector.
            Method:
                Call self.norm and return.
        """
        return self.norm()
