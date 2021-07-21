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

/*  The opacity will not render correctly for EPS format, so use PDF.         */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for labels and drawing.                                       */
defaultpen(fontsize(9pt));

/*  Function for computing the midpoint of two points in the plane.           */
pair MidPoint2D(pair A, pair B)
{
    /*  Use the midpoint formula and return.                                  */
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    pair mid = (x, y);
    return mid;
}
/*  End of MidPoint2D.                                                        */

/*  Shift for the second block.                                               */
real shift = 9.0;

/*  Pens used throughout the drawing.                                         */
pen outlinepen = deepblue + linewidth(0.8pt);
pen Afill = green + opacity(0.8);
pen Bfill = red + opacity(0.8);
pen Cfill = cyan + opacity(0.8);
pen Dfill = yellow + opacity(0.8);
pen squarefill = gray(0.7) + opacity(0.3);

/*  Coordinates for the four triangles used in the proof.                     */
pair A1 = (0.0, 3.0);
pair A2 = (0.0, 7.0);
pair A3 = (3.0, 7.0);

pair B1 = (4.0, 0.0);
pair B2 = (0.0, 0.0);
pair B3 = (0.0, 3.0);

pair C1 = (7.0, 4.0);
pair C2 = (7.0, 0.0);
pair C3 = (4.0, 0.0);

pair D1 = (3.0, 7.0);
pair D2 = (7.0, 7.0);
pair D3 = (7.0, 4.0);

/*  Fill in the shapes with color.                                            */
filldraw(A1 -- A2 -- A3 -- cycle, Afill, outlinepen);
filldraw(B1 -- B2 -- B3 -- cycle, Bfill, outlinepen);
filldraw(C1 -- C2 -- C3 -- cycle, Cfill, outlinepen);
filldraw(D1 -- D2 -- D3 -- cycle, Dfill, outlinepen);

/*  Fill in the central square.                                               */
filldraw(A1 -- B1 -- C1 -- D1 -- cycle, squarefill, outlinepen);

/*  Label all of the lines.                                                   */
label("$a$", MidPoint2D(A1, A2), E);
label("$b$", MidPoint2D(A2, A3), S);
label("$c$", MidPoint2D(A3, A1), NW);

label("$a$", MidPoint2D(B1, B2), N);
label("$b$", MidPoint2D(B2, B3), E);
label("$c$", MidPoint2D(B3, B1), SW);

label("$a$", MidPoint2D(C1, C2), E);
label("$b$", MidPoint2D(C2, C3), N);
label("$c$", MidPoint2D(C3, C1), SE);

label("$a$", MidPoint2D(D1, D2), S);
label("$b$", MidPoint2D(D2, D3), W);
label("$c$", MidPoint2D(D3, D1), NE);

label("$c^{2}$", (3.5, 3.5), fontsize(12pt));

/*  New points for the triangles in the proof.                                */
A1 = (shift + 0.0, 3.0);
A2 = (shift + 0.0, 7.0);
A3 = (shift + 3.0, 7.0);

B1 = (shift + 3.0, 7.0);
B2 = (shift + 3.0, 3.0);
B3 = (shift + 0.0, 3.0);

C1 = (shift + 7.0, 0.0);
C2 = (shift + 3.0, 0.0);
C3 = (shift + 3.0, 3.0);

D1 = (shift + 3.0, 3.0);
D2 = (shift + 7.0, 3.0);
D3 = (shift + 7.0, 0.0);

/*  Fill in the four triangles.                                               */
filldraw(A1 -- A2 -- A3 -- cycle, Afill, outlinepen);
filldraw(B1 -- B2 -- B3 -- cycle, Bfill, outlinepen);
filldraw(C1 -- C2 -- C3 -- cycle, Cfill, outlinepen);
filldraw(D1 -- D2 -- D3 -- cycle, Dfill, outlinepen);

/*  Label all of the lines.                                                   */
label("$a$", MidPoint2D(A1, A2), E);
label("$b$", MidPoint2D(A2, A3), S);
label("$c$", MidPoint2D(A3, A1), SE);

label("$a$", MidPoint2D(B1, B2), W);
label("$b$", MidPoint2D(B2, B3), N);
label("$c$", MidPoint2D(B3, B1), NW);

label("$a$", MidPoint2D(C1, C2), N);
label("$b$", MidPoint2D(C2, C3), E);
label("$c$", MidPoint2D(C3, C1), SW);

label("$a$", MidPoint2D(D1, D2), S);
label("$b$", MidPoint2D(D2, D3), W);
label("$c$", MidPoint2D(D3, D1), NE);

label("$a^{2}$", (shift+5.0, 5.0), fontsize(12pt));
label("$b^{2}$", (shift+1.5, 1.5), fontsize(12pt));

/*  Fill in the two squares.                                                  */
A1 = B1;
B1 = B2;
C1 = D2;
D1 = (shift + 7.0, 7.0);
A2 = (shift, 0.0);
B2 = (shift + 3.0, 0.0);
C2 = (shift + 3.0, 3.0);
D2 = (shift, 3.0);

filldraw(A1 -- B1 -- C1 -- D1 -- cycle, squarefill, outlinepen);
filldraw(A2 -- B2 -- C2 -- D2 -- cycle, squarefill, outlinepen);

/*  And write out the Pythagorean formula.                                    */
label("$a^{2}+b^{2}=c^{2}$", (0.5*shift + 3.5, -1.0), fontsize(12pt));
