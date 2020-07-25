// Boilerplate stuff.
import settings;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Make sure _custom_arrows.asy is in your ASYMPTOTE_DIR environment variable.
// This file is found in the asymptote/ folder. Similarly for _euc_geo_2d.
import _custom_arrows;
import _euc_geo_2d;

// Size of the output figure.
size(256);

// Needed for the use of mathbb and mathcal commands.
texpreamble("\usepackage{amssymb}");

// Size of the arrow head and a variable used for drawing paths.
real arsize = 5bp;
path g;

// Variables for shifting the graph.
real xshift = -8.0;
real yshift =  1.3;
transform TShift = shift(xshift, yshift);

// Pens used for filling and drawing.
pen fillpen1 = red + 0.3*white;
pen fillpen2 = cyan;
pen drawpen = black + linewidth(0.5pt);
pen axespen = drawpen + 0.5;
pen dashpen = drawpen + linetype("8 4");

// Points used to define the x and y axes.
pair[] XAxes = {(-0.5,  0.0), (3.0, 0.0)};
pair[] YAxes = {( 0.0, -0.5), (0.0, 3.0)};

// Points and angles for the manifold X, the open set U, and the image of U.
pair[] UPts   = {(2.0, 0.0), (2.7, 0.5), (3.5, 0.0), (3.2,-0.9), (2.2,-0.8)};
pair[] ImUPts = {(0.5, 1.5), (1.2, 1.9), (1.9, 1.4), (1.4, 0.2), (0.4, 0.3)};
pair[] XPts   = {(0, 0), (1,  0.8), (2,  0.8), (4, 0), (2, -1.5), (0, -1.5)};

real[] UAngle   = {30, 0, -90, 180, 150};
real[] ImUAngle = {30, 0, -90, 180, 150};
real[] XAngle   = {90, 0, -30, -90, 180, 150};

int USize   = 5;
int ImUSize = 5;
int XSize   = 6;

// Location and angles of the donut hole in the manifold X.
pair[] DonutPts   = {(0.5, -0.7), (1.8, -0.7), (0.6, -0.8), (1.7, -0.8)};
real[] DonutAngle = {-50, 50};

// Location and angles for the arrow indicating the function.
pair[] PhiPts   = {(-3.6, 1.2), (-1.0, 1.2)};
real[] PhiAngle = {30, -30};

// Locations for labels.
pair RnLabel  = (0.5, 3.0);
pair ImULabel = (1.1, 1.0);
pair ULabel   = TShift*(2.8,-0.2);
pair XLabel   = TShift*(1.0, 0.4);

// Draw the coordinate axes for R^n.
draw(XAxes[0]--XAxes[1], axespen, SharpArrow(arsize));
draw(YAxes[0]--YAxes[1], axespen, SharpArrow(arsize));

// Draw the manifold X, the open set U, and the image of U.
draw(TShift*PathFromPointsAndAngles(XPts, XAngle, XSize, true), drawpen);
filldraw(TShift*PathFromPointsAndAngles(UPts, UAngle, USize, true),
         fillpen2, dashpen);
filldraw(PathFromPointsAndAngles(ImUPts, ImUAngle, ImUSize, true),
         fillpen1, dashpen);

// Add a donut hole in the manifold.
g =  DonutPts[0]{dir(DonutAngle[0])}..{dir(DonutAngle[1])}DonutPts[1];
draw(TShift*g, drawpen);

g =  DonutPts[2]{dir(DonutAngle[1])}..{dir(DonutAngle[0])}DonutPts[3];
draw(TShift*g, drawpen);

// Add some labels.
label("$\mathcal{U}$", ULabel);
label("$X$", XLabel);
label("$\mathbb{R}^{n}$", RnLabel);
label("$\varphi[\mathcal{U}]$", ImULabel);

// Arrow representing the mapping phi.
g = PhiPts[0]{dir(PhiAngle[0])}..{dir(PhiAngle[1])}PhiPts[1];
draw("$\varphi$", g, SharpArrow(StealthHead, arsize));
