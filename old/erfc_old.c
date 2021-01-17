/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <rss_ringoccs/include/rss_ringoccs_math.h>

/*  These macros are for computing the error function following the methods   *
 *  in Abramowitz and Stegun's classic text. The maximum error is less than   *
 *  or equal to 10^-7. The alternate algorithm, provided by Sergei Winitzki,  *
 *  has maximum "relative" error or 0.00035 for all real x, which is very     *
 *  good since the error function rapidly approaches 1 for large x.           */
#define __do_erf_poly(x, t, poly)                                              \
    t = 1.0/(1.0 + 0.3275911*x);                                               \
    poly = 1.061405429 * t - 1.453152027;                                      \
    poly = t*poly + 1.421413741;                                               \
    poly = t*poly - 0.284496736;                                               \
    poly = t*poly + 0.254829592;                                               \
    poly = t*poly;

#define _define_abramowitz_and_stegun_erf(type, Name)                          \
type rssringoccs_##Name##_Erf(type x)                                          \
{                                                                              \
    /*  Declare necessary variables. C89 requires declarations at the top.   */\
    type erf_x, t, poly, exp_minus_x_sq, abs_x;                                \
                                                                               \
    /*  The function is odd in x so compute abs_x and use this.              */\
    abs_x = rssringoccs_Abs_##Name(x);                                         \
                                                                               \
    /*  Following Abramowitz and Stegun, we first compute exp(-x^2).         */\
    exp_minus_x_sq = rssringoccs_Exp_##Name(-x*x);                             \
                                                                               \
    /*  Next we get the polynomial in terms of t = 1/(1+px) where p is a     */\
    /*  specific constant (see Abramowitz and Stegun).                       */\
    __do_erf_poly(abs_x, t, poly);                                             \
    erf_x = 1.0 - poly*exp_minus_x_sq;                                         \
                                                                               \
    /*  Erf is an odd function, so multiply by the sign of x.                */\
    erf_x = (erf_x ? x>0 : -erf_x);                                            \
    return erf_x;                                                              \
}

/*  If you would like to compile this algorithm, as opposed to Winitzki's,    *
 *  uncomment out these lines and comment out the Winitzki ones. Do not leave *
 *  both uncommented!                                                         */

/*
 * _define_abramowitz_and_stegun_erf(float, Float)
 * _define_abramowitz_and_stegun_erf(double, Double)
 * _define_abramowitz_and_stegun_erf(long double, LongDouble)
 */

/*  The factor 8(pi-3)/3pi(4-pi) occurs in the approximation of erf.          */

/*
 * #define _erf_alpha_factor 0.14001228868666660600424949138612
 */

/*  A better alpha value is given by 0.147, which reduces relative error to   *
 *  approximately 0.00013.                                                    */
#define _erf_alpha_factor 0.1470
#define FOUR_BY_PI        1.27323954473516268615107010698011

#define _define_winitzki_erf(type, Name)                                       \
type rssringoccs_##Name##_Erf(type x)                                          \
{                                                                              \
    /*  Declare necessary variables. C89 requires declarations at the top.   */\
    type erf_x, rat, num, denom, x_sq, val;                                    \
                                                                               \
    /*  Compute (4/pi + alpha x^2)/(1+alpha x^2).                            */\
    x_sq = x*x;                                                                \
    num = FOUR_BY_PI + _erf_alpha_factor*x_sq;                                 \
    denom = 1.0 + _erf_alpha_factor*x_sq;                                      \
    rat = num/denom;                                                           \
                                                                               \
    /*  The approximation is +/- sqrt(1 - exp(-x^2 * rat)) depending on the  */\
    /*  sign of x, so compute this.                                          */\
    val = rssringoccs_Exp_##Name(-rat*x_sq);                                   \
    erf_x = rssringoccs_Sqrt_##Name(1.0-val);                                  \
    erf_x = (x < 0.0 ? -erf_x : erf_x);                                        \
    return erf_x;                                                              \
}

_define_winitzki_erf(float, Float)
_define_winitzki_erf(double, Double)
_define_winitzki_erf(long double, LongDouble)
