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
#       Check the Khovanov homologies of knots that had the same Jones'        #
#       polynomial as a twist knot.                                            #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   November 24, 2021.                                                 #
################################################################################
"""

# The SnapPy module will be used for most of the computations with knots.
import snappy

RolfString = ["K11n13", "K11n19", "K11n57", "K11n70", "K11n88"]
TwistString = ["9_2", "4_1", "5_2", "8_1", "7_2"]

for k in range(5):
    print("Current: ", RolfString[k], TwistString[k])
    RolfKnot = snappy.Link(RolfString[k])
    TwistKnot = snappy.Link(TwistString[k])
    RolfKh = Link(RolfKnot.PD_code()).khovanov_homology()
    TwistKh = Link(TwistKnot.PD_code()).khovanov_homology()

    if RolfKh == TwistKh:
        print("\tMatch")
