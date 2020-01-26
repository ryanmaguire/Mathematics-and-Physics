import graph;
import settings;
outformat="pdf";

size(300,300);

// Function.
real[] x1 = {-1.5,0};
real[] y1 = {0,0};
real[] x2 = {0,1.5};
real[] y2 = {1,1};
draw(graph(x1,y1),red+2);
draw(graph(x2,y2),red+2);

draw((0,0)--(0,1),red+1.5+linetype("4 4"));
fill( circle((0,1),0.035), red);
filldraw( circle((0,0),0.03), white, red+1.5);

// Axes.
xaxis( Label("$x$"), Ticks(new real[]{-1,-0.5,0.5,1}), Arrow);
yaxis( Label("$y$"), Ticks(new real[]{0.5,1}), Arrow, ymin=-0.18, ymax=1.25);
// Origin.
labelx("$O$",0,SW);