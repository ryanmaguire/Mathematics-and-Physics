access "custom_arrows.asy" as arrows;
import settings;

settings.outformat = "pdf";

size(256);

pair A = (-4.0000, -1.0000);
pair B = (+4.0000, +1.0000);
pair C = (-4.0000, +0.0000);
pair D = (+4.0000, -1.0000);
pair P = (+0.0000, +1.5000);
pair X = (+1.0000, +0.2500);
pair Y = (+1.7778, -0.7222);

real radius = 0.05;

margin margins = TrueMargin(0.3cm, 0.3cm);
real arrow_size = 5bp;

/*  Arrow used for all curves.                                                */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

draw(A -- B, sharp_arrow, margins);
draw(C -- D, sharp_arrow, margins);

draw(P -- Y);

filldraw(circle(A, radius), black, black);
filldraw(circle(B, radius), black, black);
filldraw(circle(C, radius), black, black);
filldraw(circle(D, radius), black, black);
filldraw(circle(P, radius), black, black);
filldraw(circle(X, radius), black, black);
filldraw(circle(Y, radius), black, black);

label("$A$", A, S);
label("$B$", B, N);
label("$C$", C, N);
label("$D$", D, S);
label("$P$", P, E);
label("$x$", X, NE);
label("$y$", Y, S);
