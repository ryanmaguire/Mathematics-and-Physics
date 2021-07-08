
import custom_arrows;

size(128);

pair[] V;
int n;
real arsize = 5bp;

for (n = 0; n < 8; ++n)
    V[n] = expi(0.25*pi*n);


draw(V[0] -- V[1], blue, MidSharpArrow(arsize));
draw(V[1] -- V[2], red, MidSharpArrow(arsize));
draw(V[3] -- V[2], blue, MidSharpArrow(arsize));
draw(V[4] -- V[3], red, MidSharpArrow(arsize));
draw(V[4] -- V[5], green, MidSharpArrow(arsize));
draw(V[5] -- V[6], yellow, MidSharpArrow(arsize));
draw(V[7] -- V[6], green, MidSharpArrow(arsize));
draw(V[0] -- V[7], yellow, MidSharpArrow(arsize));

for (n = 0; n < 8; ++n)
    dot(V[n]);
