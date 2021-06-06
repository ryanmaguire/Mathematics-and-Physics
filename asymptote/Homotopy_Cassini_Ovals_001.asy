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

/*  Set output format to "pdf".                                               */
import settings;
settings.outformat = "pdf";

/*  Graph module is used for drawing the Cassini ovals.                       */
import graph;

/*  Size of the output.                                                       */
size(256);

/*  Pens for contours and directional lines (Flows).                          */
pen cpen = deepblue + linewidth(1pt);
pen dpen = deepblue + linewidth(0.4);

/*  This struct is an augmentation of an idea I found on tex.stackexchange    *
 *  once upon a time. Unfortunately, I've forgotten the original author. It   *
 *  used for drawing Cassini ovals.                                           */
struct CassiniOval {

    /*  A Cassini oval is specified by two points and a real number. It is    *
     *  the set of all points P such that ||P-A|| * ||P-B|| = r^2, where A    *
     *  and B are the chosen points, and r is the chosen real number.         */
    pair A, B;

    /*  Number of points used to draw the Cassini oval. Higher number means   *
     *  a smoother drawing.                                                   */
    int npoints;

    real a, c, C, alpha;
    transform transf;

    guide[] curve;

    real rho(real phi)
    {
        real x0 = cos(2.0*phi);
        real x1 = a/c;
        real x1 = x1*x1*x1*x1;
        real factor = fabs(x0*x0 + x1 - 1.0);
        return c*sqrt(abs(x0 + sqrt(factor)));
    };

    real rho2(real phi)
    {
        real x0 = cos(2.0*phi);
        real x1 = a/c;
        real x1 = x1*x1*x1*x1;
        real factor = fabs(x0*x0 + x1 - 1.0);
        return c*sqrt(abs(x0 - sqrt(factor)));
    };

    guide[] normLscate()
    {
        guide[] g;
        guide q;
        real xMax = sqrt(a*a + c*c);
        real xMin = -xMax;

        /*  Determine if one contour or two.                                  */
        if(a >= c)
            g.push(transf*(polargraph(rho, 0, 2pi, npoints)--cycle));
        else
        {
            guide q0 = polargraph(rho, -alpha, alpha, npoints);
            guide q1 = reverse(polargraph(rho2, -alpha, alpha, npoints));
            q = q0 -- q1 -- cycle;
            g = (transf*q)^^(transf*reflect(N,S)*q);
        }

        return g;
    }
    /*  End of normLscate.                                                    */

    void operator init(pair A, pair B, real C, int npoints=300)
    {
        assert(C > 0.0);
        assert(npoints > 1);
        this.A = A;
        this.B = B;
        this.C = C;
        this.npoints = npoints;
        this.c = arclength(A--B)*0.5;
        this.a = sqrt(C);
        transf = shift(A)*rotate(degrees(atan2(B.y-A.y, B.x-A.x)))*shift(c, 0);

        if (a < c)
            alpha = asin(a*a/(c*c)) * 0.5;

        curve = normLscate();
    }
    /*  End of init.                                                          */
}
/*  End of CassiniOval.                                                       */

/*  Coordinates for the first focii. The second focii is -A.                  */
pair A = (2, 0);

/*  Variables used later for the Euler method of computing flows.             */
pair AA, BB;
path p;

/*  Increment step used in Euler's method.                                    */
real dx = 0.01;

/*  Maximum distance from the origin flows are allowed to travel. The vector  *
 *  field is zero at the origin, hence Euler's method will loop infinitely.   */
real EPS = 0.01;

/*  Radius of the inner circle.                                               */
real r0 = 0.5;

/*  Variable used for looping over angles.                                    */
real phi;

/*  Used for indexing.                                                        */
int n;

/*  The number of integral curves to be drawn.                                */
int number_of_curves = 16;

/*  The largest oval to be drawn.                                             */
real end = 10;
real end_sq = end*end;

/*  Function to return the 2-norm of a vector (magnitude).                    */
real norm(pair Z)
{
    return sqrt(Z.x*Z.x + Z.y*Z.y);
}

/*  Function to return the unit vector of an input vector.                    */
pair unit_vector(pair Z)
{
    /*  Declare necessary variables.                                          */
    real x, y, norm_Z, rcpr_norm_Z;
    pair out;

    /*  Compute the number of the input.                                      */
    norm_Z = norm(Z);

    /*  If ||Z|| > 0.0, we can normalize Z by dividing by this value.         */
    if (norm_Z > 0.0)
    {
        rcpr_norm_Z = 1.0 / norm_Z
        ;
        x = Z.x * rcpr_norm_Z;
        y = Z.y * rcpr_norm_Z;
    }

    /*  Division by zero, returning zero vector.                              */
    else
    {
        x = 0.0;
        y = 0.0;
    }

    /*  Set the values of the output pair and return.                         */
    out = (x, y);
    return out;
}

// The value of the Cassini oval at (Z.x, Z.y) with parameter a.
real CassiniNorm(pair Z, real a)
{
    return ((Z.x-a)^2+Z.y^2)*((Z.x+a)^2+Z.y^2);
}

/*  The normalize gradient of the Cassini function. Used for computing flows. */
pair Cassini_Gradient(real x, real y, real a)
{
    pair out;
    real x_sq = x*x;
    real y_sq = y*y;
    real a_sq = a*a;
    real rho_sq = x_sq + y_sq;
    out = (4.0*x*(rho_sq - a_sq), 4.0*y*(rho_sq + a_sq));

    return unit_vector(out);
}

// Transform to reflect image across the perpendicular bisector of A and B.
transform T(pair Z0, pair Z1)
{
    pair RotZ0 = rotate(90, (Z0+Z1)/2)*Z0;
    pair RotZ1 = rotate(90, (Z0+Z1)/2)*Z1;
    return reflect(RotZ0, RotZ1);
}

// Parameter used in defining the Cassini ovals.
real a = norm(A);

// Approximate smallest oval by a circle centered at this point. If A and B
// have been changed from (-2, 0) and (2, 0), respectively, then this factor
// will need tweaking.
pair FakeA = A-(a/20)*unit_vector(A);

// Draw circles about the two focii.
filldraw(shift(+FakeA)*scale(r0)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(-FakeA)*scale(r0)*unitcircle, blue+opacity(0.4), cpen);

// Use Euler's method to solve for integral curves of the gradient function f.
for (n = 0; n < number_of_curves; ++n)
{
    phi = 2.0*pi*n/number_of_curves;
    AA = FakeA+r0*expi(phi);
    BB = AA;
    p = AA--BB;
    while (CassiniNorm(BB, a) < end_sq)
    {
        BB = (AA+scale(dx)*Cassini_Gradient(AA.x, AA.y, a));
        p = p--BB;
        AA = BB;
        if (norm(AA) < EPS)
            break;
    }
    draw(p, dpen);
    draw(T(A, -A)*p, dpen);
}

/*  Draw the central Cassini oval (Figure eight).                             */
CassiniOval co = CassiniOval(A, -A, a*a);
draw(co.curve, cpen+linewidth(2pt));

/*  Draw the boundary (which is a different Cassini oval).                    */
co = CassiniOval(A, -A, end);
draw(co.curve, cpen);

// The the bounding Cassini oval is connected, draw a bisecting line.
if (end-a*a >= 0)
    draw((0, sqrt(end-a^2))--(0, -sqrt(end - a*a)), dpen);
