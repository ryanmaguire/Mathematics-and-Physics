/******************************************************************************
 *                                 LICENSE                                    *
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
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of output.                                                           */
size(256);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(9pt));

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Variable used for indexing.                                               */
int n;

/*  The number of nodes to draw.                                              */
int N_Nodes = 5;

/*  Pairs for drawing the nodes later in the for-loop.                        */
pair A, B, C, D;

/*  Size of the arrow heads.                                                  */
real arsize = 5bp;

/*  Loop over all of the points and label various functions and nodes.        */
for (n = 1; n < N_Nodes; ++n)
{
    /*  Compute the new points for this part of the for-loop.                 */
    A = (2.0*n, 2.0);
    B = (2.0*n, 0.0);
    C = (2.0*(n + 1.0), 2.0);
    D = (2.0*(n + 1.0), 0.0);

    /*  Draw arrows and label the functions between these nodes.              */
    draw("$f_{"+string(n)+"}$", A -- B, 2*E, fpen, SharpArrow(arsize), margins);
    draw("$g_{"+string(n)+"}$", A -- C, 2*S, fpen, SharpArrow(arsize), margins);
    draw("$h_{"+string(n)+"}$", B -- D, 2*N, fpen, SharpArrow(arsize), margins);

    /*  Label the actual nodes.                                               */
    label("$A_{"+string(n)+"}$", A);
    label("$B_{"+string(n)+"}$", B);
}
/*  End of for-loop drawing all but the last two nodes.                       */

/*  Label and draw the final nodes.                                           */
A = (2.0*n, 2.0);
B = (2.0*n, 0.0);
draw("$f_{"+string(n)+"}$", A -- B, 2*E, fpen, SharpArrow(arsize), margins);
label("$A_{"+string(n)+"}$", A);
label("$B_{"+string(n)+"}$", B);
