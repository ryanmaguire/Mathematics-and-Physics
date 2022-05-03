/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *  This file shows how to use some of the escape sequences in C to print     *
 *  colored text.                                                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  puts will be used frequently.                                             */
#include <stdio.h>

/*  Macros for the escape sequences of various colors.                        */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_GREEN_BACKGROUND "\e[102m"

/*  Function for printing colored text to the console.                        */
int main(void)
{
    puts(ANSI_COLOR_RED "This is red.");
    puts(ANSI_COLOR_GREEN "This is green.");
    puts(ANSI_COLOR_YELLOW "How about some yellow?");
    puts(ANSI_COLOR_BLUE "And who doesn't love blue?");
    puts(ANSI_COLOR_MAGENTA "This is magenta.");
    puts(ANSI_COLOR_CYAN "And this is cyan." ANSI_COLOR_RESET);
    puts("\nAnd now for some background color:");
    puts(ANSI_GREEN_BACKGROUND "\n\n\nIs This Green Enough For You?\n");
    puts(ANSI_COLOR_RESET"\n");
    return 0;
}
/*  End of main.                                                              */

