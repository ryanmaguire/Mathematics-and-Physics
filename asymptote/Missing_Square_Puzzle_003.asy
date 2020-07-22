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
size(200);

// Pens used throughout the drawing.
pen graypen = gray(0.7)+linewidth(0.4pt);
pen outlinepen = deepblue + linewidth(0.8pt);
pen Afill = green+opacity(0.7);
pen Bfill = red+opacity(0.8);

// Variables used for making the grid.
int i;
int nx = 8;
int ny = 3;

real x, y;

// The bigger triangle.
pair A1 = (0.0, 0.0);
pair A2 = (8.0, 0.0);
pair A3 = (8.0, 3.0);

// Smaller triangle.
pair B1 = A1;
pair B2 = (5.0, 0.0);
pair B3 = (5.0, 2.0);

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
