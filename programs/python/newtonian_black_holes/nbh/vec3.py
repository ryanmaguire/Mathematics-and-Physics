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

# pseudo-random number generator.
import random

# Basic Python class for dealing with vectors in R^3.
class Vec3:
    """
        Class:
            Vec3
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
                vec (Vec3):
                    The vector with Cartesian coordinates (x_val, y_val, z_val).
        """

        # We only set objects that can be converted to floats. Try this.
        try:
            self.x_val = float(x_val)
            self.y_val = float(y_val)
            self.z_val = float(z_val)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec3\n"
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
                other (Vec3):
                    The vector being added to self.
            Outputs:
                sum (Vec3):
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
                "\nError: Vec3\n"
                "    Trying to sum a Vec3 instance with\n"
                "    an object that is not of type Vec3."
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
                other (Vec3):
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
                "\nError: Vec3\n"
                "    Trying to sum a Vec3 instance with\n"
                "    an object that is not of type Vec3."
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
                other (Vec3):
                    The vector being subtracted from self.
            Outputs:
                diff (Vec3):
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
                "\nError: Vec3\n"
                "    Trying to compute the difference of a Vec3\n"
                "    with an object that is not of type Vec3."
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
                other (Vec3):
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
                "\nError: Vec3\n"
                "    Trying to compute the difference of a Vec3\n"
                "    with an object that is not of type Vec3."
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
                scaled_vector (Vec3):
                    The vector 'self' scaled by the input scalar.
            Method:
                Scalar multiplication is computed component-wise. If self is
                represented by the vector v = (x, y, z), then:

                    prod = a*v
                         = a*(x, y, z)
                         = (a*x, a*y, a*z)

                Where a is the input scalar.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            val = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec3\n"
                "    Trying to multiply a Vec3 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        x_prod = val*self.x_val
        y_prod = val*self.y_val
        z_prod = val*self.z_val
        return Vec3(x_prod, y_prod, z_prod)

    # * operator for scalar multiplication.
    def __rmul__(self, scalar):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Performs scalar multiplication of a vector with a float.
            Arguments:
                scalar (float):
                    A real number.
            Outputs:
                scaled_vector (Vec3):
                    The vector 'self' scaled by the input scalar.
            Method:
                Scalar multiplication is computed component-wise. If self is
                represented by the vector v = (x, y, z), then:

                    prod = a*v
                         = a*(x, y, z)
                         = (a*x, a*y, a*z)

                Where a is the input scalar.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            val = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec3\n"
                "    Trying to multiply a Vec3 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        x_prod = self.x_val*val
        y_prod = self.y_val*val
        z_prod = self.z_val*val
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
                "\nError: Vec3\n"
                "    Trying to multiply a Vec3 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        self.x_val *= val
        self.y_val *= val
        self.z_val *= val
        return self

    # Negation operator.
    def __neg__(self):
        """
            Operator:
                Negation (-):
            Purpose:
                Negates a vector.
            Arguments:
                None.
            Outputs:
                neg_self (Vec3):
                    The negation of self.
            Method:
                Negate each component and return.
        """

        # Negate all components and return.
        x_val = -self.x_val
        y_val = -self.y_val
        z_val = -self.z_val
        return Vec3(x_val, y_val, z_val)

    # Euclidean cross product.
    def cross(self, other):
        """
            Function:
                cross
            Purpose:
                Computes the Euclidean cross product of self with other.
            Arguments:
                other (Vec3):
                    A three dimensional vector.
            Outputs:
                cross_prod (Vec3):
                    The cross product of self with other.
            Method:
                The cross product is the unique vector orthogonal to the two
                inputs with orientation given by the right hand rule and whose
                magnitude is given by ||v|| ||w|| sin(theta) where theta is the
                angle between v and w.
        """

        # The cross product is only defined with other three-vectors.
        if not isinstance(other, Vec3):
            raise TypeError(
                "\nError: Vec3\n"
                "    Trying to compute the cross product with\n"
                "    an object that is not a Vec3 instance."
            )

        # Compute the individual components of the cross product and return.
        x_val = self.y_val*other.z_val - self.z_val*other.y_val
        y_val = self.z_val*other.x_val - self.x_val*other.z_val
        z_val = self.x_val*other.y_val - self.y_val*other.x_val
        return Vec3(x_val, y_val, z_val)

    # Euclidean cross product in-place.
    def cross_with(self, other):
        """
            Function:
                cross_with
            Purpose:
                Computes the cross product of self with other in-place.
            Arguments:
                other (Vec3):
                    A three dimensional vector.
            Outputs:
                None.
            Method:
                Compute the cross product and store the result in self.
        """

        # The cross product is only defined with other three-vectors.
        if not isinstance(other, Vec3):
            raise TypeError(
                "\nError: Vec3\n"
                "    Trying to compute the cross product with\n"
                "    an object that is not a Vec3 instance."
            )

        # Save the x and y components of self to avoid overwrites.
        x_val = self.x_val
        y_val = self.y_val

        # Compute the individual components of the cross product and return.
        self.x_val = y_val*other.z_val - self.z_val*other.y_val
        self.y_val = self.z_val*other.x_val - x_val*other.z_val
        self.z_val = x_val*other.y_val - y_val*other.x_val

    # Euclidean cross product represented as a wedge product.
    def __xor__(self, other):
        """
            Operator:
                Wedge (^)
            Purpose:
                Computes the Euclidean cross product of self with other.
            Arguments:
                other (Vec3):
                    A three dimensional vector.
            Outputs:
                cross_prod (Vec3):
                    The cross product of self with other.
            Method:
                Pass the argument to the cross method. Since the wedge product
                ^ is a generalization of the cross product, it is fitting to
                use this symbol.
        """
        return self.cross(other)

    # Euclidean cross product represented as a wedge product, in-place.
    def __ixor__(self, other):
        """
            Operator:
                Wedge (^=)
            Purpose:
                Computes the Euclidean cross product of self with other.
            Arguments:
                other (Vec3):
                    A three dimensional vector.
            Outputs:
                None.
            Method:
                Pass the argument to the cross_width method.
        """
        self.cross_with(other)
        return self

    # Euclidean dot product.
    def dot(self, other):
        """
            Function:
                dot
            Purpose:
                Computes the Euclidean dot product of self with other.
            Arguments:
                other (Vec3):
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
                "\nError: Vec3\n"
                "    Trying to compute the dot product with an\n"
                "    object that is not of type Vec3."
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

    # Creates a unit vector for non-zero vector.
    def normalize(self):
        """
            Function:
                normalize
            Purpose:
                Normalizes a vector so that it has unit magnitude.
            Arguments:
                None.
            Outputs:
                None.
            Method:
                Compute the norm of self and divide by this if it is non-zero.
        """

        # Compute the square of the norm of self.
        mag_sq = self.norm_sq()

        # If this is non-zero we may normalize.
        if mag_sq != 0:

            # The scale factor is the reciprocal of the square root of this.
            rcpr = math.sqrt(1.0 / mag_sq)

            # Scale each factor to normalize self.
            self.x_val *= rcpr
            self.y_val *= rcpr
            self.z_val *= rcpr

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

    # String representation of a vector.
    def __str__(self):
        """
            Function:
                __str__
            Purpose:
                Represents the vector as a string.
            Arguments:
                None.
            Outputs:
                self_str (str):
                    The vector self represented as a string.
        """
        return "(%f, %f, %f)" % (self.x_val, self.y_val, self.z_val)

    # How a vector is represented if called at the terminal.
    def __repr__(self):
        """
            Function:
                __repr__
            Purpose:
                Represents the vector as a string.
            Arguments:
                None.
            Outputs:
                self_str (str):
                    The vector self represented as a string.
        """
        return self.__str__()

    # Returns a component of a vector in list style.
    def __getitem__(self, key):
        """
            Function:
                __getitem__
            Purpose:
                Treats a Vec3 class as a list and returns the corresponding
                entry. 0 -> x_val, 1 -> y_val, 2 -> z_val.
            Arguments:
                key (int):
                    The key requested. (x, y, z) corresponds to (0, 1, 2).
            Outputs:
                val (float):
                    The value of the given key.
        """

        # The key must be an integer.
        if not isinstance(key, int):
            raise TypeError(
                "\nError Vec3:\n"
                "    Key is not an integer."
            )

        # Valid keys are 0, 1, and 2.
        if key < 0 or key > 2:
            raise IndexError(
                "\nError Vec3:\n"
                "    key should be 0, 1, or 2."
            )

        # Dictionary of the keys for the vector.
        keys = {
            0 : self.x_val,
            1 : self.y_val,
            2 : self.z_val
        }

        # Return the value of the requested key.
        return keys[key]

    # Sets the value of a vector in list style.
    def __setitem__(self, key, value):
        """
            Function:
                __setitem__
            Purpose:
                Treats a Vec3 class as a list and alters the corresponding
                entry. 0 -> x_val, 1 -> y_val, 2 -> z_val.
            Arguments:
                key (int):
                    The key to change. (x, y, z) corresponds to (0, 1, 2).
                value (float):
                    The value the key will be set to.
            Outputs:
                None.
        """

        # The key must be an integer.
        if not isinstance(key, int):
            raise TypeError(
                "\nError Vec3:\n"
                "    Key is not an integer."
            )

        # The key should 0, 1, or 2.
        if key < 0 or key > 2:
            raise IndexError(
                "\nError Vec3:\n"
                "    key should be 0, 1, or 2."
            )

        # The value must be able to be converted to a float.
        try:
            val = float(value)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec3\n"
                "    Can't convert value to float."
            ) from err

        # Set the corresponding key to the new value.
        if key == 0:
            self.x_val = val
        elif key == 1:
            self.y_val = val
        else:
            self.z_val = val

# Returns a random vector in R^3.
def randvec():
    """
        Function:
            random
        Purpose:
            Returns a random vector in R^3.
        Arguments:
            None.
        Outputs:
            rand_vec (Vec3):
                A vector with x, y, and z set to random values.
        Method:
            Call random.random() three times and return.
    """

    # Get three random numbers and return.
    x_val = random.random()
    y_val = random.random()
    z_val = random.random()
    return Vec3(x_val, y_val, z_val)

# Function for normalizing a vector without invoking the normalize method.
def normalize(vec):
    """
        Function:
            normalize
        Purpose:
            Normalizes a vector so that it has unit magnitude.
        Arguments:
            vec (Vec3):
                The vector to be normalized.
        Outputs:
            vec_hat (Vec3):
                The unit normal vector in the direction of the input.
        Method:
            Compute the norm of vec and divide by this if it is non-zero.
    """

    # Compute the square of the norm of vec.
    mag_sq = vec.norm_sq()

    # If this is non-zero we may normalize.
    if mag_sq != 0:

        # The scale factor is the reciprocal of the square root of this.
        rcpr = math.sqrt(1.0 / mag_sq)

        # Scale each factor to normalize self.
        x_val = rcpr*vec.x_val
        y_val = rcpr*vec.y_val
        z_val = rcpr*vec.z_val

    # Otherwise return the zero vector.
    else:
        x_val = 0.0
        y_val = 0.0
        z_val = 0.0

    return Vec3(x_val, y_val, z_val)
