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

# Needed to convert string to list of lists.
import ast

# Largest number of twists we'll check for twist knots.
twist_start = 0
twist_end = 20
twist_count = 0

# Generate the ring of Laurent polynomials in variable q over Q (rationals).
R.<q> = LaurentPolynomialRing(QQ)

# Open the file containing the PD data.
fp = open("pd_code.txt")

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

# Loop over all knots in the file.
for pd in fp:
    pd = pd.replace("\n", "")
    x = ast.literal_eval(pd)
    L = snappy.Link(x)
    f = L.jones_polynomial(new_convention=False)

    for n in range(twist_count):
        if KnotList[n] == f or MirrorList[n] == f:
            print("Match: %d" % TwistInd[n],
                  "Crossing Number: %d" % len(x),
                  "PD Code %s" % pd)


