// Seting output format to "pdf".
import settings;
import graph;
import fontsize;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output figure.
size(100);

// Size of the arrowhead.
real arsize = 5bp;

// Points for the square.
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (1.0, 1.0);
pair D = (0.0, 1.0);

draw("$a$", A--B, MidArrow(arsize));
draw("$b$", B--C, MidArrow(arsize));
draw("$a$", C--D, MidArrow(arsize));
draw("$b$", D--A, MidArrow(arsize));
