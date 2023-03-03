"""
################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Purpose:                                                                   #
#       Check the Khovanov homologies of knots that had the same Jones         #
#       polynomial as a twist knot.                                            #
#                                                                              #
#       This code is stupidly slow. The khovanov_homology method is not        #
#       optimized. The Java routines in JavaKh are more suited for this.       #
#       This took 53 minutes on a Ryzen 3900x CPU running Debian 11.
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   November 24, 2021.                                                 #
################################################################################
"""

# The SnapPy module will be used for PD code manipulations.
import snappy

# The knots that had the same Jones polynomial as a twist knot.
RolfString = ["K11n13", "K11n19", "K11n57", "K11n70", "K11n88"]

# The corresponding twist knots.
TwistString = ["9_2", "4_1", "5_2", "8_1", "7_2"]

# Loop through the knots and compare there Khovanov homologies.
#   Note: This does not catch mirrors, so as written is somewhat useless.
for k in range(5):
    # The below calculations are slow, so print something so the user doesn't
    # think their computer is broken.
    print("Current: ", RolfString[k], TwistString[k])

    # Create snappy Links from the tables.
    RolfKnot = snappy.Link(RolfString[k])
    TwistKnot = snappy.Link(TwistString[k])

    # Extract PD codes, convert to sage Links, and compute Khovanov homology.
    RolfKh = Link(RolfKnot.PD_code()).khovanov_homology()
    TwistKh = Link(TwistKnot.PD_code()).khovanov_homology()

    # If they're the same, print this. Note, if the mirrors are the same, this
    # will not detect this. So, again, somewhat useless.
    if RolfKh == TwistKh:
        print("\tMatch")
