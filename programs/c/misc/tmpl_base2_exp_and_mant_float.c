/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                       tmpl_base2_exp_and_mant_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the values m and b such that 1.0 <= |m| < 2.0, and the input *
 *      can be written as x = m*2^b, with m an integer.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Base2_Exp_and_Mant:                                        *
 *  Purpose:                                                                  *
 *      Computes the exponent and mantissa of the input.                      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      mant (float *):                                                       *
 *          A pointer to a float. The mantissa will be stored here.           *
 *      expo (signed int *):                                                  *
 *          A pointer to a signed int. The exponent will be stored here.      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Is_NaN (tmpl_math.h)                                       *
 *          Determines if a float is NaN.                                     *
 *      tmpl_Float_Is_Inf (tmpl_math.h)                                       *
 *          Determines if a float is infinity.                                *
 *      tmpl_Float_Abs (tmpl_math.h)                                          *
 *          Computes the absolute value of a float.                           *
 *          NOTE:                                                             *
 *              This function is only called if IEEE-754 support is not       *
 *              available and the portable algorithm is needed.               *
 *  Method:                                                                   *
 *      If IEEE-754 format is implemented, extract the exponent from the      *
 *      float, subtract 127 (which is the bias for single precision), set the *
 *      exponent part to 1 for the mantissa, and return.                      *
 *                                                                            *
 *      If IEEE-754 format is not implemented, find the binary representation *
 *      of the exponent via division. This algorithm has time complexity      *
 *      O(ln(ln(x))) for most implementations. If float has a ridiculously    *
 *      large range (greater than 10^4932), this algorithm has worst-case     *
 *      scenario O(ln(x)).                                                    *
 *  NOTE:                                                                     *
 *      There are three special cases. If the input is NaN, the exponent is   *
 *      set to 0 and the mantissa is set to NaN. If the input is infinity,    *
 *      the exponent is set to 0 and the mantissa is set to infinity. If      *
 *      x is 0, the exponent is set to zero and the mantissa is set to zero.  *
 *      If either of the pointers is NULL, nothing is done.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where the function prototype is given.                *
 *  2.) float.h:                                                              *
 *          Header file containing the FLT_MAX_10_EXP macro. This header is   *
 *          only included if IEEE-754 support is not implemented.             *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support.                                               */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  Function for computing the values m and b such that the input x is equal  *
 *  to x = m * 2^b, with 1 <= |m| < 2. This uses IEEE-754 tricks to do this   *
 *  in O(1) time.                                                             */
void tmpl_Float_Base2_Exp_and_Mant(float x, float *mant, signed int *expo)
{
    /*  Declare a variable for the IEEE-754 float union.                      */
    tmpl_IEEE754_Float w;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0F)
    {
        *mant = 0.0F;
        *expo = 0;
        return;
    }

    /*  Infinity is another special case. The mantissa will be set to         *
     *  infinity and the exponent will be set to zero.                        */
    else if (tmpl_Float_Is_Inf(x))
    {
        *mant = TMPL_INFINITYF;
        *expo = 0;
        return;
    }

    /*  The last special case is NaN. expo will be zero, and mant will be nan.*/
    else if (tmpl_Float_Is_NaN(x))
    {
        *mant = TMPL_NANF;
        *expo = 0;
        return;
    }

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  The exponent is biased by 127 = 11111111_2 = 0x7F. Subtract this.     */
    *expo = (signed int)w.bits.expo - 0x7F;

    /*  Set the exponent to 0 so that the float part now has 1.0 <= |x| < 2.  */
    w.bits.expo = 0x7FU;

    /*  Set mant to the float part of the union.                              */
    *mant = w.r;
}
/*  End of tmpl_Float_Base2_Exp_and_Mant.                                     */

#else
/*  Else #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1   */

/*  FLT_MAX_10_EXP is found here.                                             */
#include <float.h>

/*  This method does not assume IEEE-754 support, but instead of running in   *
 *  O(1) time, it runs in O(ln(m)), where m is the exponent of the input. So  *
 *  it roughly runs like O(ln(ln(max(|x|, |1/x|)))).                          */
