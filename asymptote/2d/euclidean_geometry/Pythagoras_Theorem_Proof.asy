// Seting output format to "pdf".
import settings;
import graph;
import _euclidean;

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
size(256);

defaultpen(fontsize(9pt));

// Shift for the second block.
real shift = 9.0;

// Pens used throughout the drawing.
pen outlinepen = deepblue + linewidth(0.8pt);
pen Afill = green+opacity(0.8);
pen Bfill = red+opacity(0.8);
pen Cfill = cyan+opacity(0.8);
pen Dfill = yellow+opacity(0.8);

pair A1 = (0.0, 3.0);
pair A2 = (0.0, 7.0);
pair A3 = (3.0, 7.0);

pair B1 = (4.0, 0.0);
pair B2 = (0.0, 0.0);
pair B3 = (0.0, 3.0);

pair C1 = (7.0, 4.0);
pair C2 = (7.0, 0.0);
pair C3 = (4.0, 0.0);

pair D1 = (3.0, 7.0);
pair D2 = (7.0, 7.0);
pair D3 = (7.0, 4.0);

// Fill in the shapes with color.
filldraw(A1--A2--A3--cycle, Afill, outlinepen);
filldraw(B1--B2--B3--cycle, Bfill, outlinepen);
filldraw(C1--C2--C3--cycle, Cfill, outlinepen);
filldraw(D1--D2--D3--cycle, Dfill, outlinepen);

filldraw(A1--B1--C1--D1--cycle, gray(0.7)+opacity(0.3), outlinepen);

label("$a$", MidPoint2D(A1, A2), E);
label("$b$", MidPoint2D(A2, A3), S);
label("$c$", MidPoint2D(A3, A1), NW);

label("$a$", MidPoint2D(B1, B2), N);
label("$b$", MidPoint2D(B2, B3), E);
label("$c$", MidPoint2D(B3, B1), SW);

label("$a$", MidPoint2D(C1, C2), E);
label("$b$", MidPoint2D(C2, C3), N);
label("$c$", MidPoint2D(C3, C1), SE);

label("$a$", MidPoint2D(D1, D2), S);
label("$b$", MidPoint2D(D2, D3), W);
label("$c$", MidPoint2D(D3, D1), NE);

label("$c^{2}$", (3.5, 3.5), fontsize(12pt));

pair A1 = (shift+0.0, 3.0);
pair A2 = (shift+0.0, 7.0);
pair A3 = (shift+3.0, 7.0);

pair B1 = (shift+3.0, 7.0);
pair B2 = (shift+3.0, 3.0);
pair B3 = (shift+0.0, 3.0);

pair C1 = (shift+7.0, 0.0);
pair C2 = (shift+3.0, 0.0);
pair C3 = (shift+3.0, 3.0);

pair D1 = (shift+3.0, 3.0);
pair D2 = (shift+7.0, 3.0);
pair D3 = (shift+7.0, 0.0);

filldraw(A1--A2--A3--cycle, Afill, outlinepen);
filldraw(B1--B2--B3--cycle, Bfill, outlinepen);
filldraw(C1--C2--C3--cycle, Cfill, outlinepen);
filldraw(D1--D2--D3--cycle, Dfill, outlinepen);

label("$a$", MidPoint2D(A1, A2), E);
label("$b$", MidPoint2D(A2, A3), S);
label("$c$", MidPoint2D(A3, A1), SE);

label("$a$", MidPoint2D(B1, B2), W);
label("$b$", MidPoint2D(B2, B3), N);
label("$c$", MidPoint2D(B3, B1), NW);

label("$a$", MidPoint2D(C1, C2), N);
label("$b$", MidPoint2D(C2, C3), E);
label("$c$", MidPoint2D(C3, C1), SW);

label("$a$", MidPoint2D(D1, D2), S);
label("$b$", MidPoint2D(D2, D3), W);
label("$c$", MidPoint2D(D3, D1), NE);

pair A1 = (shift+0.0, 0.0);
pair A2 = (shift+7.0, 0.0);
pair A3 = (shift+7.0, 7.0);
pair A4 = (shift+0.0, 7.0);

draw(A1--A2--A3--A4--cycle, outlinepen);
filldraw(B1--B2--D2--A3--cycle, gray(0.7)+opacity(0.3), outlinepen);
filldraw(B3--B2--C2--A1--cycle, gray(0.7)+opacity(0.3), outlinepen);

label("$a^{2}$", (shift+5.0, 5.0), fontsize(12pt));
label("$b^{2}$", (shift+1.5, 1.5), fontsize(12pt));

label("$a^{2}+b^{2}=c^{2}$", (0.5*(shift+7), -1.0), fontsize(14pt));

