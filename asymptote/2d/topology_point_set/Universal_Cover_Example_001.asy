// Boilerplate stuff.
import settings;
settings.outformat = "pdf";


pair midpoint(pair A, pair B){return scale(0.5)*(A+B);}

// Default pen for drawing.
defaultpen(black+linewidth(0.5pt));

// Size of the output figure.
size(256);


// Radius of sphere.
real R = 0.5;
pair A, B, C;

int i;
int n = 8;

// Paths to draw the figures.
path g;

// Draw the sphere.
for (i=0; i<n; i+=2){
    A = (i, 0);
    B = (i+1, 0);
    C = (i+1.5, 0);
    draw(A--B);
    filldraw(circle(C, R), gray(0.7)+opacity(0.5));
    draw(scale(1, 0.4)*arc(C, R, 180, 360));
    draw(scale(1, 0.4)*arc(C, R, 0, 180), linetype("4 4"));
}
A = (n, 0);
B = (n+1, 0);
draw(A--B);
