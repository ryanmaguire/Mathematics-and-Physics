
import graph3;
import settings;
settings.render = 8;

size(256);

currentprojection=perspective(5.0, 4.0, 4.0);

/*  Two radii defining the torus.                                             */
real R = 3.0;
real a = 1.0;

/*  Number of samples in the merge region between the two torii.              */
int xsamples = 20;
int ysamples = 40;

/*  Start and end parameters for the merge region.                            */
pair start = (-R - a, -2.0);
pair end = (-R, 2.0);

/*  Material the 2-genus surface is made out of.                              */
material blob = material(
    diffusepen=gray(0.7),
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

/*  Function for drawing the torus.                                           */
triple torus_parameterization(pair t)
{
    real u = 2.0*pi*t.x;
    real v = 2.0*pi*t.y;
    real cosu = cos(u);
    real cosv = cos(v);
    real sinu = sin(u);
    real sinv = sin(v);

    real x = (R + a*cosv)*cosu;
    real y = (R + a*cosv)*sinu;
    real z = a*sinv;

    triple out = (x, y, z);
    return out;
}

/*  First function for merging the two torii.                                 */
triple f(pair P)
{
    triple out;
    real x_plus_R = P.x + R;
    real a_plus_R = a + R;

    /*  The x and y values are the same for all cases.                        */
    real x = P.x + 0.5*x_plus_R*x_plus_R/a;
    real y = sin(0.5*pi*P.y) * sqrt(a_plus_R*a_plus_R - x*x);

    /*  This factor is used for the z part.                                   */
    real factor = R - sqrt(x*x + y*y);

    /*  The z part only differes in sign, depending on the value of P.y       */
    real z = sqrt(a*a - factor*factor);

    if (fabs(P.y) >= 1.0)
        out = (-P.x, y, -z);
    else
        out = (-P.x, y, z);

    return out;
}

/*  Second function for merging the two torii.                                */
triple g(pair P)
{
    triple out;
    real x_plus_R = P.x + R;
    real a_plus_R = a + R;

    /*  The x and y values are the same for all cases.                        */
    real x = P.x + 0.5*x_plus_R*x_plus_R/a;
    real y = sin(0.5*pi*P.y) * sqrt(a_plus_R*a_plus_R - x*x);

    /*  This factor is used for the z part.                                   */
    real factor = R - sqrt(x*x + y*y);

    /*  The z part only differes in sign, depending on the value of P.y       */
    real z = sqrt(a*a - factor*factor);

    if (fabs(P.y) >= 1.0)
        out = (P.x, y, -z);
    else
        out = (P.x, y, z);

    return shift((2.0*(R + a), 0.0, 0.0))*out;
}

surface t0 = surface(torus_parameterization, (0.0, 0.0), (1.0, 1.0), Spline);
surface t1 = shift((2.0*(R + a), 0.0, 0.0))*t0;
surface merge0 = surface(f, start, end, xsamples, ysamples, Spline);
surface merge1 = surface(g, start, end, xsamples, ysamples, Spline);

draw(t0, surfacepen = blob, render(merge=true));
draw(t1, surfacepen = blob, render(merge=true));
draw(merge0, surfacepen = blob, render(merge=true));
draw(merge1, surfacepen = blob, render(merge=true));
