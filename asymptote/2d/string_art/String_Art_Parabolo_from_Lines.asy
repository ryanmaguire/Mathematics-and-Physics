/*  Set up the format of the figure.                                          */
import settings;
settings.outformat = "pdf";

/* Size of the output figure.                                                 */
size(256);

/*  Number of points along the circle.                                        */
int N_Points = 100;

pair a, b;
pair X0, X1;
pair O;
real t;
real dt;

int n;

O = (0, 0);
X0 = (-1, 1);
X1 = (1, 1);

dt = 1.0/N_Points;

draw(O--X0);
draw(O--X1);

for (n=0; n<N_Points; ++n)
{
    a = scale(t)*X0;
    b = scale(1-t)*X1;

    draw(a--b);
    t += dt;
}
