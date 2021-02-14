/*  Trig functions found here.                                                */
#include <math.h>

/*  Coefficients for the Taylor expansions found here.                        */
#include <rss_ringoccs_math_constants.h>

/******************************************************************************
 *  Define Coefficients Used for the Rational Approximation of the            *
 *  Fresnel Integrals using approximations from Mark. A. Heald.               *
 *  See Rational Approximations for the Fresnel Integrals,                    *
 *  Mathematics of Computation, Vol. 44, No. 170 (Apr., 1985), pp. 459-461    *
 *                                                                            *
 *  Heald defines the Fresnel Integrals as the integral of                    *
 *  sin(pi/2 x^2) and cos(pi/2 x^2), whereas we adopt the definition of       *
 *  the integral of sin(x^2) and cos(x^2). As such, a scale factor of         *
 *  sqrt(2/pi) is multiplied to our coefficients, and a scale factor of       *
 *  sqrt(pi/2) is multiplied to the final output.                             *
 ******************************************************************************/

/* Coefficients for up to 3 significant digits. */
#define FRESNEL_HEALD_RATIONAL_EPS_3_A00 1.0

#define FRESNEL_HEALD_RATIONAL_EPS_3_B00 2.0
#define FRESNEL_HEALD_RATIONAL_EPS_3_B01 2.524
#define FRESNEL_HEALD_RATIONAL_EPS_3_B02 1.886
#define FRESNEL_HEALD_RATIONAL_EPS_3_B03 0.803

#define FRESNEL_HEALD_RATIONAL_EPS_3_C00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_3_C01 0.506

#define FRESNEL_HEALD_RATIONAL_EPS_3_D00 SQRT_2
#define FRESNEL_HEALD_RATIONAL_EPS_3_D01 2.054
#define FRESNEL_HEALD_RATIONAL_EPS_3_D02 1.79

/* Coefficients for up to 4 significant digits. */
#define FRESNEL_HEALD_RATIONAL_EPS_4_A00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_4_A01 0.1765

#define FRESNEL_HEALD_RATIONAL_EPS_4_B00 2.0
#define FRESNEL_HEALD_RATIONAL_EPS_4_B01 2.915
#define FRESNEL_HEALD_RATIONAL_EPS_4_B02 2.079
#define FRESNEL_HEALD_RATIONAL_EPS_4_B03 1.519

#define FRESNEL_HEALD_RATIONAL_EPS_4_C00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_4_C01 0.5083
#define FRESNEL_HEALD_RATIONAL_EPS_4_C02 0.3569

#define FRESNEL_HEALD_RATIONAL_EPS_4_D00 SQRT_2
#define FRESNEL_HEALD_RATIONAL_EPS_4_D01 2.1416
#define FRESNEL_HEALD_RATIONAL_EPS_4_D02 1.8515
#define FRESNEL_HEALD_RATIONAL_EPS_4_D03 1.1021

/* Coefficients for up to 6 significant digits. */
#define FRESNEL_HEALD_RATIONAL_EPS_6_A00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_6_A01 0.08218
#define FRESNEL_HEALD_RATIONAL_EPS_6_A02 0.15108

#define FRESNEL_HEALD_RATIONAL_EPS_6_B00 2.0
#define FRESNEL_HEALD_RATIONAL_EPS_6_B01 2.7097
#define FRESNEL_HEALD_RATIONAL_EPS_6_B02 2.3185
#define FRESNEL_HEALD_RATIONAL_EPS_6_B03 1.2389
#define FRESNEL_HEALD_RATIONAL_EPS_6_B04 0.6561

#define FRESNEL_HEALD_RATIONAL_EPS_6_C00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_6_C01 0.60427
#define FRESNEL_HEALD_RATIONAL_EPS_6_C02 0.41159
#define FRESNEL_HEALD_RATIONAL_EPS_6_C03 0.19170

#define FRESNEL_HEALD_RATIONAL_EPS_6_D00 SQRT_2
#define FRESNEL_HEALD_RATIONAL_EPS_6_D01 2.26794
#define FRESNEL_HEALD_RATIONAL_EPS_6_D02 2.15594
#define FRESNEL_HEALD_RATIONAL_EPS_6_D03 1.26057
#define FRESNEL_HEALD_RATIONAL_EPS_6_D04 0.60353

