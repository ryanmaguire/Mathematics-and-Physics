// Boilerplate stuff.
import settings;
import graph3;
settings.outformat="pdf";
settings.render=4;

currentprojection = perspective(
    camera = (20, 60, 20),
    up = (0, 0, 1),
    target = (0,  0,  0),
    zoom = 1.0
);

// Size of the output figure.
size(200);

// Arrow size.
real arsize = 5bp;

// Label for the axes.
Label L;

// Function to return homotopy between x^3 and exp(x).
triple f(pair t) {
    real x = t.x;
    real z = t.y;
    real y = z*(x^3)+(1-z)*exp(x);
    return (x, y, z);
}

// Create the surface.
surface s=surface(f, (0, 0), (1, 1), 100, 100, Spline);

material blob = material(diffusepen=blue+0.3*lightgreen+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.1));

// Draw axes.
L = Label("$x$", position=1.0);
draw(L, (0.0, 0.0, 0.0)---(1.2, 0.0, 0.0), S, black, Arrow3(arsize));
draw(L, (0.0, 0.0, 1.0)---(1.2, 0.0, 1.0), S, black, Arrow3(arsize));

L = Label("$y$", position=1.0);
draw(L, (0.0, 0.0, 0.0)---(0.0, 3.0, 0.0), S, black, Arrow3(arsize));
draw(L, (0.0, 0.0, 1.0)---(0.0, 3.0, 1.0), S, black, Arrow3(arsize));

L = Label("$t$", position=1.0);
draw(L, (0.0, 0.0, 0.0)---(0.0, 0.0, 1.2), W, black, Arrow3(arsize));

// Draw the Gaussian surface.
draw(s, surfacepen=blob, render(merge=true));

// Create a mesh for the surface and draw it.
s=surface(f, (0, 0), (1, 1), 20, 20, Spline);
draw(s, opacity(0.0), meshpen=black+thick(), render(merge=true));
