import settings;
settings.outformat = "pdf";
size(128);

pair A = (0.0, 0.0);
pair B = (2.0, 1.0);
pair C = (2.0, -1.0);
pair D = (4.0, -2.0);
pair E = (4.0, 0.0);
real rDot = 0.2;

draw(A -- B);
draw(A -- C);
draw(C -- E);
draw(C -- D);


filldraw(circle(A, rDot), cyan, black);
filldraw(circle(B, rDot), green, black);
filldraw(circle(C, rDot), red, black);
filldraw(circle(D, rDot), blue, black);
filldraw(circle(E, rDot), orange, black);