/* Coefficients for up to 8 significant digits. */
#define FRESNEL_HEALD_RATIONAL_EPS_8_A00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_8_A01 0.1945161
#define FRESNEL_HEALD_RATIONAL_EPS_8_A02 0.2363641
#define FRESNEL_HEALD_RATIONAL_EPS_8_A03 0.0683240
#define FRESNEL_HEALD_RATIONAL_EPS_8_A04 0.0241212

#define FRESNEL_HEALD_RATIONAL_EPS_8_B00 2.0
#define FRESNEL_HEALD_RATIONAL_EPS_8_B01 2.9355041
#define FRESNEL_HEALD_RATIONAL_EPS_8_B02 2.7570460
#define FRESNEL_HEALD_RATIONAL_EPS_8_B03 1.8757210
#define FRESNEL_HEALD_RATIONAL_EPS_8_B04 0.9781130
#define FRESNEL_HEALD_RATIONAL_EPS_8_B05 0.3566810
#define FRESNEL_HEALD_RATIONAL_EPS_8_B06 0.1182470

#define FRESNEL_HEALD_RATIONAL_EPS_8_C00 1.0
#define FRESNEL_HEALD_RATIONAL_EPS_8_C01 0.7769507
#define FRESNEL_HEALD_RATIONAL_EPS_8_C02 0.6460117
#define FRESNEL_HEALD_RATIONAL_EPS_8_C03 0.3460509
#define FRESNEL_HEALD_RATIONAL_EPS_8_C04 0.1339259
#define FRESNEL_HEALD_RATIONAL_EPS_8_C05 0.0433995

#define FRESNEL_HEALD_RATIONAL_EPS_8_D00 SQRT_2
#define FRESNEL_HEALD_RATIONAL_EPS_8_D01 2.5129806
#define FRESNEL_HEALD_RATIONAL_EPS_8_D02 2.7196741
#define FRESNEL_HEALD_RATIONAL_EPS_8_D03 1.9840524
#define FRESNEL_HEALD_RATIONAL_EPS_8_D04 1.0917325
#define FRESNEL_HEALD_RATIONAL_EPS_8_D05 0.4205217
#define FRESNEL_HEALD_RATIONAL_EPS_8_D06 0.13634704

double Fresnel_Cosine_Heald_Rational_EPS_Minus_Three(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_3_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_3_B03*x + FRESNEL_HEALD_RATIONAL_EPS_3_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_3_C01*x + FRESNEL_HEALD_RATIONAL_EPS_3_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_3_D02*x + FRESNEL_HEALD_RATIONAL_EPS_3_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_3_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*sin(A));
}

double Fresnel_Cosine_Heald_Rational_EPS_Minus_Four(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_4_A01*x + FRESNEL_HEALD_RATIONAL_EPS_4_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_4_B03*x + FRESNEL_HEALD_RATIONAL_EPS_4_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_4_C02*x + FRESNEL_HEALD_RATIONAL_EPS_4_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_4_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_4_D03*x + FRESNEL_HEALD_RATIONAL_EPS_4_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*sin(A));
}

double Fresnel_Cosine_Heald_Rational_EPS_Minus_Six(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_6_A02*x + FRESNEL_HEALD_RATIONAL_EPS_6_A01;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_6_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_6_B04*x + FRESNEL_HEALD_RATIONAL_EPS_6_B03;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_6_C03*x + FRESNEL_HEALD_RATIONAL_EPS_6_C02;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_6_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_6_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_6_D04*x + FRESNEL_HEALD_RATIONAL_EPS_6_D03;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*sin(A));
}

double Fresnel_Cosine_Heald_Rational_EPS_Minus_Eight(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_8_A04*x + FRESNEL_HEALD_RATIONAL_EPS_8_A03;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A02;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A01;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_8_B06*x + FRESNEL_HEALD_RATIONAL_EPS_8_B05;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B04;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B03;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_8_C05*x + FRESNEL_HEALD_RATIONAL_EPS_8_C04;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C03;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C02;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_8_D06*x + FRESNEL_HEALD_RATIONAL_EPS_8_D05;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D04;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D03;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*sin(A));
}

