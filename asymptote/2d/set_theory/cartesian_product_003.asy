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
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt) + fontsize(10pt));
pen thickp = black + linewidth(0.7pt) + fontsize(14pt);
real r = 0.05;
real arsize = 5bp;
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw green to indicate the set A.                                         */
filldraw(circle((1.0, 0.0), r), green, green);
filldraw(circle((2.0, 0.0), r), green, green);
filldraw(circle((5.0, 0.0), r), green, green);
filldraw(circle((6.0, 0.0), r), green, green);
filldraw(circle((7.0, 0.0), r), green, green);
draw((2.0, 0.0) -- (5.0, 0.0), green);
draw((6.0, 0.0) -- (7.0, 0.0), green);

/*  Draw red to denote the set B.                                             */
filldraw(circle((0.0, 1.0), r), red, red);
filldraw(circle((0.0, 2.0), r), red, red);
filldraw(circle((0.0, 5.0), r), red, red);
draw((0.0, 2.0) -- (0.0, 5.0), red);

/*  Use blue to mark AxB (Cartesian product).                                 */
filldraw(circle((1.0, 1.0), r), blue, blue);
filldraw(circle((1.0, 2.0), r), blue, blue);
filldraw(circle((1.0, 5.0), r), blue, blue);
filldraw(circle((2.0, 1.0), r), blue, blue);
filldraw(circle((5.0, 1.0), r), blue, blue);
filldraw(circle((6.0, 1.0), r), blue, blue);
filldraw(circle((7.0, 1.0), r), blue, blue);
filldraw(circle((2.0, 2.0), r), blue, blue);
filldraw(circle((2.0, 5.0), r), blue, blue);
filldraw(circle((5.0, 2.0), r), blue, blue);
filldraw(circle((5.0, 5.0), r), blue, blue);
filldraw(circle((6.0, 2.0), r), blue, blue);
filldraw(circle((7.0, 2.0), r), blue, blue);
filldraw(circle((6.0, 5.0), r), blue, blue);
filldraw(circle((7.0, 5.0), r), blue, blue);

draw((1.0, 2.0) -- (1.0, 5.0), blue);
draw((2.0, 1.0) -- (5.0, 1.0), blue);
draw((6.0, 1.0) -- (7.0, 1.0), blue);

filldraw((2.0, 2.0) -- (5.0, 2.0) -- (5.0, 5.0) -- (2.0, 5.0) -- cycle,
         blue+opacity(0.4), blue);
filldraw((6.0, 2.0) -- (7.0, 2.0) -- (7.0, 5.0) -- (6.0, 5.0) -- cycle,
         blue+opacity(0.4), blue);
