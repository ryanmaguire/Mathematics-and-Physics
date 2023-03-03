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
#       Compare Alexander polynomial of torus knots. KFH removed.              #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       March 3, 2023.                                                 #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

# Numpy is needed for it's GCD function.
import numpy

# Needed to convert string to list of lists.
import ast

# Largest number of twists we'll check for torus knots.
torus_start = 2
torus_end = 50
torus_count = 0

# Set up ring of Laurent polynomials.
R.<q> = LaurentPolynomialRing(QQ)

# Three empty lists we'll be adding knots and polynomials to later.
KnotList = []
PolyList = []
TorusStringList = []

# Open the file containing the PD data.
fp = open("pd_code.txt")

# Loop over all torus knots and compute their Alexander polynomial.
for m in range(torus_start, torus_end):

    # Skip these values, they correspond to the trivial knot.
    if (m == 0) or (m == 1) or (m == -1):
        continue

    # T(m,n) and T(n,m) can be treated as the same, so start with n > m.
    for n in range(m + 1, torus_end):

        # Same skip as before.
        if (n == 0) or (n == 1) or (n == -1):
            continue

        # If GCD(m, n) != 1 we have a link, not a knot. Skip this.
        if (numpy.gcd(m, n) != 1):
            continue

        # If n*m is big it will have a larger degree than any of the knots in
        # the text file. Skip these.
        if (m*n > 100):
            continue

        # Compute the Alexander polynomial for the torus knot T(m, n).
        L = snappy.Link("T(%d,%d)" % (m, n))
        f = L.alexander_polynomial()

        KnotList.append(L)
        PolyList.append(f)
        TorusStringList.append("(%d, %d)" % (m, n))
        torus_count += 1

# Loop over all PD codes in the text file.
for pd in fp:

    # The string in the text file is of the form [[...],[...],...,[...]]. That
    # is, a list of lists. Use the ast module to convert the string to a list.
    x = ast.literal_eval(pd)

    # Compute the Alexander polynomial for the knot with the given PD code.
    L = snappy.Link(x)
    f = L.alexander_polynomial()

    # See if this matches any of the torus knots.
    for n in range(torus_count):
        if PolyList[n] == f:
            print("Match: %s" % TorusStringList[n],
                  "Crossing Number: %d" % len(x),
                  "PD Code %s" % pd, end = "")
