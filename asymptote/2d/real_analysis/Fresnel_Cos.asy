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
real FRESNEL_COSINE_TAYLOR_00 =  1.0;
real FRESNEL_COSINE_TAYLOR_01 = -0.10;
real FRESNEL_COSINE_TAYLOR_02 =  4.62962962962962962962962962963e-3;
real FRESNEL_COSINE_TAYLOR_03 = -1.06837606837606837606837606838e-4;
real FRESNEL_COSINE_TAYLOR_04 =  1.45891690009337068160597572362e-6;
real FRESNEL_COSINE_TAYLOR_05 = -1.31225329638028050726463424876e-8;
real FRESNEL_COSINE_TAYLOR_06 =  8.35070279514723959168403612848e-11;
real FRESNEL_COSINE_TAYLOR_07 = -3.95542951645852576339713723403e-13;
real FRESNEL_COSINE_TAYLOR_08 =  1.44832646435981372649642651246e-15;
real FRESNEL_COSINE_TAYLOR_09 = -4.22140728880708823303144982434e-18;
real FRESNEL_COSINE_TAYLOR_10 =  1.00251649349077191670194893133e-20;
real FRESNEL_COSINE_TAYLOR_11 = -1.97706475387790517483308832056e-23;
real FRESNEL_COSINE_TAYLOR_12 =  3.28926034917575173275247613225e-26;
real FRESNEL_COSINE_TAYLOR_13 = -4.67848351551848577372630857707e-29;
real FRESNEL_COSINE_TAYLOR_14 =  5.75419164398217177219656443388e-32;
real FRESNEL_COSINE_TAYLOR_15 = -6.18030758822279613746380577975e-35;
real FRESNEL_COSINE_TAYLOR_16 =  5.84675500746883629629795521967e-38;
real FRESNEL_COSINE_TAYLOR_17 = -4.90892396452342296700208077293e-41;
real FRESNEL_COSINE_TAYLOR_18 =  3.68249351546114573519399405667e-44;
real FRESNEL_COSINE_TAYLOR_19 = -2.48306909745491159103989919027e-47;
real FRESNEL_COSINE_TAYLOR_20 =  1.51310794954121709805375306783e-50;
real FRESNEL_COSINE_TAYLOR_21 = -8.37341968387228154282667202938e-54;
real FRESNEL_COSINE_TAYLOR_22 =  4.22678975419355257583834431490e-57;
real FRESNEL_COSINE_TAYLOR_23 = -1.95410258232417110409647625591e-60;
real FRESNEL_COSINE_TAYLOR_24 =  8.30461450592911058167783010711e-64;
real FRESNEL_COSINE_TAYLOR_25 = -3.25539546201302778914022841136e-67;
real FRESNEL_COSINE_TAYLOR_26 =  1.18076183891157008799527066561e-70;

// Variables used for indexing.
int i;

// Number of samples in the Fresnel Cosine function.
int samples1 = 200;

// Number of samples for each section of cos(x^2) (there are 5).
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

// Roots of cos(x^2).
real root1  = 1.2533141373155001;
real root2  = 2.1708037636748028;
real root3  = 2.8024956081989645;
real root4  = 3.3159575219782710;

// Pen used for drawing functions.
pen db = deepblue;

// Taylor series for the Fresnel cosine function.
real f(real x)
{
    // Variables for S(x) and powers of x, respectively.
    real cx, arg;
    arg = x*x;

    // This Taylor Series is capable of double precision accuracy for values
    // in the range -3.3 < x < 3.3. Perfect for our plot range. We use Horner's
    // method to compute the polynomial.
    arg *= arg;
    cx = arg * FRESNEL_COSINE_TAYLOR_26 + FRESNEL_COSINE_TAYLOR_25;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_24;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_23;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_22;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_21;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_20;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_19;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_18;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_17;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_16;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_15;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_14;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_13;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_12;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_11;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_10;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_09;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_08;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_07;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_06;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_05;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_04;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_03;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_02;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_01;
    cx = arg * cx + FRESNEL_COSINE_TAYLOR_00;
    return cx*x;
};

// Function to return cos(x^2).
real h(real x){return cos(x*x);}

// Plot the function.
path g=graph(f, start, end, n=samples1);
draw(g, db);

// Plots for cos(x^2) split into positive and negative regions.
path h1 = graph(h, start, root1, n=samples2);
path h2 = graph(h, root1, root2, n=samples2);
path h3 = graph(h, root2, root3, n=samples2);
path h4 = graph(h, root3, root4, n=samples2);
path h5 = graph(h, root4, end,   n=samples2);

// Plot the functions blue and red, indicating positive and negative.
filldraw(shift(0, yshift)*(h1 -- (root1, 0) -- (0, 0) -- cycle), lightblue, db);
filldraw(shift(0, yshift)*(h2 -- (root2, 0) -- cycle),           lightred,  db);
filldraw(shift(0, yshift)*(h3 -- (root3, 0) -- cycle),           lightblue, db);
filldraw(shift(0, yshift)*(h4 -- (root4, 0) -- cycle),           lightred,  db);
filldraw(shift(0, yshift)*(h5 -- (end,   0) -- cycle),           lightblue, db);

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

// Labels for the functions and a definition of C(x), the Fresnel cos function.
label("$C(x)$", (3.2, 0.8));
label("$\displaystyle{C(x)=\int_{0}^{x}\cos(t^{2})\,\textrm{d}t}$",
      (1.5, -0.7), fontsize(12pt));
label("$\cos(x^{2})$", (3.05, yshift+0.75));

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