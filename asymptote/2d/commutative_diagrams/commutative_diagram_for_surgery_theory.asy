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
 *      Commutative diagram that appears in Stanley Chang's lectures on       *
 *      surgery theory.                                                       *
 ******************************************************************************/

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of output.                                                           */
size(256);

/*  Default font size for labels.                                             */
defaultpen(fontsize(9pt));

/*  Transform for shifting later.                                             */
transform T;

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Coordinates for the points.                                               */
pair M = (0.0, 0.0);
pair BG = (1.0, 0.0);
pair BO = (1.0, -1.0);

/*  This label is only used on the third diagram.                             */
pair GO = (4.0, 0.5);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$f$", BG -- BO, E, fpen, sharp_arrow, margins);
draw("$\varphi$", M -- BG, N, fpen, sharp_arrow, margins);
draw("$\tilde{\varphi}$", M -- BO, SW, fpen, sharp_arrow, margins);

/*  Label points.                                                             */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);

/*  Shift the labels to the right.                                            */
T = shift(1.5, 0.0);
M = T*M;
BO = T*BO;
BG = T*BG;

/*  Draw arrows.                                                              */
draw("$f$", BG -- BO, E, fpen, sharp_arrow, margins);
draw("$?$", M -- BG, N, fpen, sharp_arrow, margins);
draw("$\tilde{\varphi}$", M -- BO, SW, fpen, sharp_arrow, margins);

/*  Label coordinates.                                                        */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);

/*  Shift the labels right and down. This last set of labels is bigger, hence *
 *  the need for the vertical shift.                                          */
T = shift(1.5, -0.5);
M = T*M;
BO = T*BO;
BG = T*BG;

/*  Draw the arrows.                                                          */
draw("$f_{1}$", M -- GO, NW, fpen, sharp_arrow, margins);
draw("$f_{2}$", M -- BG, S, fpen, sharp_arrow, margins);
draw("$f_{3}$", M -- BO, SW, fpen, sharp_arrow, margins);
draw("$g_{1}$", GO -- BG, E, fpen, sharp_arrow, margins);
draw("$g_{2}$", BG -- BO, E, fpen, sharp_arrow, margins);

/*  Label the points.                                                         */
label("$M$", M);
label("$BO$", BO);
label("$BG$", BG);
label("$G/O$", GO);
