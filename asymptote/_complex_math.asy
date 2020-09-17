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
