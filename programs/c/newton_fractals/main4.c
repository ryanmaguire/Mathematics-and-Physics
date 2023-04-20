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
    struct nf_complex_roots *roots = nf_complex_poly_roots(&poly);
    unsigned int n;
    printf("%u\n", roots->number_of_roots);

    for (n = 0U; n < roots->number_of_roots; ++n)
        printf("%e + i%e\n", roots->roots[n].real, roots->roots[n].imag);

    nf_complex_roots_destroy(&roots);
}
