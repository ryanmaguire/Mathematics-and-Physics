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
 *      Draws the intersection of a plane with a cube, revealing a hexagon.   *
 *      This is what you'd get if you dipped a cube into water with one of    *
 *      vertices of the cube facing down.                                     *
 ******************************************************************************/

/*  Create 3D drawings using 2D points.                                       */
import "vec2.asy" as vec2;

/*  Default pens and parameters for size(512) drawings provided here.         */
import "size_512_default_settings.asy" as default;

/*  Coordinates for all of the points in the cube.                            */
vec2.Vec2 O = vec2.ProjectXYZ(0, 0, 0);
vec2.Vec2 x = vec2.ProjectXYZ(6, 0, 0);
vec2.Vec2 y = vec2.ProjectXYZ(0, 6, 0);
vec2.Vec2 z = vec2.ProjectXYZ(0, 0, 6);
vec2.Vec2 xy = vec2.ProjectXYZ(6, 6, 0);
vec2.Vec2 xz = vec2.ProjectXYZ(6, 0, 6);
vec2.Vec2 yz = vec2.ProjectXYZ(0, 6, 6);
vec2.Vec2 xyz = vec2.ProjectXYZ(6, 6, 6);
vec2.Vec2 MID = vec2.ProjectXYZ(3, 3, 3);
vec2.Vec2 a1 = vec2.ProjectXYZ(3, 0, 6);
vec2.Vec2 a2 = vec2.ProjectXYZ(3, 6, 6);
vec2.Vec2 a3 = vec2.ProjectXYZ(0, 3, 6);
vec2.Vec2 a4 = vec2.ProjectXYZ(6, 3, 6);
vec2.Vec2 b1 = vec2.ProjectXYZ(0, 0, 3);
vec2.Vec2 b2 = vec2.ProjectXYZ(6, 0, 3);
vec2.Vec2 b3 = a1;
vec2.Vec2 b4 = vec2.ProjectXYZ(3, 0, 0);
vec2.Vec2 c1 = b2;
vec2.Vec2 c2 = vec2.ProjectXYZ(6, 6, 3);
vec2.Vec2 c3 = a4;
vec2.Vec2 c4 = vec2.ProjectXYZ(6, 3, 0);
vec2.Vec2 d1 = vec2.ProjectXYZ(0, 6, 3);
vec2.Vec2 d2 = c2;
vec2.Vec2 d3 = a2;
vec2.Vec2 d4 = vec2.ProjectXYZ(3, 6, 0);
vec2.Vec2 e1 = a3;
vec2.Vec2 e2 = vec2.ProjectXYZ(0, 3, 0);
vec2.Vec2 e3 = b1;
vec2.Vec2 e4 = d1;
vec2.Vec2 f1 = e2;
vec2.Vec2 f2 = c4;
vec2.Vec2 f3 = b4;
vec2.Vec2 f4 = d4;
vec2.Vec2 A = vec2.ProjectXYZ(3, 3, 6);
vec2.Vec2 B = vec2.ProjectXYZ(3, 0, 3);
vec2.Vec2 C = vec2.ProjectXYZ(6, 3, 3);
vec2.Vec2 D = vec2.ProjectXYZ(3, 6, 3);
vec2.Vec2 E = vec2.ProjectXYZ(0, 3, 3);
vec2.Vec2 F = vec2.ProjectXYZ(3, 3, 0);

/*  Draw the back of the cube.                                                */
draw(O.LineTo(x), default.dash_pen);
draw(O.LineTo(y), default.dash_pen);
draw(O.LineTo(z), default.dash_pen);

/*  Thin lines that make crosses on each of the outer faces.                  */
draw(a1.LineTo(a2), default.thin_pen);
draw(a3.LineTo(a4), default.thin_pen);
draw(c1.LineTo(c2), default.thin_pen);
draw(c3.LineTo(c4), default.thin_pen);
draw(d1.LineTo(d2), default.thin_pen);
draw(d3.LineTo(d4), default.thin_pen);

/*  Dashed lines that makes crosses on each of the inner faces.               */
draw(b1.LineTo(b2), default.thin_dash_pen);
draw(b3.LineTo(b4), default.thin_dash_pen);
draw(e1.LineTo(e2), default.thin_dash_pen);
draw(e3.LineTo(e4), default.thin_dash_pen);
draw(f1.LineTo(f2), default.thin_dash_pen);
draw(f3.LineTo(f4), default.thin_dash_pen);

/*  Dashed lines on the inside of the cube connecting the centers of the      *
 *  faces to the center of the cube.                                          */
draw(A.LineTo(MID), default.thin_dash_pen);
draw(B.LineTo(MID), default.thin_dash_pen);
draw(C.LineTo(MID), default.thin_dash_pen);
draw(D.LineTo(MID), default.thin_dash_pen);
draw(E.LineTo(MID), default.thin_dash_pen);
draw(F.LineTo(MID), default.thin_dash_pen);

/*  Draw the hexagon.                                                         */
draw(a1.LineTo(a3), default.blue_pen);
draw(a3.LineTo(d1), default.blue_dash_pen);
draw(d1.LineTo(d4), default.blue_pen);
draw(d4.LineTo(c4), default.blue_dash_pen);
draw(c4.LineTo(b2), default.blue_pen);
draw(b2.LineTo(a1), default.blue_dash_pen);

/*  Draw the spokes of the hexagon.                                           */
draw(a1.LineTo(MID), default.green_dash_pen);
draw(a3.LineTo(MID), default.green_dash_pen);
draw(d1.LineTo(MID), default.green_dash_pen);
draw(c4.LineTo(MID), default.green_dash_pen);
draw(d4.LineTo(MID), default.green_dash_pen);
draw(b2.LineTo(MID), default.green_dash_pen);

/*  Draw the front of the cube.                                               */
draw(x.LineTo(xy));
draw(y.LineTo(xy));
draw(x.LineTo(xz));
draw(z.LineTo(xz));
draw(y.LineTo(yz));
draw(z.LineTo(yz));
draw(xy.LineTo(xyz));
draw(yz.LineTo(xyz));
draw(xz.LineTo(xyz));
