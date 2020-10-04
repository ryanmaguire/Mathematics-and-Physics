// Boilerplate stuff.
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Pen used to draw things.
defaultpen(linewidth(0.4pt));

// Size of output.
size(256);

// Pairs of points to draw arrows between.
pair O = (0, 0);
pair X = (1, 0);

// Path for the arrow.
path g = O--X;

// Size of arrowhead.
real arsize = 5bp;

// Displacements used to shift the path.
real dy = -0.5;
real dx =  1.5;

// Loop through sharp plain arrow.
draw(shift(0*dx, 0*dy)*g, black, SharpArrow(arsize));
draw(shift(0*dx, 1*dy)*g, black, EndSharpArrow(arsize));
draw(shift(0*dx, 2*dy)*g, black, MidSharpArrow(arsize));
draw(shift(0*dx, 3*dy)*g, black, SharpArrows(arsize));
draw(shift(0*dx, 4*dy)*g, black, BeginSharpArrow(arsize));

// Loop through sharp dashed arrow.
draw(shift(1*dx, 0*dy)*g, black+dashed, SharpArrow(arsize));
draw(shift(1*dx, 1*dy)*g, black+dashed, EndSharpArrow(arsize));
draw(shift(1*dx, 2*dy)*g, black+dashed, MidSharpArrow(arsize));
draw(shift(1*dx, 3*dy)*g, black+dashed, SharpArrows(arsize));
draw(shift(1*dx, 4*dy)*g, black+dashed, BeginSharpArrow(arsize));

// Loop through plain stealth arrow.
draw(shift(2*dx, 0*dy)*g, black, SharpArrow(StealthHead, arsize));
draw(shift(2*dx, 1*dy)*g, black, EndSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 2*dy)*g, black, MidSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 3*dy)*g, black, SharpArrows(StealthHead, arsize));
draw(shift(2*dx, 4*dy)*g, black, BeginSharpArrow(StealthHead, arsize));

// Loop through dashed stealth arrow.
draw(shift(3*dx, 0*dy)*g, black+dashed, SharpArrow(StealthHead, arsize));
draw(shift(3*dx, 1*dy)*g, black+dashed, EndSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 2*dy)*g, black+dashed, MidSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 3*dy)*g, black+dashed, SharpArrows(StealthHead, arsize));
draw(shift(3*dx, 4*dy)*g, black+dashed, BeginSharpArrow(StealthHead, arsize));
