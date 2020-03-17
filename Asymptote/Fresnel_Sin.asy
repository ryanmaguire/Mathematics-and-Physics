// Import necessary stuff, set format to PDF file.
import graph;
import settings;
import contour;
import fontsize;
outformat="pdf";

defaultpen(fontsize(9pt));

// Size of the output figure.
size(256, 256);

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
real FRESNEL_SINE_TAYLOR_27 = -7.09571739181805357327043566663e-76;
real FRESNEL_SINE_TAYLOR_28 =  2.14564844309633852738645079818e-79;
real FRESNEL_SINE_TAYLOR_29 = -6.05939744697137480782877578571e-83;
real FRESNEL_SINE_TAYLOR_30 =  1.60173329821314496897157652161e-86;

// Variables that will be used throughout.
int i;
int samples1 = 200;
int samples2 = 50;
real start   =  0.00;
real end     =  3.40;
real xmin    = -0.10;
real xmax    =  3.70;
real ymin    = -0.10;
real ymax    =  1.22;
real yshift  = -2.00;
real root1   = 1.7724538509055159;
real root2   = 2.5066282746310002;
real root3   = 3.0699801238394655;

// Hectic, but continuous, function that is to be plotted.
real f(real x)
{
    /* Variables for S(x) and powers of x, respectively. */
    real sx;
    real arg = x*x;

    /* This Taylor Series is capable of double precision accuracy for values  *
     * in the range -3.3 < x < 3.3. Perfect for our plot range.               */
    x *= arg;
    arg *= arg;
    sx = arg * FRESNEL_SINE_TAYLOR_24 + FRESNEL_SINE_TAYLOR_23;
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

// Plot the function.
path g=graph(f, start, end, n=samples1);
draw(g, black);

real h(real x){return sin(x*x);}

// Plot the function.
path g=graph(f, start, end, n=samples1);
draw(g, black);

path h1 = graph(h, start, root1, n=samples2);
path h2 = graph(h, root1, root2, n=samples2);
path h3 = graph(h, root2, root3, n=samples2);
path h4 = graph(h, root3, end,   n=samples2);

filldraw(shift(0, yshift)*(h1 -- (root1, 0) -- (0, 0) -- cycle), lightblue);
filldraw(shift(0, yshift)*(h2 -- (root2, 0) -- cycle), lightred);
filldraw(shift(0, yshift)*(h3 -- (root3, 0) -- cycle), lightblue);
filldraw(shift(0, yshift)*(h4 -- (end, 0)   -- cycle), lightred);

// Plot the axes.
label("$x$", (xmax, 0.0),  S);
label("$y$", (0.0,  ymax), W);
label("$x$", (xmax, yshift),     S);
label("$y$", (0.0,  ymax+yshift), W);

real y0 = f(end);

dot((end,  f(end)));
dot((end,  h(end)+yshift));
draw((end, f(end)) -- (end, h(end)+yshift), dashed);

label("$S(x)$", (3.6, 0.7));
label("$\displaystyle{S(x)=\int_{0}^{x}\sin(t^{2})\textrm{d}t}$",
      (1.5, -0.7), fontsize(12pt));
label("$\sin(x^{2})$", (3.6, yshift-1.0));

int i;
draw((xmin, 0) -- (xmax, 0), arrow=Arrow());
for (i=0; i<=4*(int)xmax+1; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, -0.1));
        label("$"+string((int)i/4)+"$", (i/4, -0.2));
    }
    else draw((i/4, 0) -- (i/4, -0.05));
}

draw((0, ymin) -- (0, ymax), arrow=Arrow());
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2) -- (-0.1, i/2));
        label("$"+string((int)i/2)+"$", (-0.2, i/2));
    }
    else draw((0, i/2) -- (-0.05, i/2));
}

draw((xmin, yshift) -- (xmax, yshift), arrow=Arrow());
for (i=0; i<=4*(int)xmax+1; ++i){
    if ((i % 4) == 0){
        draw((i/4, yshift) -- (i/4, yshift-0.1));
        label("$"+string((int)i/4)+"$", (i/4, yshift-0.2));
    }
    else draw((i/4, yshift) -- (i/4, yshift-0.05));
}

draw((0, ymin+yshift) -- (0, ymax+yshift), arrow=Arrow());
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2+yshift) -- (-0.1, i/2+yshift));
        label("$"+string((int)i/2)+"$", (-0.2, i/2+yshift));
    }
    else draw((0, i/2+yshift) -- (-0.05, i/2+yshift));
}