/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      For reasons beyond me, the brightness button stopped working on a     *
 *      2017 iMac 27" running Ubuntu-Budgie 20.04 LTS. I wrote this short     *
 *      bit of code for my girlfriend so she could easily change the          *
 *      brightness (hence the name "mollymakebright.c").                      *
 *                                                                            *
 *      A recent update to Ubuntu-Budgie seems to have fixed the problem and  *
 *      the brightness button works. Keeping this code here for future use.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       November 2, 2021                                              *
 ******************************************************************************/

/*  sprintf and puts are here.                                                */
#include <stdio.h>

/*  system is here.                                                           */
#include <stdlib.h>

/*  Function for changing the brightness of an iMac 27" retina display using  *
 *  xrandr. This has only been tested on Ubuntu-Budgie.                       */
int main(int argc, char *argv[])
{
    /*  Array for storing the xrandr command later.                           */
    char arg[80];

    /*  The user should provide a number between 0 and 1. This value will be  *
     *  be converted from a string and stored in this variable.               */
    double val;

    /*  Check for bad inputs.                                                 */
    if (argc != 2)
    {
        puts("You must supply a number!");
        puts("Example: mollymakebright 0.6");
        return -1;
    }

    /*  Read in the user-provided value and convert it to a double with atof. */
    val = atof(argv[1]);

    /*  Check that the input was legal.                                       */
    if (val > 1.0 || val < 0.0)
    {
        /*  Display funny message and exit.                                   */
        puts("Are you trying to break my computer!");
        puts("The number needs to be between 0 and 1!");
        return -1;
    }

    /*  Create the argument being passed to "system" with sprintf.            */
    sprintf(arg, "xrandr --output eDP --brightness %f", atof(argv[1]));

    /*  Run the command and return.                                           */
    system(arg);
    return 0;
}
/*  End of main.                                                              */

