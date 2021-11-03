import graph3;
import tube;

size(256, 256);

// Camera and light setups.
currentprojection=perspective(camera = (0, 0, 100), up   = (0, 0, 1),
                              target = (0, 0, 0),   zoom = 0.85);

currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material bluepipe = material(
    diffusepen=blue+0.3*green,
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

real angle1 = 30*pi/180;
real angle2 = 2pi-angle1;
real dr = pi/4;
real scalefact = 0.2;

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

real scalefunc(real u, real shift){
    return DoubleCutoff(u, angle1, angle1+dr, angle2-dr, angle2)+shift;
}

triple f(real t){
    return scalefunc(t, scalefact)*TrefoilEquation(t);
}

path3 p=graph(f, 0, 2pi, n=300, operator ..);
draw(tube(p, scale(0.15)*unitcircle), surfacepen=bluepipe, light=currentlight);
