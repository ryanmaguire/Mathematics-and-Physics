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
 *      I use GNOME Builder when writing LaTeX docs because it's a nice IDE.  *
 *      It lacks the LaTeX plug-in available in VS Code, so I wrote this      *
 *      small bit of code to mimic that feature. It runs easily in GNOME      *
 *      Builder's terminal, essentially giving the same functionality for     *
 *      LaTeX docs as VS Code.                                                *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       November 12, 2021                                             *
 ******************************************************************************/

/*  puts and sprintf are here.                                                */
#include <stdio.h>

/*  System is here.                                                           */
#include <stdlib.h>

/*  Function for making LaTeX docs into PDFs with bibliography and hyperlinks *
 *  properly rendered.                                                        */
int main(int argc, char *argv[])
{
    /*  Two commands for building the doc: One with pdflatex, one with bibtex.*/
	char command1[512];
	char command2[512];

    /*  Check for invalid inputs.                                             */
    if (argc != 2)
    {
        puts("Input must be a LaTeX file");
        puts("Example: makemypdf /path/to/file");
		puts("\tDo not include .tex in the filename.");
        return -1;
    }

    /*  Create the commands.                                                  */
	sprintf(command1, "pdflatex %s", argv[1]);
	sprintf(command2, "bibtex %s", argv[1]);

    /*  First command, pdflatex, builds doc with bibliography and hyperlinks. */
	system(command1);

    /*  Second command, bibtex, creates the bibliography file.                */
	system(command2);

    /*  Third command, pdflatex again. Adds the bibliography to the pdf.      */
	system(command1);

    /*  Fourth command, pdflatex. Creates hyperlinks correctly.               */
	system(command1);
	return 0;
}
/*  End of main.                                                              */

