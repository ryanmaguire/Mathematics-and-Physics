/*  Set up the format of the figure.                                          */
import settings;
settings.outformat = "pdf";

/* Size of the output figure.                                                 */
size(256);

/*  Number of points for each parabola.                                       */
int N_Points = 100;

/*  Variable for indexing.                                                    */
int n;

/*  Variables for drawing the lines.                                          */
pair a, b;

/*  Create variables for the three vertices of the triangle.                  */
pair X0 = (-1, 0.0);
pair X1 = (1, 0.0);
pair X2 = (0.0, sqrt(3.0));

/*  We'll use these variables for parameterizing the edges of the triangle.   */
real t;
real dt = 1.0/N_Points;

/*  Draw the outline of the triangle.                                         */
draw(X0--X1--X2--cycle);

/*  Loop over the points and draw in the trefoil.                             */
for (n=0; n<N_Points; ++n)
{
    a = scale(t)*X0 + scale(1-t)*X1;
    b = scale(t)*X1 + scale(1-t)*X2;
    draw(a--b);

    a = scale(t)*X1 + scale(1-t)*X2;
    b = scale(t)*X2 + scale(1-t)*X0;
    draw(a--b);

    a = scale(t)*X2 + scale(1-t)*X0;
    b = scale(t)*X0 + scale(1-t)*X1;
    draw(a--b);

    /*  Increment t to the next point.                                        */
    t += dt;
}
