import graph;
import settings;
outformat="pdf";

size(256, 256);

int i;
int samples = 128;
real start  = 0.05;
real end    = start+1.0;
real xmin   = -0.1;
real xmax   = 1.1;
real ymin   = -0.35;
real ymax   = 0.5;
real height = 0.4;
real x0, x1, y, mid;

real f(real x) {
    x = x-start;
    int i;
    real result = 0.0;
    for(i=1; i<9; ++i){
        result += sin((i*i*i*i)*x)/(2*i);
    }
    result *= x-0.5;
    return result-0.1;
};

path g=graph(f, start, end, n=samples);
draw(g, black);

for (i=0; i<6; ++i){
    if (i == 0){
        x0 = start;
        mid = x0;
    }
    else if (i == 1){
        x1 = end;
        mid = x1;
    }
    else {
        mid = (x0+x1)/2;
    }

    y = f(mid);
    if      (y<0)   x0 = mid;
    else if (y>0)   x1 = mid;
    else break;

    draw ((mid, height) -- (mid, y), dashed);
    dot((mid, y));
    label("$x_{" +string(i)+ "}$", (mid, height), N);
}

xaxis(Label("$x$"), Arrow, xmin=xmin, xmax=xmax);
yaxis(Label("$y$"), Arrow, ymin=ymin, ymax=ymax);