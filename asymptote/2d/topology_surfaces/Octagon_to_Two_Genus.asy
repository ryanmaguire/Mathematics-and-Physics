// Seting output format to "pdf".
import graph;

// Size of the output figure.
size(256);

// Size of the arrow head.
real arsize = 5bp;

// Variable for indexing.
int i;

// Number of sides.
int n = 8;

// For looping over angles.
real phi;

// Current points.
pair A, B;

// The Label.
Label L;

// The path.
path g;

// Shifts for the second image.
real xshift = 3.0;
real yshift = 0.0;

A = expi(pi/n);

for (i=0; i<n; ++i)
{
    phi = 2*pi*(i+1)/n + pi/n;
    B = expi(phi);
    g = A--B;

    if (i == 1)      L = Label("$a$", position=0.5, N);
    else if (i == 2) L = Label("$b$", position=0.5, NW);
    else if (i == 3) L = Label("$a$", position=0.5, W);
    else if (i == 4) L = Label("$b$", position=0.5, SW);
    else if (i == 5) L = Label("$c$", position=0.5, S);
    else if (i == 6) L = Label("$d$", position=0.5, SE);
    else if (i == 7) L = Label("$c$", position=0.5, E);
    else             L = Label("$d$", position=0.5, NE);

    if ((i==3) || (i==4) || (i==7) || (i==0)) g = reverse(g);

    draw(L, g, fontsize(10pt), MidArrow(arsize));
    A = B;
}

phi = 2*pi/n + pi/n;
A = expi(phi);
phi += pi;
B = expi(phi);

draw(A--B, dashed);

A = (xshift+0.0, yshift+0.5);
B = (xshift-0.5, yshift+1.0);

draw("$a$", A--B, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift-1.5, yshift);

draw("$b$", A--B, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift-0.5, yshift-1.0);

draw("$a$", B--A, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift, yshift-0.5);

draw("$b$", B--A, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift+0.5, yshift-1.0);

draw("$c$", A--B, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift+1.5, yshift);

draw("$d$", A--B, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift+0.5, yshift+1.0);

draw("$c$", B--A, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift, yshift+0.5);

draw("$d$", B--A, fontsize(10pt), MidArrow(arsize));

A = B;
B = (xshift, -0.5);
draw(A--B, dashed);

// Draw the third image.
xshift += 3.0;
n = 4;
A = (1.0, 0.0);

for (i=0; i<n; ++i){
    phi = 2*pi*(i+1)/n;
    B = expi(phi);
    g = A--B;
    if (i == 0)      L = Label("$a$", position=0.5, NE);
    else if (i == 1) L = Label("$b$", position=0.5, NW);
    else if (i == 2) L = Label("$a$", position=0.5, SW);
    else             L = Label("$b$", position=0.5, SE);

    if ((i==2) || (i==3)) g = reverse(g);

    draw(L, shift(xshift, yshift)*g, fontsize(10pt), MidArrow(arsize));
    A = B;
}

A = (xshift+1.0, yshift+0.0);
B = (xshift+2.0, yshift+0.0);
draw(A--B, dashed);

xshift += 3.0;
A = (1.0, 0.0);
for (i=0; i<n; ++i){
    phi = 2*pi*(i+1)/n;
    B = expi(phi);
    g = A--B;
    if (i == 0)      L = Label("$c$", position=0.5, NE);
    else if (i == 1) L = Label("$d$", position=0.5, NW);
    else if (i == 2) L = Label("$c$", position=0.5, SW);
    else             L = Label("$d$", position=0.5, SE);

    if ((i==0) || (i==1)) g = reverse(g);

    draw(L, shift(xshift, yshift)*g, fontsize(10pt), MidArrow(arsize));
    A = B;
}

xshift = 1.3;
yshift = -2.8;

g = (0.0, 0.8){W}..(-0.8, 1.0)..(-2.0, 0.0)..(-0.8, -1.0)..(0.0, -0.8){E};
draw(shift(xshift, yshift)*g);
draw(shift(xshift+1.0, yshift)*(reflect((0.0, 1.0), (0.0, -1.0))*g));
draw(shift(xshift, yshift)*((0.0,  0.8)--(1.0,  0.8)), dashed);
draw(shift(xshift, yshift)*((0.0, -0.8)--(1.0, -0.8)), dashed);

// Add donut holes.
g =  (1.2, 0.0){dir(-50)}..{dir(50)}(2.3, 0.0);
draw(shift(xshift, yshift)*g);
draw(shift(xshift-2.45, yshift)*g);

g = (1.3, -0.1){dir(50)}..{dir(-50)}(2.2, -0.1);
draw(shift(xshift, yshift)*g);
draw(shift(xshift-2.45, yshift)*g);

xshift += 6.3;

g = (0.0,  0.8){W}..(-0.8,  1.0)..(-2.0, 0.0)..(-0.8, -1.0)..
    (0.0, -0.8){E}..( 0.8, -1.0)..( 2.0, 0.0)..( 0.8,  1.0)..cycle;
draw(shift(xshift, yshift)*g);

// Add donut holes.
g =  (0.45, 0.0){dir(-50)}..{dir(50)}(1.55, 0.0);
draw(shift(xshift, yshift)*g);
draw(shift(xshift-2, yshift)*g);

g = (0.55, -0.1){dir(50)}..{dir(-50)}(1.45, -0.1);
draw(shift(xshift, yshift)*g);
draw(shift(xshift-2, yshift)*g);
