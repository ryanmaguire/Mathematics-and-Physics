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
#       Simple script for creating the Jones and HOMFLY database.              #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       May 18, 2023.                                                  #
################################################################################
"""

# pylint will complain that regina does not have a "Link" attribute, even
# though it does. The following line disables this erroneous warning.
# pylint: disable=E1101

# Needed for parsing inputs.
import sys

# Used for computing knot invariants.
import regina

# Handles CSV files.
import pandas

# The input from the user is the CSV containing the list of DT codes.
DT_CODE_FILE_NAME = sys.argv[1]

# The names of the output files for the two invariants. The input file name
# ends with "_dt.csv" so we remove the last 7 characters and append the name
# of the invariant instead.
JONES_FILE_NAME = (DT_CODE_FILE_NAME.split("/")[-1])[0:-7] + "-jones.csv"
HOMFLY_FILE_NAME = (DT_CODE_FILE_NAME.split("/")[-1])[0:-7] + "-homfly.csv"

# Extract the data from the CSV.
CSV_DATA = pandas.read_csv(DT_CODE_FILE_NAME)

# Print an update every now and again.
NUMBER_OF_KNOTS = len(CSV_DATA.dt_code)
SKIP = 100000

# Open the files for the Jones and HOMFLY polynomials with write permissions.
JONES_FILE = open(JONES_FILE_NAME, "w")
HOMFLY_FILE = open(HOMFLY_FILE_NAME, "w")

# Loop through each DT code.
for CURRENT_KNOT in range(NUMBER_OF_KNOTS):

    # Print an update so we know things are moving along.
    if CURRENT_KNOT % SKIP == 0:
        print("\t", CURRENT_KNOT, NUMBER_OF_KNOTS)

    # Get the knot the current DT code represents.
    DT_STRING = CSV_DATA.dt_code[CURRENT_KNOT]
    REG_LINK = regina.Link.fromDT(DT_STRING)

    # Shrink the strings by removing spaces.
    JONES_STRING = str(REG_LINK.jones()).replace(" ", "")
    HOMFLY_STRING = str(REG_LINK.homfly()).replace(" ", "")

    # Write the results to the new CSV files.
    JONES_FILE.write(DT_STRING + "," + JONES_STRING + "\n")
    HOMFLY_FILE.write(DT_STRING + "," + HOMFLY_STRING + "\n")
