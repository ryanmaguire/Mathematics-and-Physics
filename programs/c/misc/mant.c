#include <stdio.h>
#include <math.h>
#include <float.h>

static const double vals[9] = {
    4.00000000000000000e+00,
    1.60000000000000000e+01,
    2.56000000000000000e+02,
    6.55360000000000000e+04,
    4.29496729600000000e+09,
    1.84467440737095516e+19,
    3.40282366920938463e+38,
    1.15792089237316195e+77,
    1.34078079299425971e+154
};

void get_mant_and_exp(double x, double *mant, signed int *expo)
{
    double abs_x = (x > 0 ? x : -x);
    unsigned int n;

    if (abs_x == 0.0)
    {
        *mant = 0.0;
        *expo = 0;
        return;
    }

    *mant = (abs_x > 1.0 ? abs_x : 1.0 / abs_x);
    *expo = 0;

    for (n = 0; n < 9; ++n)
    {
        while (*mant > vals[n])
        {
            *mant /= vals[n];
            *expo += 2 << n;
        }
    }

    while (*mant > 1.0)
    {
        *mant *= 0.5;
        *expo += 1;
    }

    if (abs_x < 1.0)
    {
        *expo = -*expo - 1;
        *mant = 2.0 / *mant;
    }

    if (x < 0.0)
        *mant = -*mant;
}

int main(void)
{
    signed int expo;
    double mant;
    double y;
    unsigned long int n;
    unsigned long int N = 1E8;
    double x = 0.0;
    double dx = 0.5*DBL_MAX / (double)N;
    double max_abs = 0.0;
    double tmp;


    for (n = 0; n < N; ++n)
    {
        get_mant_and_exp(x, &mant, &expo);
        y = mant * pow(2.0, expo);
        tmp = fabs(y - x);
        if (max_abs < tmp)
            max_abs = tmp;
        x += dx;

    }
    printf("Max Absolute Error = %e\n", max_abs);

    return 0;
}

