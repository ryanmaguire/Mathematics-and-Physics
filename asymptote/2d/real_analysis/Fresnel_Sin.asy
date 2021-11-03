// This code uses an asymptote version of C code I had written for the
// NASA Cassini radio science team as a part of rss_ringoccs. Like this
// project, rss_ringoccs was released under the GNU GPL 3 license.
// https://github.com/NASA-Planetary-Science/rss_ringoccs

// Import necessary stuff, set format to PDF file.
import graph;
import custom_arrows;
import settings;
settings.outformat="pdf";

// Size of the output figure.
size(256);

// Define Coefficients for the Fresnel Sine Taylor Expansion.
real FRESNEL_SINE_TAYLOR_00 =  0.33333333333333333333333333333;
real FRESNEL_SINE_TAYLOR_01 = -2.38095238095238095238095238095e-2;
real FRESNEL_SINE_TAYLOR_02 =  7.57575757575757575757575757576e-4;
real FRESNEL_SINE_TAYLOR_03 = -1.32275132275132275132275132275e-5;
real FRESNEL_SINE_TAYLOR_04 =  1.45038522231504687645038522232e-7;
real FRESNEL_SINE_TAYLOR_05 = -1.08922210371485733804574384285e-9;
real FRESNEL_SINE_TAYLOR_06 =  5.94779401363763503681199154450e-12;
real FRESNEL_SINE_TAYLOR_07 = -2.46682701026445692771004257606e-14;
real FRESNEL_SINE_TAYLOR_08 =  8.03273501241577360913984452289e-17;
real FRESNEL_SINE_TAYLOR_09 = -2.10785519144213582486050800945e-19;
real FRESNEL_SINE_TAYLOR_10 =  4.55184675892820028624362194733e-22;
real FRESNEL_SINE_TAYLOR_11 = -8.23014929921422135684449347133e-25;
real FRESNEL_SINE_TAYLOR_12 =  1.26410789889891635219506925867e-27;
real FRESNEL_SINE_TAYLOR_13 = -1.66976179341737202698649397027e-30;
real FRESNEL_SINE_TAYLOR_14 =  1.91694286210978253077267196219e-33;
real FRESNEL_SINE_TAYLOR_15 = -1.93035720881510785655551537411e-36;
real FRESNEL_SINE_TAYLOR_16 =  1.71885606280178362396819126766e-39;
real FRESNEL_SINE_TAYLOR_17 = -1.36304126177913957635067836351e-42;
real FRESNEL_SINE_TAYLOR_18 =  9.68728023887076175384366004096e-46;
real FRESNEL_SINE_TAYLOR_19 = -6.20565791963739670594197460729e-49;
real FRESNEL_SINE_TAYLOR_20 =  3.60157930981012591661339989697e-52;
real FRESNEL_SINE_TAYLOR_21 = -1.90254122728987952723942026864e-55;
real FRESNEL_SINE_TAYLOR_22 =  9.18642950239868569596123672835e-59;
real FRESNEL_SINE_TAYLOR_23 = -4.07013527785325672297810283986e-62;
real FRESNEL_SINE_TAYLOR_24 =  1.66058051345108993284425792700e-65;
real FRESNEL_SINE_TAYLOR_25 = -6.25918411694871134024677459636e-69;
real FRESNEL_SINE_TAYLOR_26 =  2.18621042295388572102809768805e-72;

// Variables used for indexing.
int i;

// Number of samples in the Fresnel Sine function.
int samples1 = 200;

// Number of samples for each section of sin(x^2) (there are 4).
int samples2 = 50;

// The first and last values to be plotted.
real start   =  0.00;
real end     =  3.40;

// The start and end of the x axis.
real xmin    = -0.10;
real xmax    =  3.70;

// The start and end of the y axis.
real ymin    = -0.10;
real ymax    =  1.22;

// The displacement of the second graph.
real yshift  = -2.00;

// Size of the arrow heads.
real arsize = 5bp;

// Roots of sin(x^2).
real root1   = 1.7724538509055159;
real root2   = 2.5066282746310002;
real root3   = 3.0699801238394655;

// Pen used for drawing functions.
pen db = deepblue;

