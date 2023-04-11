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
#       Provides a class for working with vectors in R^6.                      #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

# sqrt function provided here.
import math

# 3D vectors. A 6D vector consists of two 3D vectors.
from . import vec3

# Class for working in phase-space.
class Vec6:
    """
        Class:
            Vec6
        Purpose:
            Six dimensional Euclidean vector class with vector arithmetic and
            basic geometrical properties included.
    """

    # Create a 6D vector from two 3D vectors.
    def __init__(self, pos, vel):
        """
            Function:
                __init__
            Purpose:
                Creates a Vec6 instance from two Vec3 instances.
            Arguments:
                pos (Vec3):
                    The position vector.
                vel (Vec3):
                    The velocity vector.
            Outputs:
                vec (Vec6):
                    The 6D vector (pos, vel).
        """

        # Both inputs should be 3D vectors.
        if not isinstance(pos, vec3.Vec3) or not isinstance(vel, vec3.Vec3):
            raise TypeError(
                "\nError: Vec6\n"
                "    One of the inputs is not a Vec3 instance."
            )

        # Otherwise set the variables for the class.
        self.pos = pos
        self.vel = vel

    # + operator for vector addition.
    def __add__(self, other):
        """
            Operator:
                Addition (+).
            Purpose:
                Performs vector addition in R^6.
            Arguments:
                other (Vec6):
                    The vector being added to self.
            Outputs:
                sum (Vec6):
                    The vector sum of self and other.
            Method:
                Add the vectors component-wise. If self and other are
                represented as u0 = (p0, v0) and u1 = (p1, v1),
                respectively, the sum is then:

                    u0 + u1 = (p0, v0) + (p1, v1)
                            = (p0 + p1, v0 + v1)

                That is, vector addition is done component-wise.
        """

        # It is only valid to add another Vec6 class to the vector.
        if not isinstance(other, Vec6):
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to sum a Vec6 instance with\n"
                "    an object that is not of type Vec6."
            )

        # Vector addition is performed component-wise.
        sum_pos = self.pos + other.pos
        sum_vel = self.vel + other.vel
        return Vec6(sum_pos, sum_vel)

    # += operator for vector addition.
    def __iadd__(self, other):
        """
            Operator:
                Addition (+=).
            Purpose:
                Performs vector addition in-place.
            Arguments:
                other (Vec6):
                    The vector being added to self.
            Outputs:
                self
            Method:
                Perform vector addition component-wise and store
                the result in self.
        """

        # It is only valid to add another Vec6 class to the vector.
        if not isinstance(other, Vec6):
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to sum a Vec6 instance with\n"
                "    an object that is not of type Vec6."
            )

        # Vector addition is performed component-wise.
        self.pos += other.pos
        self.vel += other.vel
        return self

    # - operator for vector subtraction.
    def __sub__(self, other):
        """
            Operator:
                Subtraction (-).
            Purpose:
                Performs vector subtraction in R^6.
            Arguments:
                other (Vec6):
                    The vector being subtracted from self.
            Outputs:
                diff (Vec6):
                    The vector difference of self and other.
            Method:
                Subtract the vectors component-wise. If self and other are
                represented as u0 = (p0, v0) and u1 = (p1, v1),
                respectively, the difference is then:

                    u0 - u1 = (p0, v0) - (p1, v1)
                            = (p0 - p1, v0 - v1)

                That is, vector subtraction is done component-wise.
        """

        # It is only valid to subtract another Vec6 class from the vector.
        if not isinstance(other, Vec6):
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to compute the difference of a Vec6\n"
                "    with an object that is not of type Vec6."
            )

        # Vector subtraction is performed component-wise.
        diff_pos = self.pos - other.pos
        diff_vel = self.vel - other.vel
        return Vec6(diff_pos, diff_vel)

    # +- operator for vector subtraction.
    def __isub__(self, other):
        """
            Operator:
                Subtraction (-=).
            Purpose:
                Performs vector subtraction in-place.
            Arguments:
                other (Vec6):
                    The vector being subtracted from self.
            Outputs:
                self
            Method:
                Perform vector subtraction component-wise and store
                the result in self.
        """

        # It is only valid to add another Vec6 class to the vector.
        if not isinstance(other, Vec6):
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to compute the difference of a Vec6\n"
                "    with an object that is not of type Vec6."
            )

        # Vector subtraction is performed component-wise.
        self.pos -= other.pos
        self.vel -= other.vel
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
                scaled_vector (Vec6):
                    The vector 'self' scaled by the input scalar.
            Method:
                Scalar multiplication is computed component-wise. If self is
                represented by the vector u = (p, v), then:

                    prod = a*u
                         = a*(p, v)
                         = (a*p, a*v)

                Where a is the input scalar.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            factor = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to multiply a Vec6 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        pos_prod = factor*self.pos
        vel_prod = factor*self.vel
        return Vec6(pos_prod, vel_prod)

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
                scaled_vector (Vec6):
                    The vector 'self' scaled by the input scalar.
            Method:
                Scalar multiplication is computed component-wise. If self is
                represented by the vector u = (p, v), then:

                    prod = a*u
                         = a*(p, v)
                         = (a*p, a*v)

                Where a is the input scalar.
        """

        # The input needs to be representable as a float. Try to convert.
        try:
            factor = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to multiply a Vec6 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        pos_prod = self.pos*factor
        vel_prod = self.vel*factor
        return Vec6(pos_prod, vel_prod)

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
            factor = float(scalar)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to multiply a Vec6 instance with an\n"
                "    object that can not be converted to float."
            ) from err

        # Compute scalar multiplication component-wise.
        self.pos *= factor
        self.vel *= factor
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
                neg_self (Vec6):
                    The negation of self.
            Method:
                Negate each component and return.
        """

        # Negate all components and return.
        pos = -self.pos
        vel = -self.vel
        return Vec6(pos, vel)

    # Euclidean dot product.
    def dot(self, other):
        """
            Function:
                dot
            Purpose:
                Computes the Euclidean dot product of self with other.
            Arguments:
                other (Vec6):
                    Another vector.
            Outputs:
                dot_prod (float):
                    The dot product of self with other.
            Method:
                Use the standard dot product formula. If self and other are
                represented by u0 = (p0, v0) and u1 = (p1, v1),
                respectively, the dot product is computed via:

                    u0 . u1 = (p0, v0) . (p1, v1)
                            = (p0 . p1) + (v0 . v1)

                The is computed and returned.
        """

        # Dot products only make sense between vectors of the same type.
        if not isinstance(other, Vec6):
            raise TypeError(
                "\nError: Vec6\n"
                "    Trying to compute the dot product with an\n"
                "    object that is not of type Vec6."
            )

        # Compute the sum of the products and return.
        return self.pos.dot(other.pos) + self.vel.dot(other.vel)

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
                Use the Pythagorean formula and compute. If the vector u is
                represented as u = (p, v), then:

                    ||u||^2 = ||p||^2 + ||v||^2

                This is computed and the sum is returned.
        """

        # Using Pythagoras, compute the squares of the computes.
        return self.pos.norm_sq() + self.vel.norm_sq()

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
                represented as u = (p, v), then:

                    ||v|| = sqrt(||p||^2 + ||v||^2)

                This is computed and the magnitude is returned.
        """
        return math.sqrt(self.pos.norm_sq() + self.vel.norm_sq())

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
            self.pos *= rcpr
            self.vel *= rcpr

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
        pstr = "(%f, %f, %f)" % (self.pos.x_val, self.pos.y_val, self.pos.z_val)
        vstr = "(%f, %f, %f)" % (self.vel.x_val, self.vel.y_val, self.vel.z_val)
        return "(%s, %s)" % (pstr, vstr)

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
                Treats a Vec6 class as a list and returns the corresponding
                entry.
            Arguments:
                key (int):
                    The key requested. (x, y, z) corresponds to (0, 1, 2),
                    (vx, vy, vy) corresponds to (3, 4, 5).
            Outputs:
                val (float):
                    The value of the given key.
        """

        # The key must be an integer.
        if not isinstance(key, int):
            raise TypeError(
                "\nError Vec6:\n"
                "    Key is not an integer."
            )

        # Valid keys are between 0 and 5.
        if key < 0 or key > 5:
            raise IndexError(
                "\nError Vec6:\n"
                "    key should be between 0 and 5."
            )

        # For keys between 0 and 2 we return the position vectors component.
        if key < 3:
            return self.pos[key]

        # Otherwise shift by 3 and return the velocity vectors key.
        return self.vel[key - 3]

    # Sets the value of a vector in list style.
    def __setitem__(self, key, value):
        """
            Function:
                __setitem__
            Purpose:
                Treats a Vec6 class as a list and alters the corresponding
                entry.
            Arguments:
                key (int):
                    The key to change. (x, y, z) corresponds to (0, 1, 2),
                    (vx, vy, vz) corresponds to (3, 4, 5).
                value (float):
                    The value the key will be set to.
            Outputs:
                None.
        """

        # The key must be an integer.
        if not isinstance(key, int):
            raise TypeError(
                "\nError Vec6:\n"
                "    Key is not an integer."
            )

        # The key should 0, 1, or 2.
        if key < 0 or key > 6:
            raise IndexError(
                "\nError Vec6:\n"
                "    key should be between 0 and 5."
            )

        # The input must be representable as a float.
        try:
            key_val = float(value)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Vec6\n"
                "    Value must be representable as a float."
            ) from err

        # For keys 0, 1, and 2 set the position vectors component.
        if key < 3:
            self.pos[key] = key_val

        # Otherwise set the velocity vectors component.
        else:
            self.vel[key] = key_val

# Returns a random vector in R^3.
def randvec():
    """
        Function:
            random
        Purpose:
            Returns a random vector in R^6.
        Arguments:
            None.
        Outputs:
            rand_vec (Vec6):
                A vector with pos and vel set to random three-vectors.
        Method:
            Call vec3.randvec twice and return.
    """

    # Get two random vectors and return.
    pos = vec3.randvec()
    vel = vec3.randvec()
    return Vec6(pos, vel)

# Function for normalizing a vector without invoking the normalize method.
def normalize(vec):
    """
        Function:
            normalize
        Purpose:
            Normalizes a vector so that it has unit magnitude.
        Arguments:
            vec (Vec6):
                The vector to be normalized.
        Outputs:
            vec_hat (Vec6):
                The unit normal vector in the direction of the input.
        Method:
            Compute the norm of vec and divide by this if it is non-zero.
    """

    # Compute the square of the norm of self.
    mag_sq = vec.norm_sq()

    # If this is non-zero we may normalize.
    if mag_sq != 0:

        # The scale factor is the reciprocal of the square root of this.
        rcpr = math.sqrt(1.0 / mag_sq)

        # Scale each factor to normalize self.
        pos = vec.pos*rcpr
        vel = vec.vel*rcpr

    # Otherwise return the zero vector.
    else:
        pos = vec3.Vec3(0.0, 0.0, 0.0)
        vel = vec3.Vec3(0.0, 0.0, 0.0)

    return Vec6(pos, vel)
