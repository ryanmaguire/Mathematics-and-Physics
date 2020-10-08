import _euclidean;

pair InverseCurve(pair f(real), real t)
{
    /*  Declare necessary variables.                                          */
    real X, Y, Px, Py, normsq;
    pair P, invP;

    /*  Compute the point from the given function f and the value t.          */
    P = f(t);

    /*  If P is the origin, the inverse of it is the point "at infinity" so   *
     *  we'll return the pair (inf, inf).                                     */
    normsq = EuclideanNorm2D(P);
    if (normsq == 0.0)
        return (inf, inf);

    /*  Otherwise, square the current value to get normsq.                    */
    else
        normsq = normsq*normsq;

    /*  Extract the x and y values from P.                                    */
    Px = P.x;
    Py = P.y;

    /*  Compute the inverse X and Y values with respect to the unit circle.   */
    X = Px/normsq;
    Y = Py/normsq;

    /*  The inverse of P is just (X, Y) so compute this and return.           */
    invP = (X, Y);
    return invP;
}