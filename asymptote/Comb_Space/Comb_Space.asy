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