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
 *      Functions for creating 3D drawings with 2D points.                    *
 ******************************************************************************/

/*  Factor for the x axis which is sheared by the y and z axes.               */
real shear_factor = -0.4;

/******************************************************************************
 *  Function:                                                                 *
 *      ResetShear                                                            *
 *  Purpose:                                                                  *
 *      Resets the shear factor to a new user-provided value.                 *
 *  Arguments:                                                                *
 *      new_factor (real):                                                    *
 *          The new value for the shear factor.                               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
void ResetShear(real new_factor)
{
    shear_factor = new_factor;
}

/******************************************************************************
 *  Function:                                                                 *
 *      XYZPoint                                                              *
 *  Purpose:                                                                  *
 *      Projects a point (x, y, z) onto the plane by shearing the x axis in   *
 *      terms of the y and z. This creates the standard 3D coordinate axes    *
 *      one finds in a vector calculus or 3D geometry text book.              *
 *  Arguments:                                                                *
 *      x (real):                                                             *
 *          The x coordinate of the point.                                    *
 *      y (real):                                                             *
 *          The y coordinate of the point.                                    *
 *      z (real):                                                             *
 *          The z coordinate of the point.                                    *
 *  Outputs:                                                                  *
 *      ProjXYZ (pair):                                                       *
 *          The projection of the point (x, y, z).                            *
 ******************************************************************************/
pair XYZPoint(real x, real y, real z)
{
    /*  The x component is computed from the y and z axes by shearing.        */
    pair X = (shear_factor*x, shear_factor*x);

    /*  The y and z axes are unchanged by the projection.                     */
    pair Y = (y, 0.0);
    pair Z = (0.0, z);

    /*  The final result (the projection) is the sum of the three terms.      */
    return X + Y + Z;
}
/*  End of XYZPoint.                                                          */
