// Boilerplate stuff.
import settings;
import three;
import graph3;

settings.render=8;


currentprojection=perspective(camera = (100, 20, -30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(128);

// Radius of the dot and pipes.
real dotR = 0.08;
int samples = 40;

triple f(pair t)
{
    real u = 2.0*pi*t.x;
    real v = pi*t.y;
    real cosu = cos(u);
    real sinu = sin(u);
    real cosv = cos(v);
    real sinv = sin(v);

    real x = cosu*sinv;
    real y = sinu*sinv;
    real z = cosv;
    return (x, y, z);
}

triple path(real t, pair A, pair B)
{
    return f(scale(1.0 - t)*A + scale(t)*B);
}

pair V0 = (0.0, 0.5);
pair V1 = V0 + scale(0.13)*expi(0.0);
pair V2 = V0 + scale(0.2)*expi(2.0*pi / 3.0);
pair V3 = V0 + scale(0.2)*expi(4.0*pi / 3.0);

triple c0(real t)
{
    return path(t, V0, V1);
}

triple c1(real t)
{
    return path(t, V0, V2);
}

triple c2(real t)
{
    return path(t, V0, V3);
}

triple c3(real t)
{
    return path(t, V1, V2);
}

triple c4(real t)
{
    return path(t, V1, V3);
}

triple c5(real t)
{
    return path(t, V2, V3);
}

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

draw(unitsphere, surfacepen=blob, render(merge=true));
draw(graph(c0, 0.0, 1.0, samples));
draw(graph(c1, 0.0, 1.0, samples));
draw(graph(c2, 0.0, 1.0, samples));
draw(graph(c3, 0.0, 1.0, samples));
draw(graph(c4, 0.0, 1.0, samples));
draw(graph(c5, 0.0, 1.0, samples));

surface s = scale(dotR, dotR, dotR)*unitsphere;
draw(shift(f(V0))*s, surfacepen=orb, render(merge=true));
draw(shift(f(V1))*s, surfacepen=orb, render(merge=true));
draw(shift(f(V2))*s, surfacepen=orb, render(merge=true));
draw(shift(f(V3))*s, surfacepen=orb, render(merge=true));
