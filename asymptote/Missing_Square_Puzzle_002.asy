// Seting output format to "pdf".
import settings;
import graph;
import _custom_arrows;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

defaultpen(fontsize(7pt));

// Size of the output figure.
size(256);

// Pens used throughout the drawing.
pen graypen = gray(0.7)+linewidth(0.4pt);
pen outlinepen = deepblue + linewidth(0.8pt);
pen Afill = green+opacity(0.8);
pen Bfill = red+opacity(0.8);
pen Cfill = cyan+opacity(0.8);
pen Dfill = yellow+opacity(0.8);

// Variables used for making the grid.
int i;
int nx = 13;
int ny = 5;

real x, y;

// The bigger triangle.
pair A1 = (0.0, 0.0);
pair A2 = (8.0, 0.0);
pair A3 = (8.0, 3.0);

// Smaller triangle.
pair B1 = A3;
pair B2 = (13.0, 3.0);
pair B3 = (13.0, 5.0);

// Top tetris piece below smaller triangle.
pair C1 = A3;
pair C2 = B2;
pair C3 = (13.0, 2.0);
pair C4 = (10.0, 2.0);
pair C5 = (10.0, 1.0);
pair C6 = (8.0, 1.0);

// Bottom tetris piece below smaller triangle.
pair D1 = A2;
pair D2 = (13.0, 0.0);
pair D3 = C3;
pair D4 = C4;
pair D5 = C5;
pair D6 = C6;

// The missing piece.
pair E1 = A1;
pair E2 = A3;
pair E3 = B3;
pair E4 = (5.0, 2.0);

// Create the background grid.
for (i = 0; i <= nx; ++i){
    x = (real)i;
    draw((x, -0.5)--(x, ny+0.5), graypen);
}

for (i = 0; i <= ny; ++i){
    y = (real)i;
    draw((-0.5, y)--(nx+0.5, y), graypen);
}

// Fill in the shapes with color.
filldraw(A1--A2--A3--cycle, Afill, outlinepen);
filldraw(B1--B2--B3--cycle, Bfill, outlinepen);
filldraw(C1--C2--C3--C4--C5--C6--cycle, Cfill, outlinepen);
filldraw(D1--D2--D3--D4--D5--D6--cycle, Dfill, outlinepen);
filldraw(E1--E2--E3--E4--cycle, black);
