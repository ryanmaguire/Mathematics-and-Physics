// Some boiler plate stuff.
import _custom_arrows;
import settings;
settings.render = 8;
outformat="pdf";

// Size of the output figure.
size(150);

// Variable for drawing the blobs.
path p;

// Pens used for drawing lines.
pen dpen = black+linewidth(0.3pt);

// Variable for indexing.
int i;

// The number of comb spikes to draw.
int n = 500;

// Coordinates for labelling the blobs.
p = (0, 0)--(1, 0);
draw(p, dpen);

for (i=1; i<=n; ++i){
    p = (1/i, 1)--(1/i, 0);
    draw(p, dpen);
}

p = (0, 1)--(0, 0);
draw(p, dpen);