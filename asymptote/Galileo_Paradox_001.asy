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

pair midpoint(pair A, pair B){return scale(0.5)*(A+B);}

// Default pen for drawing.
defaultpen(black+linewidth(0.4pt));

// Size of the output figure.
size(128);

draw((-1.0,  0.0)--(1.0,  0.0));
draw((-0.5, -0.5)--(0.5, -0.5));