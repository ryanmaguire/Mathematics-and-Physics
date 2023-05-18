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
#       Script for comparing the Jones polynomial of torus knots to others.    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       March 3, 2023.                                                 #
################################################################################
"""

# pylint complains about regina because of dynamically loaded object members.
# The following comment disables these warnings.
# pylint: disable=E1101

# For parsing input arguments.
import sys

# Knot and link routines.
import regina

# GCD routine needed.
import numpy

# Handles CSV files.
import pandas

# The user should supply the path to the CSV file with DT codes.
FILE_NAME = sys.argv[1]

# Gather the data from the CSV file.
CSV_DATA = pandas.read_csv(FILE_NAME)

# During the for loop we'll print out status updates every now and again.
NUMBER_OF_KNOTS = len(CSV_DATA.dt_code)
SKIP = 100000

# The lowest value allowed for p and q while looping through T(p, q) knots.
TORUS_START = 2

# The largest value allowed for p and q.
TORUS_END = 50

# The threshold for the pairs (p, q). Once p * q is larger than this threshold
# we'll skip the corresponding torus knots.
TORUS_THRESHOLD = 100

# The number of torus knots being looped over. Computed incrementally.
TORUS_COUNT = 0

# List of Jones polynomials of torus knots and the mirrors of torus knots.
TORUS_KNOT_JONES_LIST = []
TORUS_KNOT_MIRROR_JONES_LIST = []

# List of the string representation of torus knots, which is "T(p, q)".
TORUS_STRING_LIST = []

# Constant Laurent polynomials used frequently.
ONE = regina.Laurent(0)

# The denominator of a torus knot is 1 + q^4. The denominator of a torus knot
# mirror is 1 + q^-4. To avoid polynomial division we'll multiply by these
# factors.
ONE_MINUS_POW_NEG_Q = ONE - regina.Laurent(-4)
ONE_MINUS_POW_POS_Q = ONE - regina.Laurent(4)

# Loop over the row index of torus knots. The "p" in T(p, q).
for ROW_IND in range(TORUS_START, TORUS_END):

    # If the index is 0 or +/- 1 we have the unknot. Skip this.
    if ROW_IND in (0, 1, -1):
        continue

    # Loop over the columns. The "q" in T(p, q).
    for COL_IND in range(ROW_IND + 1, TORUS_END):

        # Same skip as before, ignore the unknot.
        if COL_IND in (0, 1, -1):
            continue

        # T(p, q) is a knot for coprime p and q. Skip if this is not coprime.
        if numpy.gcd(ROW_IND, COL_IND) != 1:
            continue

        # If max(p, q) * (min(p, q) - 1) is large no knot with few crossings
        # will have the same Jones polynomial as T(p, q) since the degree is
        # too small. We can skip these torus knots.
        if COL_IND * (ROW_IND - 1) > TORUS_THRESHOLD:
            continue

        a = regina.Laurent((ROW_IND - 1)*(COL_IND - 1))
        b = regina.Laurent(2*ROW_IND + 2)
        c = regina.Laurent(2*COL_IND + 2)
        d = regina.Laurent(2*(ROW_IND + COL_IND))

        f = a*(ONE - b - c + d)

        a = regina.Laurent((1 - ROW_IND)*(COL_IND - 1))
        b = regina.Laurent(-2*ROW_IND - 2)
        c = regina.Laurent(-2*COL_IND - 2)
        d = regina.Laurent(-2*(ROW_IND + COL_IND))

        g = a*(ONE - b - c + d)

        TORUS_KNOT_JONES_LIST.append(f)
        TORUS_KNOT_MIRROR_JONES_LIST.append(g)
        TORUS_STRING_LIST.append("(%d, %d)" % (ROW_IND, COL_IND))
        TORUS_COUNT += 1

for CURRENT_KNOT in range(NUMBER_OF_KNOTS):

    if CURRENT_KNOT % SKIP == 0:
        print("\t", CURRENT_KNOT, NUMBER_OF_KNOTS)

    DT_CODE = CSV_DATA.dt_code[CURRENT_KNOT].replace("\n", "")

    KNOT = regina.Link.fromDT(DT_CODE)

    JONES_POLY = KNOT.jones()
    SCALED_JONES = JONES_POLY*ONE_MINUS_POW_POS_Q
    SCALED_MIRROR = JONES_POLY*ONE_MINUS_POW_NEG_Q

    for n in range(TORUS_COUNT):
        if TORUS_KNOT_JONES_LIST[n] == SCALED_JONES:
            print("Match: %s" % TORUS_STRING_LIST[n],
                  "- Crossing Number: %d" % (len(DT_CODE)),
                  "- DT Code: %s" % DT_CODE)

        elif TORUS_KNOT_MIRROR_JONES_LIST[n] == SCALED_MIRROR:
            print("Mirror Match: %s" % TORUS_STRING_LIST[n],
                  "- Crossing Number: %d" % (len(DT_CODE)),
                  "- DT Code: %s" % DT_CODE)
