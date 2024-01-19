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
 *      Provides commonly used arrow heads.                                   *
 ******************************************************************************/

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as custom_arrows;

/*  Default size of arrow heads.                                              */
real arrow_size = 5bp;

/*  The default arrow head uses the "tikz-stealth" style in custom_arrows.    */
arrowbar sharp_arrow = custom_arrows.SharpArrow(arrow_size);
arrowbar mid_sharp_arrow = custom_arrows.MidSharpArrow(arrow_size);
arrowbar begin_sharp_arrow = custom_arrows.BeginSharpArrow(arrow_size);
arrowbar sharp_arrows = custom_arrows.SharpArrows(arrow_size);
