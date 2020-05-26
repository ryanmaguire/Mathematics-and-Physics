// Boilerplate stuff.
import settings;

// Make sure _custom_arrows.asy is in your ASYMPTOTE_DIR environment variable.
// This file is found in the asymptote/ folder.
import _custom_arrows;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Default pen for drawing.
defaultpen(black+linewidth(0.5pt));

// Size of the output figure.
size(256);

// Needed for the use of mathbb and mathcal commands.
texpreamble('\usepackage{amssymb}');
texpreamble('\DeclareMathSymbol{\minus}{\mathbin}{AMSa}{"39}');

// Size of the arrow head.
real arsize = 5bp;

// Used for drawing paths.
path g;

// Pen for curves and dashes.
pen cpen = black+linewidth(0.5pt);
pen dpen = black+linewidth(0.2pt)+dashed;

real xshift = 3;
real yshift = 4.5;

draw((-1,  0)--(3, 0), SharpArrow(arsize));
draw(( 0, -1)--(0, 3), SharpArrow(arsize));
g = (0.5, 1.5){dir(30)} ..(1.2,  1.9){dir(0)}  ..(1.9,  1.4)
              {dir(-90)}..(1.4,  0.2){dir(180)}..(0.4,  0.3){dir(150)}..cycle;
filldraw(g, red+opacity(0.5), dpen);

label("$\mathbb{R}^{n}$", (0.5, 3.0));
label("$\varphi^{\minus{1}}[\mathcal{U}]$", (1.1, 1.0));

g = (1.3, 2){dir(90)}..{dir(0)}(4.7, 4.2);
draw("$\varphi$", g, NW, cpen, BeginSharpArrow(arsize));

g = (0,0){dir(90)} ..(1,  1.0){dir(0)}  ..(2,  1.0){dir(-30)}..(4,  0.0)
         {dir(-90)}..(2, -2.5){dir(180)}..(0, -2.5){dir(150)}..cycle;
draw(shift(xshift, yshift)*g);

        
draw(shift(xshift, yshift)*((0.5, -1.7){dir(310)}..{dir(50)}(1.8, -1.7)));
draw(shift(xshift, yshift)*((0.6, -1.8){dir(50)} ..{dir(310)}(1.7, -1.8)));

g = (2.0, 0.0) {dir(30) }..(2.7,  0.5){dir(0)  }..(3.5,  0.0)
               {dir(-90)}..(3.2, -0.9){dir(180)}..(2.2, -0.8){dir(150)}..cycle;

filldraw(shift(xshift, yshift)*g, blue+opacity(0.5), dpen);

label("$\mathcal{U}$", shift(xshift, yshift)*(2.8, -0.2));
label("$X$",           shift(xshift, yshift)*(1.0,  0.6));

g = (6, 0)--(10, 0);
draw(Label("$\mathbb{R}$", position=1.0), g, N, SharpArrows(arsize));

g = (6.7, 4.2){dir(0)}..{dir(270)}(8.0, 0.2);
draw("$f$", g, E, cpen, SharpArrow(arsize));

draw(arc((9-0.5, 0), 0.5, -15, 15), blue+1);
draw(arc((7+0.5, 0), 0.5, 165, 195), blue+1);
draw((7,0)--(9, 0), blue+1);

g = (1.2, -0.2){dir(-30)}..{dir(30)}(7.8, -0.2);
draw("$f\circ\varphi^{\minus{1}}$", g, N, cpen, SharpArrow(arsize));