#include "nf_inline.h"
#include "nf_ppm.h"
#include "nf_setup.h"
#include "nf_complex.h"
#include "nf_color.h"
#include "nf_newton.h"
#include "nf_complex_poly.h"
#include <stdio.h>

static struct nf_complex coeffs[4] = {
    {-1.0, 0.0},
    {0.0, 0.0},
    {0.0, 0.0},
    {1.0, 0.0}
};

static const unsigned int degree = sizeof(coeffs)/sizeof(coeffs[0]) - 1U;

int main(void)
{
    const struct nf_complex_poly poly = {coeffs, degree};
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

            iters = nf_newton_poly(&poly, &z);

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
