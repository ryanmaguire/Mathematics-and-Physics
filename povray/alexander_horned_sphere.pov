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
 *  This is a modification of Bernard H.'s drawing, who graciously dedicated  *
 *  the image and code to the public domain. The modifications are just to    *
 *  learn how POV-Ray works, and not to improve the image.                    *
 ******************************************************************************/

global_settings {
    assumed_gamma 1
}

camera {
  location <0.00, 3.35, -3.50>
  right x
  up y
  look_at <0.00, 1.30, 0.00>
  angle 40.0
}

light_source {
  <4.5, 8.0, -8.0>,
  color rgb <1.0, 1.0, 1.0>
}

/*  Torus minor radius.                                                       */
#declare r = 0.03;

/*  Scale when incrementing level.                                            */
#declare k = 0.50;

/*  Angle of torus slice removed.                                             */
#declare theta = 75.0;

/*  Maximum number of iterations allowed in the Alexander construction.       */
#declare level_max = 10;

#declare p1 = <+sin(theta*pi / 360.0), 1.00 + cos(theta*pi / 360.0), 0.00>;
#declare p2 = <-sin(theta*pi / 360.0), 1.00 + cos(theta*pi / 360.0), 0.00>;

#declare torus_section = union {

    difference {

        torus {
            1.0, r
            rotate 90.0*x
            translate y
        }

        prism {
            -1.01*r, 1.01*r, 4.0
            <0.0, 0.0>,
            2.0 * <+sin(theta*pi / 360.0), +cos(theta*pi / 360.0)>,
            2.0 * <-sin(theta*pi / 360.0), +cos(theta*pi / 360.0)>
            <0.0, 0.0>
            rotate -90.0*x
            translate y
        }
    }

    sphere {
        p1, r
    }

    sphere {
        p2, r
    }

    finish {
        ambient 0.10
        diffuse 0.60
        specular 0.60
        roughness 0.05
        metallic
    }
}

#macro recursive_torus(L)

#if (L < 5)

#local c = rgb(<1.00, 0.15, 0.00>*(5.0 - L) + <1.00, 1.00, 0.00>*L) / 5.0;

#else

#local c = rgb <1.0, 1.0, 0.0>;

#end
/*  End of #if (L < 5).                                                       */

#if (L = level_max)

object {
    torus_section
    pigment {
        c
    }
}

#else
/*  Else for #if (L = level_max).                                             */

union {

    object {
        torus_section
        pigment {
            c
        }
    }

    object {
        recursive_torus(L + 1)
        scale k
        rotate 90.0*z
        translate p1
    }

    object {
        recursive_torus(L + 1)
        scale k
        rotate +90.0*y
        rotate -90.0*z
        translate p2
    }
}

#end
/*  End of #if (L = level_max).                                               */

#end
/*  End of #macro recursive_torus(L).                                         */

object {
  recursive_torus(0)
  translate r*y
}

/*  Background plane with shadows cast on it from the rendering.              */
plane {
    y, 0

    pigment {
        rgb <0.20, 0.20, 0.80>
    }

    finish {
        ambient 0.1
        diffuse 0.6
    }
}
