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
#       Provides routines for performing Euler's method for ODE's.             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       April 11, 2023.                                                #
################################################################################
"""

# Vec6 found here.
from . import vec6

# Time step used in Euler's method. The user may change this.
TIME_INCREMENT = 0.01

# The max number of iterations in Euler's method.
MAX_ITERS = 65535

# Uses Euler's method to compute the path of a particle.
def path(vec, acc, stop):
    """
        Function:
            path
        Purpose:
            Given a vector-valued acceleration a = acc(r), a starting
            position p, an initial velocity v, and a stopping condition stop,
            perform Euler's method method to numerically solve the system of
            motion. The initial conditions (p, v) are given by vec.
        Arguments:
            vec (Vec6):
                A 6D vector representing the initial position and velocity.
            acc (function):
                A function that describes the equation of motion.
            stop (function):
                A function that determines when to stop Euler's method.
        Outputs:
            None.
        Method:
            Apply Euler's method. Given initial conditions (p0, v0) and time
            increment dt, we iteratively compute:

                v_{n+1} = dt*acc(p_{n+1}) + v_{n}
                p_{n+1} = dt*v_{n+1} + p_{n}

            Do this until the stopper function tells you to stop, or until
            you've done to many iterations.
    """

    # The first variable must be a 6D vector.
    if not isinstance(vec, vec6.Vec6):
        raise TypeError(
            "\nError: path\n"
            "    First argument should be a 6D vector representing\n"
            "    the initial position and velocity of the particle."
        )

    # Use of this function with nbh makes a very naive assumption. Newton's
    # Second Law states that F = ma, where a is the acceleration. For
    # gravity we obtain the vector-valued differential equation:
    #     -GMm p / ||p||^3 = m d^2/dt^2 p
    # Where G is the universal gravitational constant, and M is the mass of
    # the black hole (m being the mass of the object under consideration).
    # We can take G*M to be 1 for simplicity, since we never specified the
    # units we're in. Now, if m is any non-zero value we can cancel to get:
    #     p / ||p||^3 = d^2/dt^2 p
    # Solving this vector-valued differential equation results in the
    # trajectory of the object. The only problem is it is generally
    # believed that photons, which are particles of light, have zero mass.
    # So let's pretend they have a mass that is so stupidly small it would
    # be impossible to measure, but not zero. Given this we could apply
    # Newtonian mechanics to get a rough sketch of a black hole.

    # In the main use of this function the black hole is of radius r at
    # the origin and our detector is the plane z = z0. Our source of light
    # is some plane z = z1. So the light is coming down and heading towards
    # our detector. We'll increment time using a small value dt, and we'll
    # keep incrementing until the light either hits the detector or is
    # absorbed by the black hole. dt is given by the TIME_INCREMENT value,
    # and the stopping condition (hitting the detector, or being absorbed
    # by a black hole) is determined by the "stop" function.
    iters = 0

    # Keep performing Euler's method until we hit the detector or perform
    # too many iterations.
    while not stop(vec.pos) and iters < MAX_ITERS:

        # We numerically solve d^2/dt^2 p = F(p) in two steps. First we
        # compute the velocity dp/dt, meaning we need to solve dv/dt = F(p).
        # We solve numerically with Euler's method. Then we use this v to
        # compute p via dp/dt = v, again solving numerically with Euler's
        # method. So long as dt is small, the error should be small as well.
        accel = acc(vec.pos)

        vec.pos += TIME_INCREMENT*vec.vel
        vec.vel += TIME_INCREMENT*accel

        # It is possible that a photon was captured into orbit, but not
        # absorbed into the black hole. To avoid an infinite loop
        # abort the computation once n gets too large.
        iters += 1