void tmpl_Float_Base2_Exp_and_Mant(float x, float *mant, signed int *expo)
{
    /*  We'll compute the exponent using |x|, so compute this. To avoid loss  *
     *  of precision, run the computation at double precision and then        *
     *  cast to float.                                                        */
    double abs_x, mant_dbl;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0F)
    {
        *mant = 0.0F;
        *expo = 0;
        return;
    }

    /*  Infinity is another special case. The mantissa will be set to         *
     *  infinity and the exponent will be set to zero.                        */
    else if (tmpl_Float_Is_Inf(x))
    {
        *mant = TMPL_INFINITYF;
        *expo = 0;
        return;
    }

    /*  The last special case is NaN. expo will be zero, and mant will be nan.*/
    else if (tmpl_Float_Is_NaN(x))
    {
        *mant = TMPL_NANF;
        *expo = 0;
        return;
    }

    /*  If we have a non-exceptional case, compute |x|.                       */
    abs_x = tmpl_Double_Abs((double)x);

    /*  If |x| < 1,0, compute with 1/|x|. We'll then negate the exponent at   *
     *  the end of the computation.                                           */
    if (abs_x < 1.0)
        mant_dbl = 1.0 / abs_x;

    /*  If |x| >= 1.0, the exponent is non-negative. No need to invert.       */
    else
        mant_dbl = abs_x;

    /*  Initialize the exponent to zero. The value will be computed by a sum. */
    *expo = 0;

    /*  The exponent is computed via it's binary representation. We find what *
     *  powers of 2 the value is greater than, and then divide by these,      *
     *  which amounts to zeroing out that particular value in the binary      *
     *  expansion of the exponent. Because of this, for values less than      *
     *  10^4932 (which is almost certainly beyond the bounds of float for     *
     *  your implementation), we can compute the mantissa and exponent in     *
     *  O(ln(ln(x))) time. To avoid compiler warnings about constants beyond  *
     *  the range of float, use the macro FLT_MAX_10_EXP to check the largest *
     *  power of 10 allowed.                                                  */
#if FLT_MAX_10_EXP > 4932

    /*  While it is likely not the case, if float has a range larger than     *
     *  10^4932, we should use a while loop to continuously decrease the      *
     *  the exponent until it is below this value. This is for the sake of    *
     *  portability. If float has a very large range, this part of the        *
     *  algorithm runs in O(ln(x)) time, instead of O(ln(ln(x))).             */
    while (mant_dbl >= 1.1897314953572317650857593266280E4932)
    {
        mant_dbl /= 1.1897314953572317650857593266280E4932;
        *expo += 16384;
    }
#endif
#if FLT_MAX_10_EXP > 2466
    while (mant_dbl >= 1.0907481356194159294629842447338E2466)
    {
        mant_dbl /= 1.0907481356194159294629842447338E2466;
        *expo += 8192;
    }
#endif
#if FLT_MAX_10_EXP > 1233
    while (mant_dbl >= 1.0443888814131525066917527107166E1233)
    {
        mant_dbl /= 1.0443888814131525066917527107166E1233;
        *expo += 4096;
    }
#endif
#if FLT_MAX_10_EXP > 616
    while (mant_dbl >= 3.2317006071311007300714876688670E616)
    {
        mant_dbl /= 3.2317006071311007300714876688670E616;
        *expo += 2048;
    }
#endif
#if FLT_MAX_10_EXP > 308
    while (mant_dbl >= 1.7976931348623159077293051907890E308)
    {
        mant_dbl /= 1.7976931348623159077293051907890E308;
        *expo += 1024;
    }
#endif
#if FLT_MAX_10_EXP > 154
    while (mant_dbl >= 1.3407807929942597099574024998206E154)
    {
        mant_dbl /= 1.3407807929942597099574024998206E154;
        *expo += 512;
    }
#endif
#if FLT_MAX_10_EXP > 77
    while (mant_dbl >= 1.1579208923731619542357098500869E77)
    {
        mant_dbl /= 1.1579208923731619542357098500869E77;
        *expo += 256;
    }
#endif
#if FLT_MAX_10_EXP > 38
    while (mant_dbl >= 3.4028236692093846346337460743177E38)
    {
        mant_dbl /= 3.4028236692093846346337460743177E38;
        *expo += 128;
    }
#endif
#if FLT_MAX_10_EXP > 19
    while (mant_dbl >= 1.84467440737095516160E19)
    {
        mant_dbl /= 1.84467440737095516160E19;
        *expo += 64;
    }
#endif
#if FLT_MAX_10_EXP > 9
    while (mant_dbl >= 4.2949672960E9)
    {
        mant_dbl /= 4.2949672960E9;
        *expo += 32;
    }
#endif

    if (mant_dbl >= 65536.0)
    {
        mant_dbl /= 65536.0;
        *expo += 16;
    }
    if (mant_dbl >= 256.0)
    {
        mant_dbl *= 0.003906250;
        *expo += 8;
    }
    if (mant_dbl >= 16.0)
    {
        mant_dbl *= 0.0625;
        *expo += 4;
    }
    if (mant_dbl >= 4.0)
    {
        mant_dbl *= 0.25;
        *expo += 2;
    }
    if (mant_dbl >= 2.0)
    {
        mant_dbl *= 0.5;
        *expo += 1;
    }

    /*  If |x| < 1, we need to negate the exponent since we computed the      *
     *  exponent of 1 / |x|. We also need to set mant to 1 / mant. This will  *
     *  result in mant < 1, so multiply by 2 and subtract 1 from the          *
     *  exponent. This will give us the correct value 1.m * 2^b.              */
    if (abs_x < 1.0)
    {
        *expo = -*expo - 1;
        mant_dbl = 2.0 / mant_dbl;
    }

    /*  If x was negative, negate mant so it has the proper sign.             */
    if (x < 0.0F)
        mant_dbl = -mant_dbl;

    *mant = (float)mant_dbl;
}
/*  End of tmpl_Float_Base2_Exp_and_Mant.                                     */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.   */