// Taylor series for Fresnel sine.
real f(real x)
{
    // Variables for S(x) and powers of x, respectively.
    real sx;
    real arg = x*x;

    // This Taylor Series is capable of double precision accuracy for values
    // in the range -3.3 < x < 3.3. Perfect for our plot range.
    x *= arg;
    arg *= arg;
    sx = arg * FRESNEL_SINE_TAYLOR_26 + FRESNEL_SINE_TAYLOR_25;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_24;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_23;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_22;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_21;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_20;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_19;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_18;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_17;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_16;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_15;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_14;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_13;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_12;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_11;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_10;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_09;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_08;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_07;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_06;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_05;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_04;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_03;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_02;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_01;
    sx = arg * sx + FRESNEL_SINE_TAYLOR_00;
    return sx*x;
};

// Function to return sin(x^2).
real h(real x){return sin(x*x);}

// Plot the function.
path g=graph(f, start, end, n=samples1);
draw(g, db);

// Plots for sin(x^2) split into positive and negative regions.
path h1 = graph(h, start, root1, n=samples2);
path h2 = graph(h, root1, root2, n=samples2);
path h3 = graph(h, root2, root3, n=samples2);
path h4 = graph(h, root3, end,   n=samples2);

// Plot the functions blue and red, indicating positive and negative.
filldraw(shift(0, yshift)*(h1 -- (root1, 0) -- (0, 0) -- cycle), lightblue, db);
filldraw(shift(0, yshift)*(h2 -- (root2, 0) -- cycle),           lightred,  db);
filldraw(shift(0, yshift)*(h3 -- (root3, 0) -- cycle),           lightblue, db);
filldraw(shift(0, yshift)*(h4 -- (end, 0)   -- cycle),           lightred,  db);

// Plot the axes.
label("$x$", (xmax, 0.0),         S, fontsize(9pt));
label("$y$", (0.0,  ymax),        W, fontsize(9pt));
label("$x$", (xmax, yshift),      S, fontsize(9pt));
label("$y$", (0.0,  ymax+yshift), W, fontsize(9pt));

// Dots for the functions at the point "x".
dot((end, f(end)));
dot((end, h(end)+yshift));

// Draw a dashed line between the first and second plots.
draw((end, f(end)) -- (end, h(end)+yshift), dashed);

// Labels for the functions and a definition of S(x), the Fresnel sin function.
label("$S(x)$", (3.6, 0.7));
label("$\displaystyle{S(x)=\int_{0}^{x}\sin(t^{2})\,\textrm{d}t}$",
      (1.5, -0.7), fontsize(12pt));
label("$\sin(x^{2})$", (3.6, yshift-1.1));

// Draw the x axis for the first plot, loop over points to draw tick marks.
draw((xmin, 0)--(xmax, 0), SharpArrow(arsize));
for (i=0; i<=4*(int)xmax+1; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, -0.1));
        label("$"+string((int)i/4)+"$", (i/4, -0.2), fontsize(9pt));
    }
    else draw((i/4, 0) -- (i/4, -0.05));
}

// Draw the y axis for the first plot, loop over points to draw tick marks.
draw((0, ymin)--(0, ymax), SharpArrow(arsize));
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2) -- (-0.1, i/2));
        label("$"+string((int)i/2)+"$", (-0.2, i/2), fontsize(9pt));
    }
    else draw((0, i/2) -- (-0.05, i/2));
}

// Draw the x axis for the second plot, loop over points to draw tick marks.
draw((xmin, yshift)--(xmax, yshift), SharpArrow(arsize));
for (i=0; i<=4*(int)xmax+1; ++i){
    if ((i % 4) == 0){
        draw((i/4, yshift) -- (i/4, yshift-0.1));
        label("$"+string((int)i/4)+"$", (i/4, yshift-0.2), fontsize(9pt));
    }
    else draw((i/4, yshift) -- (i/4, yshift-0.05));
}

// Draw the y axis for the second plot, loop over points to draw tick marks.
draw((0, ymin+yshift)--(0, ymax+yshift), SharpArrow(arsize));
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2+yshift) -- (-0.1, i/2+yshift));
        label("$"+string((int)i/2)+"$", (-0.2, i/2+yshift), fontsize(9pt));
    }
    else draw((0, i/2+yshift) -- (-0.05, i/2+yshift));
}