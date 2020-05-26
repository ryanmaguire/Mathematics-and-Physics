// Seting output format to "pdf".
import settings;
import _custom_arrows;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output figure.
size(128);

// pen for the axes and projections.
pen apen = black+linewidth(0.8pt);
pen dpen = black+linewidth(0.3pt)+dashed;

// Endpoints for the axes.
real start = -0.4;
real end   =  4.0;

// Size of the arrow head.
real arsize = 6bp;

// Size of the font.
real fsize = 10pt;

// Label for the axes.
Label L;

// Points for the blob.
path g = (1.0, 1.0) -- (2.0, 1.0) -- (2.0, 2.0) -- (3.0, 2.0)
                    -- (3.0, 3.5) -- (1.5, 3.5) -- (1.5, 2.0)
                    -- (1.0, 2.0) -- cycle;

// Fill in the blob.
filldraw(g, cyan, dpen);

// Draw the x and y axis.
L = Label("$x$", position=1.0, S, fontsize(fsize));
draw(L, (start, 0.0)--(end, 0.0), apen, SharpArrow(arsize));

L = Label("$y$", position=1.0, W, fontsize(fsize));
draw(L, (0.0, start)--(0.0, end), W, apen, SharpArrow(arsize));
