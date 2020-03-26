// Boilerplate stuff.
import settings;
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Size of output.
size(400);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Margins for the arrows.
real marg = 0.4cm;

// Variable used for indexing.
int i;

// size of the arrow heads.
real arsize = 5bp;

// Loop over all of the points and label various functions and nodes.
for(i=1; i<5; ++i){
    sharp_arrow("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i,   0), E,
                arsize=arsize, mstart=marg, mend=marg, fpen);
    sharp_arrow("$g_{"+string(i)+"}$", (2*i, 2) -- (2*i+2, 2), N,
                arsize=arsize, mstart=marg, mend=marg, fpen);
    sharp_arrow("$h_{"+string(i)+"}$", (2*i, 0) -- (2*i+2, 0), N,
                arsize=arsize, mstart=marg, mend=marg, fpen);

    label("$A_{"+string(i)+"}$", (2*i, 2));
    label("$B_{"+string(i)+"}$", (2*i, 0));
}

// Draw the rightmost arrows and labels.
sharp_arrow("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i, 0), E,
            arsize=arsize, mstart=marg, mend=marg, fpen);

label("$A_{"+string(i)+"}$", (2*i, 2));
label("$B_{"+string(i)+"}$", (2*i, 0));