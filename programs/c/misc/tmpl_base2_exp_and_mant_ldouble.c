#include <libtmpl/include/tmpl_math.h>

#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1
void tmpl_LDouble_Base2_Exp_and_Mant(long double x,
                                     long double *mant,
                                     signed long int *expo)
{
    tmpl_IEEE754_LDouble w;

    if (x == 0.0L)
    {
        *mant = 0.0L;
        *expo = 0L;
        return;
    }
    else if (tmpl_LDouble_Is_Inf(x))
    {
        *mant = TMPL_INFINITYL;
        *expo = 0L;
        return;
    }
    else if (tmpl_LDouble_Is_NaN(x))
    {
        *mant = TMPL_NANL;
        *expo = 0L;
        return;
    }

    w.r = x;

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_AMD64 || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_I386  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_AARCH64

    *expo = (signed long int)w.bits.expo - 0x3FFF;
    w.bits.expo = 0x3FFF;
    *mant = w.r;
#else
    *expo = (signed long int)w.bits.expo - 0x3FF;

    w.bits.expo = 0x3FFU;
    *mant = w.r;
#endif
}

#else
#include <float.h>

void tmpl_LDouble_Base2_Exp_and_Mant(long double x,
                                     long double *mant,
                                     signed long int *expo)
{
    long double abs_x;
    
    if (x == 0.0L)
    {
        *mant = 0.0L;
        *expo = 0L;
        return;
    }

    abs_x = tmpl_LDouble_Abs(x);

    if (abs_x < 1.0L)
        *mant = 1.0L / abs_x;
    else
        *mant = abs_x;


    *expo = 0L;

#if LDBL_MAX_10_EXP > 4932
    while (*mant >= 1.1897314953572317650857593266280E4932L)
    {
        *mant /= 1.1897314953572317650857593266280E4932L;
        *expo += 16384L;
    }
#endif
#if LDBL_MAX_10_EXP > 2466
    while (*mant >= 1.0907481356194159294629842447338E2466L)
    {
        *mant /= 1.0907481356194159294629842447338E2466L;
        *expo += 8192L;
    }
#endif
#if LDBL_MAX_10_EXP > 1233
    while (*mant >= 1.0443888814131525066917527107166E1233L)
    {
        *mant /= 1.0443888814131525066917527107166E1233L;
        *expo += 4096L;
    }
#endif
#if LDBL_MAX_10_EXP > 616
    while (*mant >= 3.2317006071311007300714876688670E616L)
    {
        *mant /= 3.2317006071311007300714876688670E616L;
        *expo += 2048L;
    }
#endif
#if LDBL_MAX_10_EXP > 308
    while (*mant >= 1.7976931348623159077293051907890E308L)
    {
        *mant /= 1.7976931348623159077293051907890E308L;
        *expo += 1024L;
    }
#endif
#if LDBL_MAX_10_EXP > 154
    while (*mant >= 1.3407807929942597099574024998206E154L)
    {
        *mant /= 1.3407807929942597099574024998206E154L;
        *expo += 512;
    }
#endif
#if LDBL_MAX_10_EXP > 77
    while (*mant >= 1.1579208923731619542357098500869E77L)
    {
        *mant /= 1.1579208923731619542357098500869E77L;
        *expo += 256;
    }
#endif
#if LDBL_MAX_10_EXP > 38
    while (*mant >= 3.4028236692093846346337460743177E38L)
    {
        *mant /= 3.4028236692093846346337460743177E38L;
        *expo += 128L;
    }
#endif
#if LDBL_MAX_10_EXP > 19
    while (*mant >= 1.84467440737095516160E19L)
    {
        *mant /= 1.84467440737095516160E19L;
        *expo += 64L;
    }
#endif
#if LDBL_MAX_10_EXP > 9
    while (*mant >= 4.2949672960E9L)
    {
        *mant /= 4.2949672960E9L;
        *expo += 32L;
    }
#endif

    if (*mant >= 65536.0L)
    {
        *mant /= 65536.0L;
        *expo += 16L;
    }
    if (*mant >= 256.0L)
    {
        *mant *= 0.003906250L;
        *expo += 8L;
    }
    if (*mant >= 16.0L)
    {
        *mant *= 0.0625L;
        *expo += 4L;
    }
    if (*mant >= 4.0L)
    {
        *mant *= 0.25L;
        *expo += 2L;
    }
    if (*mant >= 2.0L)
    {
        *mant *= 0.5L;
        *expo += 1L;
    }

    if (abs_x < 1.0L)
    {
        *expo = -*expo;
        *mant = 1.0L / *mant;
    }

    if (*mant < 1.0L)
    {
        *mant *= 2.0L;
        *expo -= 1L;
    }

    if (x < 0.0L)
        *mant = -*mant;
}

#endif
