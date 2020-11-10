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

/*  Default settings for all 2D drawings.                                     */
import settings;
if(settings.render < 0)
    settings.render = 8;

if(!settings.multipleView)
    settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;
settings.bw          = false;
settings.cmyk        = false;
viewportmargin       = (2, 2);

/*  Pen used for labels and drawing. The size of the pen is suitable for most *
 *  drawings, however depending on the "size" of the figure one may deem it   *
 *  too thick or too thin. Just reset it after importing if so.               */
defaultpen(black+linewidth(0.5pt)+fontsize(7pt));

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

/*  Commonly used pens.                                                       */
pen axesp  = black + linewidth(0.7pt) + fontsize(9pt);
pen dashp  = defaultpen + linetype("8 4");
pen thinp  = black + linewidth(0.3pt);
pen labelp = defaultpen + fontsize(10pt);

/*  Size used for drawing dots.                                               */
real rDot = 0.025;
