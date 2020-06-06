// Seting output format to "pdf".
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of output.
size(256);

// Default pen used for labels.
defaultpen(fontsize(9pt));

// Pen used to label functions.
pen fpen = fontsize(7pt);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.3cm, 0.3cm);

// Variable used for indexing.
int i;

// size of the arrow heads.
real arsize = 5bp;

// Loop over all of the points and label various functions and nodes.
for(i=1; i<5; ++i){
    draw("$f_{"+string(i)+"}$", (2*i, 2)--(2*i,   0), 2*E, fpen,
         SharpArrow(arsize), margins);
    draw("$g_{"+string(i)+"}$", (2*i, 2)--(2*i+2, 2), 2*S, fpen,
         SharpArrow(arsize), margins);
    draw("$h_{"+string(i)+"}$", (2*i, 0)--(2*i+2, 0), 2*N, fpen,
         SharpArrow(arsize), margins);

    label("$A_{"+string(i)+"}$", (2*i, 2));
    label("$B_{"+string(i)+"}$", (2*i, 0));
}

// Draw the rightmost arrows and labels.
draw("$f_{"+string(i)+"}$", (2*i, 2)--(2*i, 0), 2*E, fpen,
     SharpArrow(arsize), margins);

label("$A_{"+string(i)+"}$", (2*i, 2));
label("$B_{"+string(i)+"}$", (2*i, 0));