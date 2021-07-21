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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Compute the dot product of two 2-dimensional vectors.                     */
real DotProduct2D(pair A, pair B)
{
    /*  Compute the Euclidean dot product and return.                         */
    return A.x*B.x + A.y*B.y;
}
/*  End of DotProduct2D.                                                      */

/*  Returns the Euclidean norm of a 2-dimensional point.                      */
real EuclideanNorm2D(pair A)
{
    /*  Using Pythagoras, we simply compute sqrt(x^2 + y^2).                  */
    return  sqrt(A.x*A.x + A.y*A.y);
}
/*  End of EuclideanNorm2D.                                                   */

/*  Returns the angle between X and Y relative to the point O.                */
real RelAngle2D(pair O, pair X, pair Y)
{
    /*  Declare necessary variables.                                          */
    pair P, Q;
    real dot_prod, abs_prod;

    /*  Compute the vectors from O to X and O to Y, respectively.             */
    P = X - O;
    Q = Y - O;

    /*  Compute the dot product of P and Q.                                   */
    dot_prod = DotProduct2D(P, Q);

    /*  Compute the product of the norms of P and Q as well.                  */
    abs_prod = EuclideanNorm2D(P)*EuclideanNorm2D(Q);

    /*  If abs_prod is 0, either P = O, or Q = O. In either case the angle is *
     *  undefined, so return Not-a-Number.                                    */
    if (abs_prod == 0.0)
        return nan;

    /*  Otherwise, use the fact that <a|b> = ||a|| ||b|| cos(theta), where    *
     *  <a|b> denotes the dot product of a and b, and ||a|| represents the    *
     *  Euclidean norm of a. Using this, we solve for theta.                  */
    else
        return acos(dot_prod/abs_prod);
}
/*  End of RelAngle2D.                                                        */

/*  Radius for drawing dots.                                                  */
real rDot = 0.03;

/*  Pen for labels.                                                           */
pen labelp = defaultpen + fontsize(10pt);

/*  Start and end times for the line between A and C, and B and C.            */
real start = -0.2;
real end = 1.3;

/*  Radius used for drawing arcs used to represent angles.                    */
real angle_length = 0.2;

/*  The three points used for the two lines.                                  */
pair A = (0.0, 1.0);
pair B = (0.0, 0.0);
pair C = (4.0, 0.2);

/*  The start and end points on both lines.                                   */
pair L0_Start = scale(1.0 - start)*A + scale(start)*C;
pair L1_Start = scale(1.0 - start)*B + scale(start)*C;
pair L0_End = scale(1.0 - end)*A + scale(end)*C;
pair L1_End = scale(1.0 - end)*B + scale(end)*C;

/*  The angles the two lines make.                                            */
real angle1 = RelAngle2D(A, B, C);
real angle2 = RelAngle2D(B, A, C);

/*  Factor for converting from radians to degrees.                            */
real r2d = 0.017453292519943295;

/*  Draw the lines.                                                           */
draw(L0_Start -- L0_End);
draw(L1_Start -- L1_End);

/*  Draw the perspective line from A to B.                                    */
draw(A -- B);

/*  Mark the angles.                                                          */
draw(arc(A, angle_length, 270, 270 + r2d*angle1));
draw(arc(B, angle_length, 90,  90 - r2d*angle2));

/*  Mark and label the points.                                                */
filldraw(circle(A, rDot));
filldraw(circle(B, rDot));
filldraw(circle(C, rDot));
label("$A$", A, NE, labelp);
label("$B$", B, SE, labelp);
label("$C$", C, N, labelp);
