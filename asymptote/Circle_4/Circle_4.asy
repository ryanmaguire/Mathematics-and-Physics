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

defaultpen(fontsize(7pt));

// Size of the output figure.
size(128);

pen cpen = deepblue;

pair MidPoint(pair A, pair B){return scale(0.5)*(A+B);}

pair FindCenter(pair A, pair B, pair C){
    pair U = MidPoint(A, B);
    pair V = MidPoint(B, C);
    
}

pair P = (-0.5, 0.5);

real R = sqrt(0.5);

draw(circle(P, R), cpen);
draw((-1.2, 0.0)--(0.2, 0.0));
draw((0.0, -0.2)--(0.0, 1.2));
