// Seting output format to "pdf".
import settings;
settings.outformat = "pdf";

// Size of the output.
size(128);

defaultpen(black+linewidth(0.1));

int i;
int n = 400;

pair A;
real r;

for (i=0; i<n; ++i)
{
    r = 1/(i+1);
    A = (r, 0);
    draw(circle(A, r));
}