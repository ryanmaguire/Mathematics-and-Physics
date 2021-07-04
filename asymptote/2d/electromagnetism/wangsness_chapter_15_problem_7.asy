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

/*  Size of the output figure.                                                */
size(128);

/*  Default font size for labels.                                             */
defaultpen(fontsize(6pt));

/*  Pens for the cylinders and lines.                                         */
pen bpen = deepblue;
pen dpen = black;
pen lpen = deepgreen;

/*  Radii of the four cylinders.                                              */
real R0 = 0.4;
real R1 = 0.6;
real R2 = 1.2;
real R3 = 1.5;

/*  Length of the big cylinder in the x direction.                            */
real xlength = 2.5;

/*  Pair for the origin.                                                      */
pair O = (0.0, 0.0);

/*  Draw the circular part of the four cylinders.                             */
draw(circle(O, R0), bpen + linetype("4 4"));
draw(circle(O, R1), bpen);
draw(circle(O, R2), dpen);
draw(circle(O, R3), dpen);

/*  Draw lines for the "long" part of the cylinders.                          */
draw((0.0, R3) -- (xlength, R3));
draw((0.0, -R3) -- (xlength, -R3));
draw((0.0, R1) -- (sqrt(R2*R2 - R1*R1), R1), bpen);
draw((0.0, -R1) -- (sqrt(R2*R2 - R1*R1), -R1), bpen);

/*  Label the radii.                                                          */
draw(Label("$a$", position=0.4), O -- scale(R1)*expi(0.25*pi), lpen);
draw(Label("$b$", position=0.7), O -- scale(R2)*expi(0.83*pi), lpen);
draw(Label("$c$", position=0.5), O -- scale(R3)*expi(1.14*pi), lpen);
