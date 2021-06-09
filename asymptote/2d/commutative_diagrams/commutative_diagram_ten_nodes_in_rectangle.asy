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

/*  Make sure _custom_arrows.asy is in your path. This file is found in the   *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import _custom_arrows;

/*  Size of output.                                                           */
size(256);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(9pt));

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Variable used for indexing.                                               */
int i;

/*  size of the arrow heads.                                                  */
real arsize = 5bp;

/*  Loop over all of the points and label various functions and nodes.        */
for(i=1; i<5; ++i)
{
    draw("$f_{"+string(i)+"}$", (2*i, 2)--(2*i,   0), 2*E, fpen,
         SharpArrow(arsize), margins);
    draw("$g_{"+string(i)+"}$", (2*i, 2)--(2*i+2, 2), 2*S, fpen,
         SharpArrow(arsize), margins);
    draw("$h_{"+string(i)+"}$", (2*i, 0)--(2*i+2, 0), 2*N, fpen,
         SharpArrow(arsize), margins);

    label("$A_{"+string(i)+"}$", (2*i, 2));
    label("$B_{"+string(i)+"}$", (2*i, 0));
}

/*  Draw the rightmost arrows and labels.                                     */
draw("$f_{"+string(i)+"}$", (2*i, 2)--(2*i, 0), 2*E, fpen,
     SharpArrow(arsize), margins);

label("$A_{"+string(i)+"}$", (2*i, 2));
label("$B_{"+string(i)+"}$", (2*i, 0));