double Fresnel_Cosine_While_to_Asymptotic_Double(double x)
{
    double FRESNEL_COSINE_TAYLOR_COEFFICIENTS[27] = {
        FRESNEL_COSINE_TAYLOR_00, FRESNEL_COSINE_TAYLOR_01,
        FRESNEL_COSINE_TAYLOR_02, FRESNEL_COSINE_TAYLOR_03,
        FRESNEL_COSINE_TAYLOR_04, FRESNEL_COSINE_TAYLOR_05,
        FRESNEL_COSINE_TAYLOR_06, FRESNEL_COSINE_TAYLOR_07,
        FRESNEL_COSINE_TAYLOR_08, FRESNEL_COSINE_TAYLOR_09,
        FRESNEL_COSINE_TAYLOR_10, FRESNEL_COSINE_TAYLOR_11,
        FRESNEL_COSINE_TAYLOR_12, FRESNEL_COSINE_TAYLOR_13,
        FRESNEL_COSINE_TAYLOR_14, FRESNEL_COSINE_TAYLOR_15,
        FRESNEL_COSINE_TAYLOR_16, FRESNEL_COSINE_TAYLOR_17,
        FRESNEL_COSINE_TAYLOR_18, FRESNEL_COSINE_TAYLOR_19,
        FRESNEL_COSINE_TAYLOR_20, FRESNEL_COSINE_TAYLOR_21,
        FRESNEL_COSINE_TAYLOR_22, FRESNEL_COSINE_TAYLOR_23,
        FRESNEL_COSINE_TAYLOR_24, FRESNEL_COSINE_TAYLOR_25,
        FRESNEL_COSINE_TAYLOR_26
    };

    /* Variables for S(x) and powers of x, respectively. */
    double cx;
    double arg = x*x;
    double x4 = arg*arg;
    double EPS = 1.0e-8;

    /* For small x use the Taylor expansion to compute C(x). For larger x,  *
     * use the asymptotic expansion. For values near 3.076, accuracy of 5   *
     * decimals is guaranteed. Higher precicion outside this region.        */
    if (arg < 9.0){
        int i = 0;
        double term = arg*FRESNEL_COSINE_TAYLOR_COEFFICIENTS[0];
        cx = term;
        while (term > EPS){
            /* Odd terms have a negative coefficients.
               Compute two terms at a time to compare with EPS. */
            i += 1;
            arg *= x4;
            term = arg*FRESNEL_COSINE_TAYLOR_COEFFICIENTS[i];
            cx += term;

            // Compute even term.
            i += 1;
            arg *= x4;
            term = arg*FRESNEL_COSINE_TAYLOR_COEFFICIENTS[i];
            cx += term;
        }
        return x*cx;
    }
    else if (arg < 1.0e16) {
        double sinarg, cosarg;
        cosarg = cos(arg);
        sinarg = sin(arg);
        arg = 1.0/arg;
        sinarg *= arg;
        arg *= arg;
        cosarg *= arg;

        sinarg *= FRESNEL_COSINE_ASYM_00 + arg*(
                    FRESNEL_COSINE_ASYM_02 + arg*(
                        FRESNEL_COSINE_ASYM_04 + FRESNEL_COSINE_ASYM_06*arg
                    )
                );
        cosarg *= FRESNEL_SINE_ASYM_01 + arg*(
                    FRESNEL_SINE_ASYM_03 + arg*(
                        FRESNEL_SINE_ASYM_05 + FRESNEL_SINE_ASYM_07*arg
                    )
                );

        cx = cosarg + sinarg;
        cx *= x;
        /*  (x > 0) - (x < 0) is a quick way to return sign(x) and avoids an  *
         *  expensive if-then statement. Output for the asymptotic expansion  *
         *  is f(|x|) + sign(x) * sqrt(pi/8). Error goes like 1/x^15.         */
        return cx + ((x > 0) - (x < 0))*SQRT_PI_BY_8;
    }
    else {
        /* For large values, return the limit of S(x) as x -> +/- infinity. */
        return ((x > 0) - (x < 0))*SQRT_PI_BY_8;
    }
}

