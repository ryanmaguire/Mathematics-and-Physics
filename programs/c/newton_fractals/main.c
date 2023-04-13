#include "nf_inline.h"
#include "nf_ppm.h"
#include "nf_setup.h"
#include "nf_complex.h"
#include "nf_color.h"
#include "nf_newton.h"
#include <stdio.h>

NF_INLINE struct nf_complex
f(const struct nf_complex *z)
{
    struct nf_complex out = nf_complex_square(z);
    nf_complex_multiplyby(&out, z);
    out.real -= 1.0;
    return out;
}

NF_INLINE struct nf_complex
fp(const struct nf_complex *z)
{
    struct nf_complex out = nf_complex_square(z);
    out.real *= 3.0;
    out.imag *= 3.0;
    return out;
}

int main(void)
{
    unsigned int x, y;
    unsigned int iters;
    double scale;
    struct nf_complex z;
    struct nf_color c;
    struct nf_ppm ppm = nf_ppm_create("newton_fractal.ppm");
    nf_ppm_init(&ppm);

    for (y = 0U; y < nf_setup_ysize; ++y)
    {
        const double imag = nf_setup_ymin + nf_setup_py_factor*(double)y;

        for (x = 0U; x < nf_setup_xsize; ++x)
        {
            z.real = nf_setup_xmin + nf_setup_px_factor*(double)x;
            z.imag = imag;

            iters = nf_newton(f, fp, &z);

            if (z.real > 0.0)
                c = nf_blue;
            else if (z.imag > 0.0)
                c = nf_red;
            else
                c = nf_green;

            scale = (double)(nf_setup_max_iters - iters)*nf_setup_color_scale;
            nf_color_scaleby(&c, scale);
            nf_color_write_to_ppm(&c, &ppm);
        }
    }

    nf_ppm_close(&ppm);
    return 0;
}
