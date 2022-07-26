// Seting output format to "pdf".
import settings;
settings.outformat = "pdf";

// Size of the output figure.
size(128);

// Size of the arrowhead.
real arsize = 5bp;

// Points for the square.
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (1.0, 1.0);
pair D = (0.0, 1.0);

transform T1 = shift(1.0, 0.0);
transform T2 = shift(0.0, -1.0);
transform T3 = shift(1.0, -1.0);

position pos1 = 0.47;
position pos2 = 0.57;

draw("$a$", A--B, N, MidArrow(arsize));
draw("$a$", C--D, S, MidArrow(arsize));
draw("$b$", B--C, Arrow(arsize, pos1), Arrow(arsize, pos2));
draw("$b$", D--A, E, Arrow(arsize, pos1), Arrow(arsize, pos2));

draw("$a$", T1*B--T1*A, MidArrow(arsize));
draw("$a$", T1*D--T1*C, MidArrow(arsize));
draw("$b$", T1*C--T1*B, Arrow(arsize, pos1), Arrow(arsize, pos2));

draw("$a$", T2*B--T2*A, MidArrow(arsize));
draw("$b$", T2*C--T2*B, Arrow(arsize, pos1), Arrow(arsize, pos2));
draw("$b$", T2*A--T2*D, Arrow(arsize, pos1), Arrow(arsize, pos2));

draw("$a$", T3*A--T3*B, N, MidArrow(arsize));
draw("$b$", T3*B--T3*C, W, Arrow(arsize, pos1), Arrow(arsize, pos2));
