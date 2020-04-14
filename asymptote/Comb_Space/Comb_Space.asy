// Seting output format to "pdf".
import settings;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output figure.
size(128);

// Pens used for drawing lines.
pen dpen = black+linewidth(0.3pt);

// Variable for indexing.
int i;

// The number of comb spikes to draw.
int n = 500;

// Draw the bottom and left of the comb.
draw((0, 0)--(1, 0), dpen);
draw((0, 1)--(0, 0), dpen);

// Draw all of the teeth.
for (i=1; i<=n; ++i) draw((1/i, 1)--(1/i, 0), dpen);
