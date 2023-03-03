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
#       Test a conjecture about Khovanov homology and the Jones polynomial.    #
#       The idea is that Khovanov homology can distinguish a Torus knot from   #
#       a non-torus knot. First, see if this is true of the Jones polynomial.  #
#       If we find a match, compute (currently by hand or lookup table) the    #
#       Khovanov homologies of the matching pair to see if they're the same.   #
#                                                                              #
#       DO NOT USE THIS. The second rendition of this code is significantly    #
#       faster: old_jones_polynomial_conjecture_snappy_2_9_002.sage.           #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       June 12, 2021.                                                 #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

# Numpy is needed for it's GCD function.
import numpy

# A torus knot is of the form T(p,q) where p and q are coprime. We'll loop over
# the lattice [Torus_Start, Torus_End]^2 and check these Jones' polynomials.
#   Note: If you don't start at a negative value, you may miss mirrors.
Torus_Start = -11
Torus_End = 11

# Threshold value for n*m for the Torus knot T(n,m). If n*m is large, the
# computation for the Jones' polynomial will take a very very long time.
threshold = 25

# The SnapPy module has 367 altnerating Hoste-Thistlethwaite knots
# and 185 non-alternating Hoste-Thistlethwaite knots. We can loop over these
# with strings.

# The syntax for manipulating strings in Sage comes from Python, which is
# borrowed from the syntax used in C. We use %d to indicate a placeholder for
# and integer, and then pass an integer to that placeholder via % n, where n is
# an actual integer. We surround the string with quotation marks.

# These are all of the alternating Hoste-Thistlethwaite knots available:
#       The Rolfsen table contains these, so skipping.
# Ka = [("K11a%d" % n) for n in range(1, 368)]

# And these are the non-alternating ones.
#       The Rolfsen table also contains these. Skipping.
# Kn = [("K11n%d" % n) for n in range(1, 186)]

# As a side note, the range function (which is from Python) has syntax
# range(m,n) and creates an iterator between m and n-1. That is, n is NOT
# included. Hence the need to iterate between 1 and 368 for the alternating and
# 1 and 186 for the non-alternating.

# Empty list we'll store knots in.
ManifoldList = []

# Counters for seeing how many of the knots work with the SnapPy
# is_isometric_to method.
#       None of them worked. Commenting out this code.
# counter_gcd = 0
# counter_success = 0

# SnapPy has the Rolfsen table for many knots, the highest being 11 crossings.
# Loop between 3 (Trefoil) and 11.
for k in range(3, 12):

    # Starting value for n.
    n = 1

    # If the knot k_n does not exist (for example, "3_5"), and we try to
    # create it, Python will produce an error, crashing the program.
    # Perform this loop in a try-except block to catch any exception raised
    # by the SnapPy module.
    try:
        while(1):
            knot_string = ("%d_%d" % (k, n))

            # Create a copy of the manifold class and the link class
            # corresponding to the current knot.
            m = snappy.Manifold(knot_string)
            l = snappy.Link(knot_string)

            # Shift the Jones polynomial so that all of the powers are
            # non-negative. That is, make the Jones polynomial an actual
            # polynomial, and not a Laurent polynomial with negative
            # exponents.
            knot_poly = l.jones_polynomial()
            knot_poly = knot_poly.shift(-min(knot_poly.exponents()))

            # Make the constant coefficient of our polynomials positive.
            if (knot_poly[0] < 0.0):
                knot_poly = -knot_poly

            # Append the manifold and link to our list and increment n.
            ManifoldList.append([knot_string, m, l, knot_poly])
            n += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except IOError:
        continue

# We need to loop over all Torus knots within a certain range. A torus knot
# can be specified by an ordered pair (n, m) of COPRIME integers.
for n in range(Torus_Start, Torus_End):

    # If n is -1, 0, or 1, skip. There are no Torus knots with -1, 0, or 1 as
    # one of its entries, with the exception of the trivial knot, and we can
    # skip this one.
    if ((n == -1) or (n == 1) or (n == 0)):
        continue

    # The knot T(n,m) and T(m,n) are the same. The link T(m,m) is a collection
    # of m trivial knots. To avoid these we may start the second loop at
    # m = n+1.
    for m in range(abs(n)+1, Torus_End):

        # Similar to the outer loop, if m is -1, 0, or 1, skip.
        if ((m == -1) or (m == 1) or (m == 0)):
            continue

        # If |m*n| is large, the computation can take a very very long time.
        if (abs(n*m) > threshold):
            break

        # We only have a new torus knot if GCD(n,m) = 1. Check this.
        if (numpy.gcd(n, m) == 1):

            # Print an update.
            #   Not needed, there aren't many knots to check.
            #   print("Current: (%d, %d)  Total: %d" % (n, m, Torus_End))

            # Increment our counter that checks if is_isometric_to works.
            #       This doesn't work. Commenting out this line.
            # counter_gcd += 1

            # Compute the Link class corresponding to our torus knot.
            knot_string = "T(%d, %d)" % (n, m)
            torus_knot = snappy.Link(knot_string)

            # Compute the Jones polynomial of the torus knot.
            torus_poly = torus_knot.jones_polynomial()

            # Shift the Jones polynomial so that all of the powers are
            # non-negative. That is, make the Jones polynomial an actual
            # polynomial, and not a Laurent polynomial with negative
            # exponents.
            torus_poly = torus_poly.shift(-min(torus_poly.exponents()))

            # Make the constant coefficient of our polynomials positive.
            if (torus_poly[0] < 0.0):
                torus_poly = -torus_poly

            # Loop over all of the knots in our list and check if they have the
            # same Jones Polynomial as the torus knot T(n,m).
            for k in ManifoldList:

                # Skip this for now, it does not work.
                # The is_isometric_to method failed for EVERY torus knot. The
                # documentation indicates this may happen for
                # "closed manifolds". We need to have this statement in a
                # try-except block since SnapPy produces a RunTime error if
                # SnapPea (the C code) is unable to determine if two manifolds
                # are isometric.
                #   try:
                #       if (k[1].is_isometric_to(torus_knot.exterior())):
                #           continue
                #   except RuntimeError as err:
                #       print(err)

                # If we get here (and the is_isometric_to block is NOT
                # commented out), then is_isometric_to succeeded and we should
                # increment our counter. If the is_isometric_to block is
                # commented out, we can just ignore this.
                # counter_success += 1

                # Compare the two polynomials.
                if (torus_poly == k[3]):
                    print("\tMATCH: %s %s" % (k[0], knot_string))
