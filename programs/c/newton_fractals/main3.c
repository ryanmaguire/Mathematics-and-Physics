#include "nf_inline.h"
#include "nf_ppm.h"
#include "nf_setup.h"
#include "nf_complex.h"
#include "nf_color.h"
#include "nf_newton.h"
#include "nf_complex_poly.h"
#include "nf_real_poly.h"
#include "nf_complex_roots.h"
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
    unsigned int iters, ind;
    double scale;
    struct nf_complex z;
    struct nf_ppm ppm = nf_ppm_create("newton_fractal3.ppm");
    struct nf_complex_roots *roots = nf_complex_poly_roots(&poly);
    struct nf_color *colors = nf_complex_roots_get_colors(roots->number_of_roots);
    nf_ppm_init(&ppm);
    struct nf_color c;

    for (y = 0U; y < nf_setup_ysize; ++y)
    {
        const double imag = nf_setup_ymin + nf_setup_py_factor*(double)y;

        for (x = 0U; x < nf_setup_xsize; ++x)
        {
            z.real = nf_setup_xmin + nf_setup_px_factor*(double)x;
            z.imag = imag;

            iters = nf_newton_complex_poly(&poly, &z);

            for (ind = 0U; ind < roots->number_of_roots; ++ind)
                if (nf_complex_dist(&z, &roots->roots[ind]) < nf_setup_eps)
                {
                    c = colors[ind];
                    break;
                }

            scale = (double)(nf_setup_max_iters - iters)*nf_setup_color_scale;
            nf_color_scaleby(&c, scale);
            nf_color_write_to_ppm(&c, &ppm);
        }
    }

    nf_ppm_close(&ppm);
    return 0;
}
