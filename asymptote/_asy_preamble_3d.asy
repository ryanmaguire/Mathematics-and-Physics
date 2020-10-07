/*  Boilerplate stuff.                                                        */
import settings;
import graph3;

if(!settings.multipleView)
    settings.batchView=false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
viewportmargin = (2, 2);

/*  Commonly used materials in 3D drawing.                                    */
material blob, transparentblob, redpipe, bluepipe;

blob = material(diffusepen=gray(0.7),
                emissivepen=gray(0.2),
                specularpen=gray(0.2));

transparentblob = material(diffusepen=gray(0.7)+opacity(0.7),
                           emissivepen=gray(0.2),
                           specularpen=gray(0.2));

redpipe = material(diffusepen=red,
                   emissivepen=gray(0.2),
                   specularpen=gray(0.2));

bluepipe = material(diffusepen=blue+0.3*green,
                    emissivepen=gray(0.2),
                    specularpen=gray(0.2));

// Common objects.

// The equation for a torus centered at the origin with inner radius iR and
// outer radius oR. The pair t should lie in [0,2pi]x[0,2pi]
triple TorusEquation(pair t, real iR, real oR)
{
    return ((oR+iR*cos(t.y))*cos(t.x), (oR+iR*cos(t.y))*sin(t.x), iR*sin(t.y));
}

triple TrefoilEquation(real t)
{
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));
}

real BumpFunction(real t)
{
    if (t>0)
        return exp(-1.0/t);
    else
        return 0.0;
}

real CutOff(real t, real r1, real r2)
{
    assert(r2>r1);
    return BumpFunction(r2-t)/(BumpFunction(r2-t)+BumpFunction(t-r1));
}

real DoubleCutoff(real t, real r1, real r2, real r3, real r4)
{
    assert(r1<r2);
    assert(r2<r3);
    assert(r3<r4);
    real v1 = CutOff(t, r1, r2);
    real v2 = 1.0-CutOff(t, r3, r4);
    return v1+v2;
}
