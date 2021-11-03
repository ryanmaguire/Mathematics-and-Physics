// Seting output format to "pdf".
import settings;
settings.outformat = "pdf";

// Size of the output figure.
size(128);

// Pens used for drawing lines.
defaultpen(black+linewidth(0.3pt));

// Variable for indexing.
int i;

// The number of comb spikes to draw.
int n = 500;

// Draw the bottom and left of the comb.
draw((0, 0)--(1, 0));
draw((0, 1)--(0, 0));

// Draw all of the teeth.
for (i=1; i<=n; ++i) draw((1/i, 1)--(1/i, 0));
