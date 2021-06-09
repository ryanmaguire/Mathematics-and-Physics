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
size(320);

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
int shift = 16;

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

// Create the background grid.
for (i = 0; i <= nx+shift; ++i){
    x = (real)i;
    draw((x, -0.5)--(x, ny+0.5), graypen);
}

for (i = 0; i<= nx; ++i){
    label("$"+string(i)+"$", (i, -0.7), fontsize(7pt));
    label("$"+string(i)+"$", (i+shift, -0.7), fontsize(7pt));
}

for (i = 0; i <= ny; ++i){
    y = (real)i;
    draw((-0.5, y)--(nx+shift+0.5, y), graypen);
    label("$"+string(i)+"$", (-0.7, i), fontsize(7pt));
}

// Fill in the shapes with color.
filldraw(A1--A2--A3--cycle, Afill, outlinepen);
filldraw(B1--B2--B3--cycle, Bfill, outlinepen);
filldraw(C1--C2--C3--C4--C5--C6--cycle, Cfill, outlinepen);
filldraw(D1--D2--D3--D4--D5--D6--cycle, Dfill, outlinepen);


// The bigger triangle.
pair A1 = (shift+5.0,  2.0);
pair A2 = (shift+13.0, 2.0);
pair A3 = (shift+13.0, 5.0);

// Smaller triangle.
pair B1 = (shift+0.0, 0.0);
pair B2 = (shift+5.0, 0.0);
pair B3 = A1;

// Tetris piece to the right of the smaller triangle.
pair C1 = B2;
pair C2 = B3;
pair C3 = (shift+10.0, 2.0);
pair C4 = (shift+10.0, 1.0);
pair C5 = (shift+7.0,  1.0);
pair C6 = (shift+7.0,  0.0);

// Tetris piece below bigger triangle.
pair D1 = (shift+8.0, 0.0);
pair D2 = (shift+13.0, 0.0);
pair D3 = (shift+13.0, 2.0);
pair D4 = (shift+10.0, 2.0);
pair D5 = (shift+10.0, 1.0);
pair D6 = (shift+8.0,  1.0);

// Fill in the shapes with color.
filldraw(A1--A2--A3--cycle, Afill, outlinepen);
filldraw(B1--B2--B3--cycle, Bfill, outlinepen);
filldraw(C1--C2--C3--C4--C5--C6--cycle, Cfill, outlinepen);
filldraw(D1--D2--D3--D4--D5--D6--cycle, Dfill, outlinepen);
