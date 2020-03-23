// Boilerplate stuff.
import settings;
settings.outformat="pdf";
settings.render=4;

// Size of output.
size(400);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Margins for the arrows.
margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

// Variable used for indexing.
int i;

// size of the arrow heads.
real arsize = 5bp;

// Loop over all of the points and label various functions and nodes.
for(i=1; i<5; ++i){
    draw("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i, 0),
         arrow=Arrow(arsize), E, margin=ArrowMargins, fpen);
    draw("$g_{"+string(i)+"}$", (2*i, 2) -- (2*i+2, 2),
         arrow=Arrow(arsize), N, margin=ArrowMargins, fpen);
    draw("$h_{"+string(i)+"}$", (2*i, 0) -- (2*i+2, 0),
         arrow=Arrow(arsize), N, margin=ArrowMargins, fpen);

    label("$A_{"+string(i)+"}$", (2*i, 2));
    label("$B_{"+string(i)+"}$", (2*i, 0));
}

// Draw the rightmost arrows and labels.
draw("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i, 0),
     arrow=Arrow(arsize), E, margin=ArrowMargins, fpen);

label("$A_{"+string(i)+"}$", (2*i, 2));
label("$B_{"+string(i)+"}$", (2*i, 0));