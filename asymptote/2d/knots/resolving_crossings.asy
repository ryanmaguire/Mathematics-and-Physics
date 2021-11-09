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

/*  Size of the figure.                                                       */
size(128);

import custom_arrows;
import settings;
settings.outformat = "pdf";

real arsize = 5bp;
draw((0, 0) -- (1, 1));
draw((1, 0) -- (0, 1), white + linewidth(5pt));
draw((1, 0) -- (0, 1));

draw((2.5, 2.0){SE} .. (3.5, 2.0){NE});
draw((2.5, 1.0){NE} .. (3.5, 1.0){SE});

draw((2.5, 0.0){SE} .. (2.5, -1.0){SW});
draw((3.5, 0.0){SW} .. (3.5, -1.0){SE});

draw("$0$", (1.4, 0.7) -- (2.1, 1.0), fontsize(5pt), SharpArrow(arsize));
draw("$1$", (1.4, 0.3) -- (2.1, 0.0), fontsize(5pt), SharpArrow(arsize));