double Fresnel_Sine_While_to_Asymptotic_Double(double x)
{
    double FRESNEL_SINE_TAYLOR_COEFFICIENTS[30] = {
        FRESNEL_SINE_TAYLOR_00, FRESNEL_SINE_TAYLOR_01,
        FRESNEL_SINE_TAYLOR_02, FRESNEL_SINE_TAYLOR_03,
        FRESNEL_SINE_TAYLOR_04, FRESNEL_SINE_TAYLOR_05,
        FRESNEL_SINE_TAYLOR_06, FRESNEL_SINE_TAYLOR_07,
        FRESNEL_SINE_TAYLOR_08, FRESNEL_SINE_TAYLOR_09,
        FRESNEL_SINE_TAYLOR_10, FRESNEL_SINE_TAYLOR_11,
        FRESNEL_SINE_TAYLOR_12, FRESNEL_SINE_TAYLOR_13,
        FRESNEL_SINE_TAYLOR_14, FRESNEL_SINE_TAYLOR_15,
        FRESNEL_SINE_TAYLOR_16, FRESNEL_SINE_TAYLOR_17,
        FRESNEL_SINE_TAYLOR_18, FRESNEL_SINE_TAYLOR_19,
        FRESNEL_SINE_TAYLOR_20, FRESNEL_SINE_TAYLOR_21,
        FRESNEL_SINE_TAYLOR_22, FRESNEL_SINE_TAYLOR_23,
        FRESNEL_SINE_TAYLOR_24, FRESNEL_SINE_TAYLOR_25,
        FRESNEL_SINE_TAYLOR_26, FRESNEL_SINE_TAYLOR_27,
        FRESNEL_SINE_TAYLOR_28, FRESNEL_SINE_TAYLOR_29
    };

    /* Variables for S(x) and powers of x, respectively. */
    double sx;
    double arg = x*x;
    double x4 = arg*arg;
    double EPS = 1.0e-8;

    /* For small x use the Taylor expansion to compute C(x). For larger x,  *
     * use the asymptotic expansion. For values near 3.076, accuracy of 5   *
     * decimals is guaranteed. Higher precicion outside this region.        */
    if (arg < 9.0){
        int i = 0;
        double term = arg*FRESNEL_SINE_TAYLOR_COEFFICIENTS[0];
        sx = term;
        while (term > EPS){
            /* Odd terms have a negative coefficients.
               Compute two terms at a time to compare with EPS. */
            i += 1;
            arg *= x4;
            term = arg*FRESNEL_SINE_TAYLOR_COEFFICIENTS[i];
            sx += term;

            // Compute even term.
            i += 1;
            arg *= x4;
            term = arg*FRESNEL_SINE_TAYLOR_COEFFICIENTS[i];
            sx += term;
        }
        return x*sx;
    }
    else if (arg < 1.0e16) {
        double sinarg, cosarg;
        cosarg = cos(arg);
        sinarg = sin(arg);
        arg = 1.0/arg;
        cosarg *= arg;
        arg *= arg;
        sinarg *= arg;

        cosarg *= FRESNEL_SINE_ASYM_00 + arg*(
                    FRESNEL_SINE_ASYM_02 + arg*(
                        FRESNEL_SINE_ASYM_04 + FRESNEL_SINE_ASYM_06*arg
                    )
                );
        sinarg *= FRESNEL_SINE_ASYM_01 + arg*(
                    FRESNEL_SINE_ASYM_03 + arg*(
                        FRESNEL_SINE_ASYM_05 + FRESNEL_SINE_ASYM_07*arg
                    )
                );

        sx = cosarg + sinarg;
        sx *= x;
        /*  (x > 0) - (x < 0) is a quick way to return sign(x) and avoids an  *
         *  expensive if-then statement. Output for the asymptotic expansion  *
         *  is f(|x|) + sign(x) * sqrt(pi/8). Error goes like 1/x^15.         */
        return sx + ((x > 0) - (x < 0))*SQRT_PI_BY_8;
    }
    else {
        /* For large values, return the limit of S(x) as x -> +/- infinity. */
        return ((x > 0) - (x < 0))*SQRT_PI_BY_8;
    }
}

double Fresnel_Sine_Heald_Rational_EPS_Minus_Three_Double(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_3_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_3_B03*x + FRESNEL_HEALD_RATIONAL_EPS_3_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_3_C01*x + FRESNEL_HEALD_RATIONAL_EPS_3_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_3_D02*x + FRESNEL_HEALD_RATIONAL_EPS_3_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_3_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*cos(A));
}

