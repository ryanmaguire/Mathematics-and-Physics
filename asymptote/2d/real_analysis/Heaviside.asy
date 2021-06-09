import graph;
import settings;
outformat="pdf";

size(300);

// Size of the arrow heads.
real arsize = 5bp;

pen pens = deepblue+1;

// Variables for the plot.
int i;
real xmin = -1.6;
real xmax = +1.6;
real ymin = -0.0;
real ymax = +1.2;

// Function.
real[] x1 = {-1.5, 0.0};
real[] y1 = {+0.0, 0.0};
real[] x2 = {+0.0, 1.5};
real[] y2 = {+1.0, 1.0};

// Draw the x axis.
label("$x$", (xmax, 0.0),  S);
draw((xmin, 0) -- (xmax, 0), BeginArrow(arsize), EndArrow(arsize));
for (i=-4*(int)xmax-1; i<=4*(int)xmax+1; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, 0-0.1));
    }
    else draw((i/4, 0) -- (i/4, 0-0.05));
}
label("$-1$", (-1, -0.2), fontsize(9pt));
label("$1$",  (+1, -0.2), fontsize(9pt));

// Draw the y axis.
label("$y$", (0.0,  ymax), W);
draw((0, ymin) -- (0, ymax), arrow=Arrow());
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2) -- (-0.1, i/2));
    }
    else draw((0, i/2) -- (-0.05, i/2));
}
label("$1$", (-0.2, 1), fontsize(9pt));

// Plot the function.
draw(graph(x1, y1), pens);
draw(graph(x2, y2), pens);

// Draw circles for the jump in the function.
draw((0,0)--(0,1), pens+linetype("4 4"));
fill(    circle((0, 1), 0.03), pens);
filldraw(circle((0, 0), 0.03), white, pens);

// Origin.
labelx("$O$", 0, SW);