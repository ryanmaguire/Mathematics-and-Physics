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
 *  This file shows basic use of the Cairo library. This is a great tool for  *
 *  creating PDF's and other vector graphics.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  The cairo library is needed for this example. Be sure to link with        *
 *  -lcairo when building.                                                    */
#include <cairo.h>

/*  Function for creating a "Hello, World" PNG file.                          */
int main(void)
{
    /*  Declare necessary variables.                                          */
    cairo_surface_t *surface;
    cairo_t *cr;

    /*  Create the surface. It will be 240x80 in size.                        */
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 240, 80);
    cr = cairo_create(surface);

    /*  Select the font.                                                      */
    cairo_select_font_face(
        cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD
    );

    /*  Use 24pt font size.                                                   */
    cairo_set_font_size(cr, 24.0);

    /*  Draw the picture with a light blue.                                   */
    cairo_set_source_rgb(cr, 0.0, 0.25, 0.98);

    /*  Write the word to the file.                                           */
    cairo_move_to(cr, 20.0, 50.0);
    cairo_show_text(cr, "Hello, world!");

    /*  Destroy the cr variable since we're done with it.                     */
    cairo_destroy(cr);

    /*  Create the file.                                                      */
    cairo_surface_write_to_png(surface, "cairo_hello_world.png");

    /*  And destroy the surface to avoid memory leaks.                        */
    cairo_surface_destroy(surface);
    return 0;
}
/*  End of main.                                                              */

