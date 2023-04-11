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
#       Provides default parameters for the black hole experiment.             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

# Vec3 class given here.
from . import vec3

# The z value for the source.
Z_SRC = 10.0

# The start and end parameters for the "source". The source is the
# square [START, END] x [START, END] at height Z_SRC.
START = -10.0
END = 10.0

# The height of the detector plane.
Z_DETECTOR = -10.0

# The square of the height of the detector, used frequently.
Z_DETECTOR_SQ = Z_DETECTOR*Z_DETECTOR

# The radius of the black hole.
BLACK_HOLE_RADIUS = 1.0

# The square of the black hole radius, also used frequently.
BLACK_HOLE_RADIUS_SQ = BLACK_HOLE_RADIUS*BLACK_HOLE_RADIUS

# Number of pixels in the x and y axes.
X_SIZE = 1024
Y_SIZE = 1024

# Factor used for converting from pixels to points in space.
PX_FACTOR = (END - START) / float(X_SIZE - 1)
PY_FACTOR = (END - START) / float(Y_SIZE - 1)

# Threshold for highlighting features (usually the origin).
HIGHLIGHT_THRESHOLD = 0.02

# For two black holes, the centers lie on the x axis.
BHX1 = -3.0
BHX2 = +3.0

# Converts a point on a PPM to a point in space.
def pixel_to_point(x_pixel, y_pixel):
    """
        Function:
            pixel_to_point
        Purpose:
            Converts a pixel on a PPM file to a point in space.
        Arguments:
            x_pixel (int):
                The x coordinate of the pixel.
            y_pixel (int):
                The y coordinate of the pixel.
        Outputs:
            vec (Vec3):
                The point in space corresponding to the given pixel.
    """

    # The inputs should be representable as floats. Try to convert.
    try:
        xpt = START + PX_FACTOR*float(x_pixel)
        ypt = START + PY_FACTOR*float(y_pixel)
        return vec3.Vec3(xpt, ypt, Z_SRC)

    except (TypeError, ValueError) as err:
        raise TypeError(
            "\nError: pixel_to_point\n"
            "    Inputs should be representable as floats."
        ) from err

# Stopper function for determining if a photon is still moving.
def stop(vec):
    """
        Function:
            stop
        Purpose:
            Determines if a photon is still in motion for one black hole.
        Arguments:
            vec (Vec3):
                The vector corresponding to the given photon.
        Outputs:
            stop (bool):
                Boolean for if the photon is still moving.
    """

    # The input must be a vector.
    if not isinstance(vec, vec3.Vec3):
        raise TypeError(
            "\nError: stop\n"
            "    Input must be a Vec3 instance."
        )

    # Case 1: The photon has reached the detector.
    if vec.z_val < Z_DETECTOR:
        return True

    # Case 2: The black hole swallowed the photon.
    black_hole_dist_sq = vec.norm_sq()

    # If this distance is less than the radius, the photon was absorbed.
    if black_hole_dist_sq < BLACK_HOLE_RADIUS_SQ:
        return True

    # Otherwise the photon is still moving. Don't stop.
    return False

# Stopper function for determining if a photon is still moving.
def stop2(vec):
    """
        Function:
            stop
        Purpose:
            Determines if a photon is still in motion for two black holes.
        Arguments:
            vec (Vec3):
                The vector corresponding to the given photon.
        Outputs:
            stop (bool):
                Boolean for if the photon is still moving.
    """

    # The input must be a vector.
    if not isinstance(vec, vec3.Vec3):
        raise TypeError(
            "\nError: stop2\n"
            "    Input must be a Vec3 instance."
        )

    # The black holes lie on the x axis. Compute the displacements to p.
    disp1 = vec3.Vec3(vec.x_val - BHX1, vec.y_val, vec.z_val)
    disp2 = vec3.Vec3(vec.x_val - BHX2, vec.y_val, vec.z_val)

    # Case 1: The photon has reached the detector.
    if vec.z_val < Z_DETECTOR:
        return True

    # Case 2: The first black hole swallowed the photon.
    black_hole_dist_sq = disp1.norm_sq()

    # If this distance is less than the radius, the photon was absorbed.
    if disp1.norm_sq() < BLACK_HOLE_RADIUS_SQ:
        return True

    # Case 3: The second black hole swallowed the photon.
    black_hole_dist_sq = disp2.norm_sq()

    # Same check as with the first black hole.
    if black_hole_dist_sq < BLACK_HOLE_RADIUS_SQ:
        return True

    # Otherwise, the photon is still moving. Don't stop.
    return False


def gravity(vec):
    """
        Function:
            gravity
        Purpose:
            Computes the acceleration given by the inverse square law from
            Newton's universal law of gravitation.
        Arguments:
            vec (Vec3):
                The position vector of the particle.
        Outputs:
            acc (Vec3):
            The acceleration of the particle.
    """

    # The input must be a vector.
    if not isinstance(vec, vec3.Vec3):
        raise TypeError(
            "\nError: stop2\n"
            "    Input must be a Vec3 instance."
        )

    # Given a vector p, Newton's universal law of gravitation says the
    # acceleration is proportional to p/||p||^3 = p_hat/||p||^2, where
    # p_hat is the unit vector for p. We can compute p/||p||^3 in terms
    # of the norm of p and the square of the norm of p. We have:
    factor = 1.0 / (vec.norm() * vec.norm_sq())

    # The acceleration is the minus of p times this factor. The reason it is
    # minus p is because gravity pulls inward, so the acceleration is inwards.
    return vec3.Vec3(-vec.x_val*factor, -vec.y_val*factor, -vec.z_val*factor)

# Force of gravity from two black holes.
def gravity2(vec):
    """
        Function:
            gravity2
        Purpose:
            Computes the acceleration given by the inverse square law from
            Newton's universal law of gravitation for two gravitating objects.
            This is done using the principle of superposition.
        Arguments:
            vec (Vec3):
                The position vector of the particle.
        Outputs:
            acc (Vec3):
            The acceleration of the particle.
    """

    # The input must be a vector.
    if not isinstance(vec, vec3.Vec3):
        raise TypeError(
            "\nError: stop2\n"
            "    Input must be a Vec3 instance."
        )

    # The force from one black hole is -R / ||R||^3, where R is the
    # relative position vector from the point p to the center of the
    # black hole. Compute this expression for both black holes.
    force1 = vec3.Vec3(BHX1 - vec.x_val, -vec.y_val, -vec.z_val)
    force2 = vec3.Vec3(BHX2 - vec.x_val, -vec.y_val, -vec.z_val)

    # We'll use the principle of superposition for the two black holes.
    factor1 = 1.0 / (force1.norm() * force1.norm_sq())
    factor2 = 1.0 / (force2.norm() * force2.norm_sq())

    # Scale the force vectors to get the actual force of gravity.
    force1 *= factor1
    force2 *= factor2

    # The net force is computed by the principle of superposition.
    # Add the two individual forces and return.
    return force1 + force2
