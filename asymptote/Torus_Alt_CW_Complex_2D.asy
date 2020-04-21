// Seting output format to "pdf".
import settings;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

defaultpen(black+linewidth(0.5pt));

// Size of the output figure.
size(64);

real arsize = 5bp;
position pos1 = 0.5;
position pos2 = 0.6;

pair A = (0.0, 1.0);
pair B = (1.0, 1.0);
pair C = (1.0, 0.0);
pair D = (0.0, 0.0);

filldraw(A--B--D--cycle, gray(0.3)+opacity(0.5), nullpen);
filldraw(B--D--C--cycle, gray(0.7)+opacity(0.5), nullpen);

draw(A--B, MidArrow(arsize));
draw(D--C, MidArrow(arsize));

draw(A--D, Arrow(arsize, pos1), Arrow(arsize, pos2));
draw(B--C, Arrow(arsize, pos1), Arrow(arsize, pos2));

draw(D--B, linetype("4 4"));
