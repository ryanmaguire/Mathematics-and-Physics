#include "nf.h"

int main(void)
{
    struct nf_complex coeffs[4] = {
        {-1.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {1.0, 0.0}
    };
    const char *name = "newton_fractal_z_cubed_minus_one.ppm";
    COMPLEX_RUN(coeffs, name);
    return 0;
}
