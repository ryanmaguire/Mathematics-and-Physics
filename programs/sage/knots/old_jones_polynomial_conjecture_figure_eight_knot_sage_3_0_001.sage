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
#       Compare Jones polynomial of the figure eight to other knots.           #
#                                                                              #
#       Corrected for use with snappy 3.0 and later.                           #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       February 14, 2021.                                             #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

# Generate the ring of Laurent polynomials in variable q over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Get the figure 8 knot's Jones polynomial.
figure_8_poly = snappy.Link("4_1").jones_polynomial(new_convention=False)

# These are all of the alternating Hoste-Thistlethwaite knots available:
print("\nProcessing Hoste-Thistlethwaite Alternating Table:")
for n in range(1, 368):
    knot_string = "K11a%d" % n
    knot = snappy.Link(knot_string)
    f = knot.jones_polynomial(new_convention=False)

    if (f == figure_8_poly):
        print("\tMatch: %s" % knot_string)

# And these are the non-alternating ones.
print("\nProcessing Hoste-Thistlethwaite Non-Alternating Table:")
for n in range(1, 186):
    knot_string = "K11n%d" % n
    knot = snappy.Link(knot_string)
    f = knot.jones_polynomial(new_convention=False)

    if (f == figure_8_poly):
        print("\tMatch: %s" % knot_string)

# SnapPy has the Rolfsen table for many knots, the highest being 11 crossings.
# Loop between 3 (Trefoil) and 11.
print("\nProcessing Rolfsen Table:")
for k in range(3, 12):

    # Reset m to one.
    m = 1

    # If the knot k_n does not exist (for example, "3_5"), and we try to
    # create it, Python will produce an error, crashing the program.
    # Perform this loop in a try-except block to catch any exception raised
    # by the SnapPy module.
    try:
        while(1):
            knot_string = ("%d_%d" % (k, m))
            knot = snappy.Link(knot_string)
            f = knot.jones_polynomial(new_convention=False)

            if (f == figure_8_poly):
                print("\tMatch: %s" % knot_string)

            # Increment m.
            m += 1

    # SnapPy raises an IOError on failure. Try to catch this to prevent error.
    except (IOError, ValueError):
        continue
