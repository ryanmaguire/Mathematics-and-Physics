// Seting output format to "pdf".
import settings;
import graph;
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

defaultpen(fontsize(8pt));

// Size of the output figure.
size(128);

// Some lengths.
real xlength  =  3.0;
real ystart   = -0.5;
real ylen     =  3.0;
real d        =  1.0;
real a        =  1.0;
real fsize    =  6pt;
real arlength = 0.2;
real barsize  = 2bp;
real ar       = 5bp;

pair dx      = (0.07, 0.00);
pair dy      = (0.00, 0.07);
pair dl      = (a,    0.35*ylen);
pair dlprime = (0.00, 0.5*ylen);
pair rprime  = (0.00, 0.5*ylen);

Label L;
path g;

margin arrowmargin = TrueMargin(0.0, 0.03cm);

pen dpen = black+linewidth(0.5pt)+linetype("4 4");
pen cpen = black+linewidth(0.5pt);
pen apen = black+linewidth(0.6pt);

draw((0.0, 0.0)--(xlength, 0.0), dpen);
draw((0.0, ystart)--(0.0, ylen), cpen);

draw("I",   (a,   0.0)--(a+d, 0.0),  N, apen, SharpArrow(ar, currentpos=0.55));
draw("II",  (a+d, 0.0)--(a+d, ylen), W, apen, SharpArrow(ar, currentpos=0.55));
draw("III", (a+d, ylen)--(a, ylen),  S, apen, SharpArrow(ar, currentpos=0.6));
draw("IV",  (a, ylen)--(a, 0.0),     E, apen, SharpArrow(ar, currentpos=0.5));


draw("$\mathbf{r}$",  (0.0, 0.0)--dl,     NW, cpen);
draw("$\mathbf{r}'$", (0.0, 0.0)--rprime, W,  cpen);
draw("$\mathbf{R}$",  rprime--dl,         SW, cpen);

L = Label("$\textrm{d}\ell$", position=MidPoint, align=2E, fontsize(fsize));
draw(L, (dl+dx-dy)--(dl+dx+dy), bar=Bars(barsize));

path uparrow   = (dl+dx-dy)-(0.0, arlength)--(dl+dx-dy);
path downarrow = (dl+dx+dy)+(0.0, arlength)--(dl+dx+dy);
draw(downarrow, arrow=SharpArrow(), margin = arrowmargin);
draw(uparrow,   arrow=SharpArrow(), margin = arrowmargin);

label("$d$", (0.5*d,   -0.2));
label("$a$", (d+0.5*a, -0.2));
label("$b$", (d+a+0.2, 0.5*ylen));

L = Label("$\textrm{d}\ell'$", position=MidPoint, align=2W, fontsize(fsize));
draw(L, (dlprime-dx-dy)--(dlprime-dx+dy), bar=Bars(barsize));
path uparrow   = (dlprime-dx-dy)-(0.0, arlength)--(dlprime-dx-dy);
path downarrow = (dlprime-dx+dy)+(0.0, arlength)--(dlprime-dx+dy);
draw(downarrow, arrow=SharpArrow(), margin = arrowmargin);
draw(uparrow,   arrow=SharpArrow(), margin = arrowmargin);