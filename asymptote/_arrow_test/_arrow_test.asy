// Seting output format to "pdf".
import settings;
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Size of output.
size(300);

// Pairs of points to draw arrows between.
pair O = (0, 0);
pair X = (1, 0);

// Size of arrowhead.
real arsize = 5bp;

path g = O--X;

real dy = -0.5;
real dx =  1.5;

draw(shift(0*dx, 0*dy)*g, black, SharpArrow(arsize));
draw(shift(0*dx, 1*dy)*g, black, EndSharpArrow(arsize));
draw(shift(0*dx, 2*dy)*g, black, MidSharpArrow(arsize));
draw(shift(0*dx, 3*dy)*g, black, SharpArrows(arsize));
draw(shift(0*dx, 4*dy)*g, black, BeginSharpArrow(arsize));

draw(shift(1*dx, 0*dy)*g, black+dashed, SharpArrow(arsize));
draw(shift(1*dx, 1*dy)*g, black+dashed, EndSharpArrow(arsize));
draw(shift(1*dx, 2*dy)*g, black+dashed, MidSharpArrow(arsize));
draw(shift(1*dx, 3*dy)*g, black+dashed, SharpArrows(arsize));
draw(shift(1*dx, 4*dy)*g, black+dashed, BeginSharpArrow(arsize));

draw(shift(2*dx, 0*dy)*g, black, SharpArrow(StealthHead, arsize));
draw(shift(2*dx, 1*dy)*g, black, EndSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 2*dy)*g, black, MidSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 3*dy)*g, black, SharpArrows(StealthHead, arsize));
draw(shift(2*dx, 4*dy)*g, black, BeginSharpArrow(StealthHead, arsize));

draw(shift(3*dx, 0*dy)*g, black+dashed, SharpArrow(StealthHead, arsize));
draw(shift(3*dx, 1*dy)*g, black+dashed, EndSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 2*dy)*g, black+dashed, MidSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 3*dy)*g, black+dashed, SharpArrows(StealthHead, arsize));
draw(shift(3*dx, 4*dy)*g, black+dashed, BeginSharpArrow(StealthHead, arsize));
