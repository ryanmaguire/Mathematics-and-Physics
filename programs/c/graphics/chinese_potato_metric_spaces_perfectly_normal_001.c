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
 *      Demonstrates that metric spaces are perfectly normal using characters *
 *      from simplified Chinese. The characters spell potato, a running joke  *
 *      between a few of my students.                                         *
 ******************************************************************************/

typedef struct color {
    unsigned char red, green, blue;
} color;

typedef struct pair {
    double x, y;
} pair;

typedef struct quadrilateral {
    pair a, b, c, d;
} quadrilateral;

static quadrilateral tu[3] = {
    {{-0.5, 0.0}, {0.5, 1.0}, 0.0},
    {{-1.0, -0.5}, {1.0, 0.0}, 0.0},
};

static quadrilateral dou[8] = {

} 
