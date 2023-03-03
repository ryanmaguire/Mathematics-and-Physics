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
#       Compare Jones polynomial of twist knots with other knots.              #
#                                                                              #
#       This code works with SnapPy versions greater than 3.0. Snappy 3.0 and  #
#       higher changed how the Jones polynomial function works.                #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 12, 2021.                                                     #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

# Twist knots can be indexed by a single number (the number of twists). These
# variables are for the range of twist knots we'll loop over.
twist_start = 0
twist_end = 20
twist_count = 0

# Generate the ring of Laurent polynomials in variable q over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Create two empty lists for storing the knots and their Jones polynomials.
KnotList = []
MirrorList = []
TwistInd = []

# Loop over and compute the Jones Polynomial of twist knots.
for m in range(twist_start, twist_end):

    if m % 2 == 0:
        f = (q**3 + q - q**(3-m) + q**(-m))/(1+q)
        g = (q**(-3) + q**(-1) - q**(m-3) + q**m)/(1+q**(-1))
    else:
        f = (1 + q**(-2) + q**(-m) - q**(-m-3))/(1+q)
        g = (1 + q**2 + q**(m) - q**(m+3))/(1+q**(-1))

    # Add the two knots to our lists.
    KnotList.append(f)
    MirrorList.append(g)
    TwistInd.append(m)
    twist_count += 1

# These are all of the alternating Hoste-Thistlethwaite knots available:
print("\nProcessing Hoste-Thistlethwaite Alternating Table:")
for n in range(1, 368):
    knot_string = "K11a%d" % n
    knot = snappy.Link(knot_string)
    f = knot.jones_polynomial(new_convention=False)

    for n in range(twist_count):
        if (f == KnotList[n]):
            print("\t%s matches a twist knot: %d"
                  % (knot_string, TwistInd[n]))
        elif (f == MirrorList[n]):
            print("\t%s matches a twist knot mirror: %d"
                  % (knot_string, TwistInd[n]))

# And these are the non-alternating ones.
print("\nProcessing Hoste-Thistlethwaite Non-Alternating Table:")
for n in range(1, 186):
    knot_string = "K11n%d" % n
    knot = snappy.Link(knot_string)
    f = knot.jones_polynomial(new_convention=False)

    for n in range(twist_count):
        if (f == KnotList[n]):
            print("\t%s matches a twist knot: %d"
                  % (knot_string, TwistInd[n]))
        elif (f == MirrorList[n]):
            print("\t%s matches a twist knot mirror: %d"
                  % (knot_string, TwistInd[n]))

# SnapPy has the Rolfsen table for many knots, the highest being 11 crossings.
# Loop between 3 (Trefoil) and 11.
print("\nProcessing Rolfsen Table:")
for k in range(3, 12):

    # Reset n to one.
    n = 1

    # If the knot k_n does not exist (for example, "3_5"), and we try to
    # create it, Python will produce an error, crashing the program.
    # Perform this loop in a try-except block to catch any exception raised
    # by the SnapPy module.
    try:
        while(1):
            knot_string = ("%d_%d" % (k, n))
            knot = snappy.Link(knot_string)
            f = knot.jones_polynomial(new_convention=False)

            for m in range(twist_count):
                if (f == KnotList[m]):
                    print("\t%s matches a twist knot: %s" %
                          (knot_string, TwistInd[m]))
                elif (f == MirrorList[m]):

                    print("\t%s matches a twist knot mirror: %s"
                          % (knot_string, TwistInd[m]))

            # Increment n.
            n += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except (IOError, ValueError):
        continue
