// Seting output format to "pdf".
import settings;
import graph;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

defaultpen(black+linewidth(0.4pt)+fontsize(7pt));

// Size of the output figure.
size(256);

int i;
int n = 8;
int di = 2;
path g;

pair O1 = (0, 0);
pair O2 = (0, 2);
pair A1 = (n, 0);
pair A2 = (n, 2);

pair midpoint(pair A, pair B){
    return scale(0.5)*(A+B);
}

draw(O1--A1);
draw(O2--A2);
draw(ellipse(midpoint(O1, O2), 0.5, 1.0), linetype("4 4"));
draw(ellipse(midpoint(A1, A2), 0.5, 1.0), linetype("4 4"));


// Add a donut hole in the manifold.
for (i=2; i<n; i+=di){
    g = (-0.75, 0.1){dir(-50)}..{dir(50)}(0.75, 0.1);
    draw(shift(i, 1)*g);

    g = (-0.65, 0.0){dir(50)}..{dir(-50)}(0.65, 0.0);
    draw(shift(i, 1)*g);
}