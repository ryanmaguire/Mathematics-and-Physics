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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Commutative diagram that appears in Stanley Chang's lectures on       *
 *      surgery theory.                                                       *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of output.                                                           */
size(256);

/*  Default font size for labels.                                             */
defaultpen(fontsize(9pt));

/*  Transform for shifting later.                                             */
transform T;

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Arrow size and coordinates for points.                                    */
real arsize = 5bp;
pair M = (0.0, 0.0);
pair BG = (1.0, 0.0);
pair GO = (1.0, 1.0);
pair BO = (1.0, -1.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$f$", BG -- BO, 2*E, fpen, SharpArrow(arsize), margins);
draw("$\varphi$", M -- BG, 2*N, fpen, SharpArrow(arsize), margins);
draw("$\tilde{\varphi}$", M -- BO, 2*SW, fpen, SharpArrow(arsize), margins);

/*  Label points.                                                             */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);

/*  Shift the labels by 2.                                                    */
T = shift(2.0, 0.0);
M = T*M;
BO = T*BO;
BG = T*BG;
GO = T*GO;

/*  Draw arrows.                                                              */
draw("$f$", BG -- BO, 2*E, fpen, SharpArrow(arsize), margins);
draw("$?$", M -- BG, 2*N, fpen, SharpArrow(arsize), margins);
draw("$\tilde{\varphi}$", M -- BO, 2*SW, fpen, SharpArrow(arsize), margins);

/*  Label coordinates.                                                        */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);

/*  Shift the labels right by 2 and down by 0.5.                              */
T = shift(2.0, -0.5);
M = T*M;
BO = T*BO;
BG = T*BG;
GO = T*GO;

/*  Draw the arrows.                                                          */
draw("$f_{1}$", M -- GO, 2*NW, fpen, SharpArrow(arsize), margins);
draw("$f_{2}$", M -- BG, 2*S, fpen, SharpArrow(arsize), margins);
draw("$f_{3}$", M -- BO, 2*SW, fpen, SharpArrow(arsize), margins);
draw("$g_{1}$", GO -- BG, 2*E, fpen, SharpArrow(arsize), margins);
draw("$g_{2}$", BG -- BO, 2*E, fpen, SharpArrow(arsize), margins);

/*  Label the points.                                                         */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);
label("$G/O$", GO);
