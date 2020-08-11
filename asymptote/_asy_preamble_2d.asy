import settings;
if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;
settings.bw          = false;
settings.cmyk        = false;
viewportmargin       = (2, 2);

// Pen used for labels and drawing.
defaultpen(black+linewidth(0.5pt)+fontsize(7pt));

// Default size of arrowheads.
real arsize = 5bp;

// Needed for the use of mathbb and mathcal commands.
texpreamble("\usepackage{amssymb}");

// Commonly used pens.
pen axesp  = black + linewidth(0.8pt) + fontsize(9pt);
pen dashp  = defaultpen + linetype("8 4");
pen thinp  = black + linewidth(0.3pt);
pen labelp = defaultpen + fontsize(10pt);

// Size used for drawing dots.
real rDot = 0.025;