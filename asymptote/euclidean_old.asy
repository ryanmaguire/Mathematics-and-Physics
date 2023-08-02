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
 ******************************************************************************
 *                           Euclidean Geometry                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for two and three dimensional Euclidean geometry.    *
 ******************************************************************************
 *  Functions:                                                                *
 *      CircleIntersection (pair P0, real r0, pair P1, real r1):              *
 *          Given two points and two radii, finds the intersections of the    *
 *          circles centered about each with the respective radii. If the     *
 *          two circles are identical, or if the are no intersection points,  *
 *          an assert will raise an error and about the computation.          *
 *      EuclideanNorm2D (pair A):                                             *
 *          Compute the Euclidean norm of a point in the plane.               *
 *      FindCenter2D (pair A, pair B, pair C):                                *
 *          Find the center of three non-collinear points in the plane. If    *
 *          the points provided are collinear, the function will abort. This  *
 *          returns the point that is equidistant to A, B, and C.             *
 *      PathFromPoints (pair[] Pts, int ArSize, bool closed):                 *
 *          Given an array of points Pts and size ArSize, returns a smooth    *
 *          curve through them. If the bool closed is set, it returns a       *
 *          closed path.                                                      *
 *      PathFromPointsAndAngles (pair[] Pts, real[] Dirs,                     *
 *                               int ArSize, bool closed):                    *
 *          Similar to PathFromPoints but allows the user to specify the out  *
 *          angle at each point, rather than relying on the curve fitting     *
 *          algorithm to do that for you.                                     *
 *      PolyFromPoints (pair[] Pts, int ArSize, bool closed):                 *
 *          Same as PathFromPoints, but instead of a smooth curve it returns  *
 *          a polygonal curve.                                                *
 *      MidPoint2D (pair A, pair B):                                          *
 *          Compute the midpoint of two points in the plane A and B.          *
 *      PlaneToDisk (pair A):                                                 *
 *          Diffeomorphism from the plane to the unit disk, useful if one is  *
 *          doing hyperbolic geometry.                                        *
 *      RelAngle2D (pair O, pair X, pair Y):                                  *
 *          Compute the relative angle of the points X and Y with respect to  *
 *          the point O.                                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************/

/******************************************************************************
 ******************************************************************************
 *                      Begin Two Dimensional Functions                       *
 ******************************************************************************
 ******************************************************************************/

/*  Convert rectangular coordinates to polar.                                 */
pair RectToPolar(pair P)
{
    /*  Declare necessary variables.                                          */
    real theta, r;
    pair O, X;

    /*  Declare points for the unit x vector and the origin.                  */
    O = (0.0, 0.0);
    X = (1.0, 0.0);

    /*  Compute the angle P makes with the x axis.                            */
    theta = RelAngle2D(O, X, P);

    /*  Compute the norm of P.                                                */
    r = EuclideanNorm2D(P);

    /*  The polar representation is just (r, theta), so return this.          */
    return (r, theta);
}

/*  Function for converting a polar coordinate to rectangular.                */
pair PolarToRect(pair P)
{
    /*  Declare necessary variables.                                          */
    real x, y, r, theta;

    /*  Extract the radius and theta from the polar point P.                  */
    r = P.x;
    theta = P.y;

    /*  Compute the x and y coordinates of P and return.                      */
    x = r*cos(theta);
    y = r*sin(theta);

    return (x, y);
}



/* Given an array of pairs, draw a smooth curve through the points.           */
path PathFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0]..Pts[1];

    /* Loop through the array and construct the path.                         */
    for (i=2; i<ArSize; ++i)
        g = g..Pts[i];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g..cycle;

    return g;
}

/* Given an array of pairs, draw a polygonal curve through the point.         */
path PolyFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0]--Pts[1];

    /* Loop through the array and construct the path.                         */
    for (i=2; i<ArSize; ++i)
        g = g--Pts[i];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g--cycle;

    return g;
}

/* Given an array of pairs and an array of reals, draw a path between the     *
 * pairs with angle specified by the array of reals.                          */
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Set the start of the path.                                            */
    g = Pts[0]{dir(Dirs[0])}..Pts[1]{dir(Dirs[1])};

    /* Loop through the arrays and construct the path.                        */
    for (i=2; i<ArSize; ++i)
        g = g..Pts[i]{dir(Dirs[i])};

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g..cycle;

    return g;
}

/******************************************************************************
 ******************************************************************************
 *                     Begin Three Dimensional Functions                      *
 ******************************************************************************
 ******************************************************************************/

/*  Get a point on the line PQ with respect to the parameter t. This is the   *
 *  equation L(t) = (1-t)*P + t*Q;                                            */
triple LinePQ3D(real t, triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    triple X0, X1, out;

    /*  Compute the vector (1-t)P + tQ.                                       */
    X0 = ScaleThreeVector(1.0-t, P);
    X1 = ScaleThreeVector(t, Q);

    /*  Compute the output and return it.                                     */
    out = X0 + X1;
    return out;
}

/* Find midpoint given two points in space.                                   */
triple MidPoint3D(triple A, triple B)
{
    /*  Declare necessary variables.                                          */
    triple out;

    /*  Compute the midpoint using the midpoint formula.                      */
    out = ScaleThreeVector(0.5, A+B);
    return out;
}

/*  Diffeomorphism from R^3 to the unit ball.                                 */
triple SpaceToBall(triple P)
{
    /*  Declare necessary variables.                                          */
    real norm, scale_factor;
    triple out;

    /*  If P is the origin, simply return it since the diffeormorphism fixes  *
     *  this point.                                                           */
    if (P==(0, 0))
        return P;

    /*  Otherwise, compute the length of P.                                   */
    norm = EuclideanNorm3D(P);

    /*  Compute the inverse of 2r / (1+||r||)(1-||r||).                       */
    scale_factor = (-1.0 + sqrt(4.0*norm*norm + 1.0))/(2.0*norm*norm);
    out = ScaleThreeVector(scale_factor, P);
    return out;
}


/*  Convert Cartesian to spherical coordinates.                               */
triple RectToSpherical(real x, real y, real z)
{
    /*  Declare necessary variables.                                          */
    real r, rho, phi, theta;

    /*  Compute the projection in the xy plane (rho), and r.                  */
    rho = sqrt(x*x + y*y);
    r   = sqrt(rho*rho + z*z);

    /*  Compute the azimuth and zenith angles, and return (r, phi, theta).    */
    phi = atan2(y, x);
    theta = pi-atan2(z, rho);
    return (r, phi, theta);
}
