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
        Operators:
            + (vector addition)
            += (in-place vector addition)
            - (vector subtraction)
            -= (in-place vector subtraction)
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
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: nbh.Vec3\n"
                "    Inputs could not be converted to floats."
            ) from err

    # + operator for vector addition.
    def __add__(self, other):
        """
            Operator:
                Addition (+).
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
                "\nError: nbh.Vec3\n"
                "    Trying to sum a Vec3 instance with an object that is\n"
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
                Addition (+=).
            Purpose:
                Performs vector addition in-place.
            Arguments:
                other (nbh.Vec3):
                    The vector being added to self.
            Outputs:
                self
            Method:
                Perform vector addition component-wise and store
                the result in self.
        """

        # It is only valid to add another Vec3 class to the vector.
        if not isinstance(other, Vec3):
            raise TypeError(
                "Error: nbh.Vec3\n"
                "    Trying to sum a Vec3 instance with an object that\n"
                "    is not of type nbh.Vec3."
            )

        # Vector addition is performed component-wise.
        self.x_val += other.x_val
        self.y_val += other.y_val
        self.z_val += other.z_val
        return self

    # - operator for vector subtraction.
    def __sub__(self, other):
        """
            Operator:
                Subtraction (-).
            Purpose:
                Performs vector subtraction in R^3.
            Arguments:
                other (nbh.Vec3):
                    The vector being subtracted from self.
            Outputs:
                diff (nbh.Vec3):
                    The vector difference of self and other.
            Method:
                Subtract the vectors component-wise. If self and other are
                represented as v = (vx, vy, vz) and w = (wx, wy, wz),
                respectively, the difference is then:

                    v - w = (vx, vy, vz) - (wx, wy, wz)
                          = (vx - wx, vy - wy, vz - wz)

                That is, vector subtraction is done component-wise.
        """

        # It is only valid to subtract another Vec3 class from the vector.
        if not isinstance(other, Vec3):
            raise TypeError(
                "\nError: nbh.Vec3\n"
                "    Trying to compute the difference of an nbh.Vec3\n"
                "    with an object that is not of type nbh.Vec3."
            )

        # Vector subtraction is performed component-wise.
        x_diff = self.x_val - other.x_val
        y_diff = self.y_val - other.y_val
        z_diff = self.z_val - other.z_val
        return Vec3(x_diff, y_diff, z_diff)

    # +- operator for vector subtraction.
    def __isub__(self, other):
        """
            Operator:
                Subtraction (-=).
            Purpose:
                Performs vector subtraction in-place.
            Arguments:
                other (nbh.Vec3):
                    The vector being subtracted from self.
            Outputs:
                self
            Method:
                Perform vector subtraction component-wise and store
                the result in self.
        """

        # It is only valid to add another Vec3 class to the vector.
        if not isinstance(other, Vec3):
            raise TypeError(
                "Error: nbh.Vec3\n"
                "    Trying to sum a Vec3 instance with an object that"
                "    is not of type nbh.Vec3."
            )

        # Vector subtraction is performed component-wise.
        self.x_val -= other.x_val
        self.y_val -= other.y_val
        self.z_val -= other.z_val
        return self

    # * operator for scalar multiplication.
    def __mul__(self, scalar):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Performs scalar multiplication of a vector with a float.
            Arguments:
                scalar (float):
                    A real number.
            Outputs:
                scaled_vector (nbh.Vec3):
                    The vector 'self' scaled by the input scalar.
            Method:
                Scalar multiplication is computed component-wise. If self is
                represented by the vector v = (x, y, z), then:

                    prod = a*v
                         = a*(x, y, z)
                         = (ax, ay, az)

                Where a is the input scalar.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            val = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: nbh.Vec3\n"
                "    Trying to multiply an nbh.Vec3 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        x_prod = val*self.x_val
        y_prod = val*self.y_val
        z_prod = val*self.z_val
        return Vec3(x_prod, y_prod, z_prod)

    # *= operator for scalar multiplication.
    def __imul__(self, scalar):
        """
            Operator:
                Multiplication (*=).
            Purpose:
                Performs scalar multiplication in-place.
            Arguments:
                scalar (float):
                    A real number.
            Outputs:
                self.
            Method:
                Perform scalar multiplication component-wise in-place.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            val = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: nbh.Vec3\n"
                "    Trying to multiply an nbh.Vec3 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        self.x_val *= val
        self.y_val *= val
        self.z_val *= val
        return self

    # Euclidean dot product.
    def dot(self, other):
        """
            Function:
                dot
            Purpose:
                Computes the Euclidean dot product of self with other.
            Arguments:
                other (nbh.Vec3):
                    Another vector.
            Outputs:
                dot_prod (float):
                    The dot product of self with other.
            Method:
                Use the standard dot product formula. If self and other are
                represented by v = (vx, vy, vz) and w = (wx, wy, wz),
                respectively, the dot product is computed via:

                    v . w = (vx, vy, vz) . (wx, wy, wz)
                          = vx*wx + vy*wy + vz*wz

                The is computed and returned.
        """

        # Dot products only make sense between vectors of the same type.
        if not isinstance(other, Vec3):
            raise TypeError(
                "\nError: nbh.Vec3\n"
                "    Trying to compute the dot product with an\n"
                "    object that is not of type nbh.Vec3."
            )

        # Compute the sum of the products and return.
        x_prod = self.x_val*other.x_val
        y_prod = self.y_val*other.y_val
        z_prod = self.z_val*other.z_val
        return x_prod + y_prod + z_prod

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

    # Computes the square of the length of the azimuthal part of the vector.
    def rho_sq(self):
        """
            Function:
                rho_sq
            Purpose:
                Computes the square of the length of the azimuthal path of self.
            Arguments:
                None.
            Outputs:
                rho_sq_self (float):
                    The square of the magnitude of azimuthal component.
            Method:
                Use the Pythagorean formula and compute. If the vector v is
                represented as v = (x, y, z), then:

                    rho^2 = ||(x, y)||^2 = x^2 + y^2

                This is computed and the sum is returned.
        """

        # Using Pythagoras, compute the squares of the computes.
        x_sq = self.x_val*self.x_val
        y_sq = self.y_val*self.y_val

        # Return the sum of the squares.
        return x_sq + y_sq

    # Computes the length of the cylindrical component of self.
    def rho(self):
        """
            Function:
                rho
            Purpose:
                Computes the Euclidean lenght of azimuthal part of self.
            Arguments:
                None.
            Outputs:
                rho_self (float):
                    The magnitude of the cylindical part of self.
            Method:
                Use the Pythagorean formula and compute. If the vector v is
                represented as v = (x, y, z), then:

                    rho = ||(x, y)|| = sqrt(x^2 + y^2)

                This is computed and the magnitude is returned.
        """
        return math.sqrt(self.rho_sq())

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

    def __str__(self):
        """
            Function:
                __str__
            Purpose:
                Represents the vector as a string.
        """
        return "(%f, %f, %f)" % (self.x_val, self.y_val, self.z_val)