double Fresnel_Sine_Heald_Rational_EPS_Minus_Four_Double(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_4_A01*x + FRESNEL_HEALD_RATIONAL_EPS_4_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_4_B03*x + FRESNEL_HEALD_RATIONAL_EPS_4_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_4_C02*x + FRESNEL_HEALD_RATIONAL_EPS_4_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_4_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_4_D03*x + FRESNEL_HEALD_RATIONAL_EPS_4_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*cos(A));
}

double Fresnel_Sine_Heald_Rational_EPS_Minus_Six_Double(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_6_A02*x + FRESNEL_HEALD_RATIONAL_EPS_6_A01;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_6_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_6_B04*x + FRESNEL_HEALD_RATIONAL_EPS_6_B03;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_6_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_6_C03*x + FRESNEL_HEALD_RATIONAL_EPS_6_C02;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_6_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_6_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_6_D04*x + FRESNEL_HEALD_RATIONAL_EPS_6_D03;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_6_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*cos(A));
}

double Fresnel_Sine_Heald_Rational_EPS_Minus_Eight_Double(double x)
{
    double A, R, a, b, c, d, sgn_x;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_8_A04*x + FRESNEL_HEALD_RATIONAL_EPS_8_A03;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A02;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A01;
    a = a*x + FRESNEL_HEALD_RATIONAL_EPS_8_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_8_B06*x + FRESNEL_HEALD_RATIONAL_EPS_8_B05;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B04;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B03;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_8_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_8_C05*x + FRESNEL_HEALD_RATIONAL_EPS_8_C04;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C03;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C02;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_8_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_8_D06*x + FRESNEL_HEALD_RATIONAL_EPS_8_D05;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D04;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D03;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_8_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    return sgn_x*(SQRT_PI_BY_8 - R*cos(A));
}

complex double Fresnel_Heald_Rational_EPS_Minus_Three_Func(double x)
{
    double A, R, a, b, c, d, sgn_x, sx, cx;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_3_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_3_B03*x + FRESNEL_HEALD_RATIONAL_EPS_3_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_3_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_3_C01*x + FRESNEL_HEALD_RATIONAL_EPS_3_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_3_D02*x + FRESNEL_HEALD_RATIONAL_EPS_3_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_3_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    cx = sgn_x*(SQRT_PI_BY_8 - R*sin(A));
    sx = sgn_x*(SQRT_PI_BY_8 - R*cos(A));

    return cx + _Complex_I*sx;
}

complex double Fresnel_Heald_Rational_EPS_Minus_Four_Func(double x)
{
    double A, R, a, b, c, d, sgn_x, sx, cx;
    sgn_x = (x>0)-(x<0);
    x *= SQRT_2_BY_PI*sgn_x;

    /* Compute the Numerator of the A_jk Function.      */
    a = FRESNEL_HEALD_RATIONAL_EPS_4_A01*x + FRESNEL_HEALD_RATIONAL_EPS_4_A00;

    /* Compute the Denominator of the A_jk Function.    */
    b = FRESNEL_HEALD_RATIONAL_EPS_4_B03*x + FRESNEL_HEALD_RATIONAL_EPS_4_B02;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B01;
    b = x*b + FRESNEL_HEALD_RATIONAL_EPS_4_B00;

    /* Compute the Numerator of the R_lm Function.      */
    c = FRESNEL_HEALD_RATIONAL_EPS_4_C02*x + FRESNEL_HEALD_RATIONAL_EPS_4_C01;
    c = x*c + FRESNEL_HEALD_RATIONAL_EPS_4_C00;

    /* Compute the Denominator of the R_lm Function.    */
    d = FRESNEL_HEALD_RATIONAL_EPS_4_D03*x + FRESNEL_HEALD_RATIONAL_EPS_4_D02;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D01;
    d = x*d + FRESNEL_HEALD_RATIONAL_EPS_4_D00;

    A = a/b-x*x;
    A *= PI_BY_TWO;
    R = c/d;
    R *= SQRT_PI_BY_2;

    cx = sgn_x*(SQRT_PI_BY_8 - R*sin(A));
    sx = sgn_x*(SQRT_PI_BY_8 - R*cos(A));

    return cx + _Complex_I*sx;
}
