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

pair O = (0.0, 0.0);
pair A = (1.0, 1.0);
pair B = (1.0, -1.0);
pair C = (-1.0, -1.0);
pair D = (-1.0, 1.0);
real rDot = 0.1;

draw(O{N} .. A{SE} .. O{W});
draw(O{E} .. B{SW} .. O{N});
draw(O{S} .. C{NW} .. O{E});
draw(O{W} .. D{NE} .. O{S});

filldraw(circle(O, rDot), black, black);