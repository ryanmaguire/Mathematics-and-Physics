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
import "size_512_default_settings.asy" as default;

pen white_pen = white + linewidth(5.0);
pen big_pen = fontsize(32pt);

pair A[] = new pair[8];
pair B[] = new pair[8];
pair C = (0.0, 0.0);

void init_pairs(pair center)
{
    A[0] = (-1.0, 1.0) + center;
    A[1] = (-1.3, 0.0) + center;
    A[2] = (-1.0, -1.0) + center;
    A[3] = (-0.7, 0.0) + center;
    A[4] = (1.0, 1.0) + center;
    A[5] = (1.3, 0.0) + center;
    A[6] = (1.0, -1.0) + center;
    A[7] = (0.7, 0.0) + center;

    B[0] = expi(0.75 * pi) + center;
    B[1] = center - (0.5, 0.0);
    B[2] = expi(1.25 * pi) + center;
    B[3] = center - (0.0, 0.5);
    B[4] = expi(1.75 * pi) + center;
    B[5] = center + (0.5, 0.0);
    B[6] = expi(0.25 * pi) + center;
    B[7] = center + (0.0, 0.5);

    draw(A[0] -- A[1] -- A[2]);
    draw(A[4] -- A[5] -- A[6]);
    draw(circle(C, 1.0), default.dash_pen);
}

init_pairs(C);

draw(B[0] -- B[4], default.thick_pen);
draw(B[2] -- B[6], white_pen);
draw(B[2] -- B[6], default.thick_pen);

C += (5.0, 0.0);

init_pairs(C);
draw(B[0] .. B[1] .. B[2]);
draw(B[4] .. B[5] .. B[6]);

C += (5.2, 0.0);

init_pairs(C);
draw(B[6] .. B[7] .. B[0]);
draw(B[2] .. B[3] .. B[4]);

label("$=$", (2.3, 0.0), big_pen);
label("$q$", (3.2, 0.0), big_pen);
label("$+$", (7.2, 0.0), big_pen);
label("$q^{-1}$", (8.3, 0.0), big_pen);
