// Seting output format to "pdf".
import graph;

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

position pos1 = 0.47;
position pos2 = 0.57;

draw("$a$", A--B, MidArrow(arsize));
draw("$a$", C--D, MidArrow(arsize));
draw("$b$", C--B, Arrow(arsize, pos1), Arrow(arsize, pos2));
draw("$b$", D--A, Arrow(arsize, pos1), Arrow(arsize, pos2));
