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

/*  Set the rendering factor to 8 for a smoother picture.                     */
import settings;

/*  The tube library is used for drawing knots.                               */
import tube;

/*  And the graph3 library is used for drawing parameteric curves.            */
import graph3;

/*  Set the render factor.                                                    */
settings.render=8;

/*  Size of the figure.                                                       */
size(128);

/*  Setup for how the figure is viewed.                                       */
currentprojection = orthographic(
     camera = (0, 0, 100),
     up = (0, 0, 1),
     target = (0, 0, 0),
     zoom = 0.85
);

/*  Simple parameterization of the figure-eight knot.                         */
triple f(real t)
{
    return ((2+cos(2*t)) * cos(3*t), (2+cos(2*t))*sin(3*t), sin(4*t));
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});
path section=scale(0.35)*unitcircle;

real a = 17pi / 51;
real b = 32pi / 39;
real c = 52pi / 39;
real d = 46pi / 25;
real e = a + 2pi;

path3 p1=graph(f, a, b, n=350, operator ..);
path3 p2=graph(f, b, c, n=350, operator ..);
path3 p3=graph(f, c, d, n=350, operator ..);
path3 p4=graph(f, d, e, n=350, operator ..);

draw(tube(p1, section), light = currentlight,
     surfacepen = material(diffusepen = green,
                          emissivepen = gray(0.2),
                          specularpen = gray(0.2)));

draw(tube(p2, section), light = currentlight,
     surfacepen = material(diffusepen = red,
                          emissivepen = gray(0.2),
                          specularpen = gray(0.2)));

draw(tube(p3, section), light=currentlight,
     surfacepen=material(diffusepen  = blue,
                         emissivepen = gray(0.2),
                         specularpen = gray(0.2)));

draw(tube(p4, section), light=currentlight,
     surfacepen=material(diffusepen  = purple,
                         emissivepen = gray(0.2),
                         specularpen = gray(0.2)));
