// Boilerplate stuff.
import settings;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
settings.prc=false;
viewportmargin=(2, 2);

// Size of the output figure.
size(64);

// Pen for the two 1-cells.
pen rpen = red+linewidth(0.8pt);
pen bpen = blue+linewidth(0.8pt);

// Radius for the dots.
real rdot = 0.04;

// Radius of the circle.
real R = 1.0;

draw(arc((0, 0), R, 0, 180), bpen);
draw(arc((0, 0), R, 180, 360), rpen);
filldraw(circle((R,0), rdot), black);
filldraw(circle((-R,0), rdot), black);
