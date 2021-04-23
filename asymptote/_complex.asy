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

import _euclidean;

pair _Complex_One  = (1.0, 0.0);
pair _Complex_I    = (0.0, 1.0);
pair _Complex_Zero = (0.0, 0.0);

pair ComplexFromRect(real x, real y)
{
    return (x, y);
}

pair ComplexFromPolar(real r, real theta)
{
    return (r*cos(theta), r*sin(theta));
}

pair ComplexScale(real r, pair z)
{
    return (r*z.x, r*z.y);
}

pair ComplexAdd(pair z, pair w)
{
    return (z.x + w.x, z.y + w.y);
}

pair ComplexSubtract(pair z, pair w)
{
    return (z.x-w.x, z.y-w.y);
}

pair ComplexMult(pair z, pair w)
{
    return (z.x*w.x - z.y*w.y, z.x*w.y + z.y*w.x);
}

pair ComplexConj(pair z)
{
    return (z.x, -z.y);
}

pair ComplexRcpr(pair z)
{
    real factor;

    factor = z.x*z.x + z.y*z.y;
    assert(factor > 0.0);

    factor = 1.0/factor;

    return ComplexScale(factor, ComplexConj(z));
}

pair ComplexDivide(pair z, pair w)
{
    return ComplexMult(z, ComplexRcpr(w));
}

real ComplexRealPart(pair z)
{
    return z.x;
}

real ComplexImagPart(pair z)
{
    return z.y;
}

real ComplexAbs(pair z)
{
    return sqrt(z.x*z.x + z.y*z.y);
}

// Given z = x+iy, P = a+ib compute Mobius transform about P as a function of z.
pair MobiusTransform(pair z, pair P)
{
    return ComplexDivide(
        ComplexSubtract(z, P),
        ComplexSubtract(_Complex_One, ComplexMult(ComplexConj(P), z))
    );
}

pair InverseMobiusTransform(pair z, pair P)
{
    return ComplexDivide(
        ComplexAdd(z, P),
        ComplexAdd(_Complex_One, ComplexMult(ComplexConj(P), z))
    );
}

pair HyperbolicPath(real t, pair P, pair Q)
{
    pair TransQ, InvPoint;

    TransQ = MobiusTransform(Q, P);
    InvPoint = ComplexScale(t, TransQ);

    return InverseMobiusTransform(InvPoint, P);
}

pair HyperbolicCircle(pair P, real radius, real theta)
{
    pair InvP;

    InvP = ComplexFromPolar(radius, theta);
    return InverseMobiusTransform(InvP, P);
}

pair HyperbolicPathPoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x, y;

    x = A.x*(1.0-t) + B.x*t;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x+ c2)*(A.x + c2);

        y = sqrt(c1 - (x+c2)*(x+c2));
    }
    else
        y = A.y*(1.0-t) + B.y*t;

    return (x, y);
}

pair HyperbolicLinePoincarePlane(real t, pair A, pair B)
{
    pair C;
    pair P, Q, O;

    O = (0.0, 0.0);

    real x, dist;

    P = MidPoint2D(A, B);

    if (A.x != B.x)
    {
        C = (A.y-B.y, B.x-A.x);

        x = P.x - C.x*P.y/C.y;
        Q = (x, 0.0);
        dist = EuclideanNorm2D(Q - A);

        return Q + scale(dist)*(cos(t), sin(t));
    }
    else
        return scale(1-t)*A + scale(t)*B;
}

pair HyperbolicCirclePoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x1, y1, x0, y, m, dist;

    pair center;

    x1 = B.x;
    y1 = B.y;

    x0 = A.x;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x + c2)*(A.x + c2);

        m = -(x1 + c2)/sqrt(c1 - (x1+c2)*(x1+c2));

        y = y1 + m*(x0-x1);
        center = (x0, y);

        dist = EuclideanNorm2D(center - B);

        return center + scale(dist)*(cos(t), sin(t));
    }
    else
        return A;
}
