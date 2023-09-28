/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This draws a large commutative diagram featuring 10 vertices arranged *
 *      in two rows. This could be used, for example, to demonstrate the      *
 *      the Five-Lemma that occurs in homological algebra.                    *
 ******************************************************************************/

/*  Default pens and parameters for size(256) drawings provided here.         */
import "size_256_default_settings.asy" as default;

/*  Variable used for indexing.                                               */
int n;

/*  The number of nodes to draw.                                              */
int N_Nodes = 5;

/*  Pairs for drawing the nodes later in the for-loop.                        */
pair A, B, C, D;

/*  The final node as a string.                                               */
string Ns = string(N_Nodes);

/*  Loop over all of the points and label various functions and nodes.        */
for (n = 1; n < N_Nodes; ++n)
{
    /*  Compute the new points for this part of the for-loop.                 */
    A = (2.0*n, 2.0);
    B = (2.0*n, 0.0);
    C = (2.0*(n + 1.0), 2.0);
    D = (2.0*(n + 1.0), 0.0);

    /*  Convert the current index to a string for the labels.                 */
    string ns = string(n);

    /*  Draw arrows and label the functions between these nodes.              */
    draw("$f_{"+ns+"}$", A -- B, E, default.sharp_arrow, default.small_margins);
    draw("$g_{"+ns+"}$", A -- C, S, default.sharp_arrow, default.small_margins);
    draw("$h_{"+ns+"}$", B -- D, N, default.sharp_arrow, default.small_margins);

    /*  Label the actual nodes.                                               */
    label("$A_{"+ns+"}$", A);
    label("$B_{"+ns+"}$", B);
}
/*  End of for-loop drawing all but the last two nodes.                       */

/*  Label and draw the final nodes.                                           */
A = (2.0*n, 2.0);
B = (2.0*n, 0.0);
draw("$f_{"+Ns+"}$", A -- B, E, default.sharp_arrow, default.small_margins);
label("$A_{"+Ns+"}$", A);
label("$B_{"+Ns+"}$", B);
