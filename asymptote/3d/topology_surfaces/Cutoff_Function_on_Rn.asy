/*  Boilerplate stuff.                                                        */
import graph3;
import palette;
import settings;
settings.outformat="pdf";
settings.render=8;

/*  Size of the output figure.                                                */
size(512);

/*  Camera angle.                                                             */
currentprojection=perspective(10, 8, 4);

/*  Arrow size.                                                               */
real arsize = 5bp;

real r1 = 1.0;
real r2 = 1.5;

/*  Real valued bump function.                                                */
real f(real t)
{
    if (t <= 0.0)
        return 0.0;
    else
        return exp(-1.0/t);
}

real g(real t)
{
    real a, b;
    a = f(r2-t);
    b = f(t-r1);

    return a/(a+b);
}

triple h(pair z)
{
    real r = z.x;
    real theta = z.y;

    real x = r*cos(theta);
    real y = r*sin(theta);
    return (x, y, g(r));
}

/*  Create the Gaussian surface.                                              */
surface s=surface(h, (0, 0), (2, 2pi), 50, 50, Spline);

/*  Draw axes.                                                                */
xaxis3(Label("$x$"), 0, 2.3, black, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 2.3, black, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 1.8, black, Arrow3(arsize));

/*  Draw the surface.                                                         */
draw(s, lightgray, nolight, meshpen=black+linewidth(0.5pt), render(merge=true));
