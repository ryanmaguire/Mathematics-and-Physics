import graph;
import settings;
outformat="pdf";
settings.render=4;

size(400, 100);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

int i;
real arsize = 5bp;

for(i=1; i<5; ++i){
    draw("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i, 0),
         arrow=Arrow(arsize), E, margin=ArrowMargins);
    draw("$g_{"+string(i)+"}$", (2*i, 2) -- (2*i+2, 2),
         arrow=Arrow(arsize), N, margin=ArrowMargins);
    draw("$h_{"+string(i)+"}$", (2*i, 0) -- (2*i+2, 0),
         arrow=Arrow(arsize), N, margin=ArrowMargins);

    label("$A_{"+string(i)+"}$", (2*i, 2));
    label("$B_{"+string(i)+"}$", (2*i, 0));
}

draw("$f_{"+string(i)+"}$", (2*i, 2) -- (2*i, 0),
     arrow=Arrow(arsize), E, margin=ArrowMargins);

label("$A_{"+string(i)+"}$", (2*i, 2));
label("$B_{"+string(i)+"}$", (2*i, 0));