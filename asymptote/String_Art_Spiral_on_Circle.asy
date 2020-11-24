/*  Set up the format of the figure.                                          */
import settings;
settings.outformat = "pdf";


/* Size of the output figure.                                                 */
size(256);

/*  Number of points along the circle.                                        */
int N_Points = 1000;

/*  Number of points to skip for a and b.                                     */
int a_skip = 4;
int b_skip = 3;

/*  ints to correspond to the current points on the circle.                   */
int a, b;

/*  The starting values for a and b. Set them with angles 0 and pi.           */
a = 0;
b = (int)(N_Points / 2);

/*  Loop over a and b and stop once the two values correspond to the same     *
 *  point on the circle. This occurs when a-b = 0 mod N_Points.               */
while ((a-b) % N_Points != 0)
{
    draw(expi(2*pi*a/N_Points) -- expi(2*pi*b/N_Points));
    a += a_skip;
    b += b_skip;
}

/*  Draw the outline of the circle.                                           */
draw(circle((0, 0), 1));
