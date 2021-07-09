
// Size of the output.
size(128);

// Solid pen and dashed pen.
pen bpen = black+linewidth(0.7pt);
pen wpen = white+linewidth(3pt);

pair A1 = (0, 3);
pair A2 = (1, 2);
pair A3 = (1, 1);
pair A4 = (0, 0);
pair B1 = (3, 3);
pair B2 = (2, 2);
pair B3 = (2, 1);
pair B4 = (3, 0);

real r = 0.05;

draw(B1--A2, bpen);
draw(A1--B2, wpen);
draw(A1--B2, bpen);
draw(B2--A3, bpen);
draw(A2--B3, wpen);
draw(A2--B3, bpen);
draw(B3--A4, bpen);
draw(A3--B4, wpen);
draw(A3--B4, bpen);
draw(A1--A4, bpen);
draw(B1--B4, bpen);

filldraw(circle(A1, r), black, black);
filldraw(circle(A2, r), black, black);
filldraw(circle(A3, r), black, black);
filldraw(circle(A4, r), black, black);
filldraw(circle(B1, r), black, black);
filldraw(circle(B2, r), black, black);
filldraw(circle(B3, r), black, black);
filldraw(circle(B4, r), black, black);
