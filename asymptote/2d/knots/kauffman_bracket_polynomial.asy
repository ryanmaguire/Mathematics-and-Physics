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
import "vec2.asy" as vec2;

vec2.Vec2 LeftBracket[] = new vec2.Vec2[3];
vec2.Vec2 RightBracket[] = new vec2.Vec2[3];

vec2.Vec2 B[] = new vec2.Vec2[8];
vec2.Vec2 C = vec2.Vec2(0.0, 0.0);

void init_pairs(vec2.Vec2 center)
{
    LeftBracket[0] = vec2.Vec2(-1.0, 1.0) + center;
    LeftBracket[1] = vec2.Vec2(-1.3, 0.0) + center;
    LeftBracket[2] = vec2.Vec2(-1.0, -1.0) + center;

    RightBracket[0] = vec2.Vec2(1.0, 1.0) + center;
    RightBracket[1] = vec2.Vec2(1.3, 0.0) + center;
    RightBracket[2] = vec2.Vec2(1.0, -1.0) + center;

    B[0] = center + vec2.NorthWest;
    B[1] = center + 0.5*vec2.West;
    B[2] = center + vec2.SouthWest;
    B[3] = center + 0.5*vec2.South;
    B[4] = center + vec2.SouthEast;
    B[5] = center + 0.5*vec2.East;
    B[6] = center + vec2.NorthEast;
    B[7] = center + 0.5*vec2.North;

    draw(vec2.PolygonThroughPoints(LeftBracket));
    draw(vec2.PolygonThroughPoints(RightBracket));
    draw(circle(C.AsPair(), 1.0), default.dash_pen);
}

init_pairs(C);
draw(B[2].LineTo(0.1 * B[2]), default.thick_pen);
draw(B[6].LineTo(0.1 * B[6]), default.thick_pen);
draw(B[0].LineTo(B[4]), default.thick_pen);

C += (4.5, 0.0);
init_pairs(C);
vec2.Vec2[] FirstCurve = {B[6], B[7], B[0]};
vec2.Vec2[] SecondCurve = {B[2], B[3], B[4]};
draw(vec2.CurveThroughPoints(FirstCurve));
draw(vec2.CurveThroughPoints(SecondCurve));

C += (4.8, 0.0);
init_pairs(C);
vec2.Vec2[] ThirdCurve = {B[0], B[1], B[2]};
vec2.Vec2[] FourthCurve = {B[4], B[5], B[6]};
draw(vec2.CurveThroughPoints(ThirdCurve));
draw(vec2.CurveThroughPoints(FourthCurve));

label("$=$", (2.2, 0.0), default.massive_pen);
label("$-$", (6.8, 0.0), default.massive_pen);
label("$q$", (7.6, 0.0), default.massive_pen);
