// Make sure _asy_preamble_2d.asy and _euc_geo_2d.asy are in your ASYMPTOTE_DIR
// environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _euc_geo_2d;
import graph;

// Size of the output figure.
size(256);

real start = -0.2;
real end   =  1.3;
real angle_length = 0.2;

int samples = 3;

pair A = (0.0, 1.0);
pair B = (0.0, 0.0);
pair C = (4.0, 0.2);

real angle1 = RelAngleTwo(A, B, C);
real angle2 = RelAngleTwo(B, A, C);

pair f1(real t){return scale(1-t)*A+scale(t)*C;}
pair f2(real t){return scale(1-t)*B+scale(t)*C;}

draw(graph(f1, start, end, n=samples));
draw(graph(f2, start, end, n=samples));

draw(A--B);
draw(arc(A, angle_length, 270, 270+180*angle1/pi));
draw(arc(B, angle_length, 90,  90-180*angle2/pi));

filldraw(circle(A, rDot));
filldraw(circle(B, rDot));
filldraw(circle(C, rDot));
label("$A$", A, NE, labelp);
label("$B$", B, SE, labelp);
label("$C$", C, N,  labelp);