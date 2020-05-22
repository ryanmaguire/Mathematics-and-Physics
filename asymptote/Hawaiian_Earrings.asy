// Seting output format to "pdf".
import settings;
texpreamble("\usepackage{amssymb}");

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output.
size(128);

defaultpen(black+linewidth(0.1));

int i;
int n = 400;

pair A;
real r;

for (i=0; i<n; ++i){
    r = 1/(i+1);
    A = (r, 0);
    draw(circle(A, r));
}