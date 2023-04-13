

#ifndef NF_NEWTON_H
#define NF_NEWTON_H

#include "nf_inline.h"
#include "nf_complex.h"
#include "nf_setup.h"

typedef struct nf_complex (*complex_function)(const struct nf_complex *);

NF_INLINE unsigned int
nf_newton(complex_function f, complex_function fp, struct nf_complex *z0)
{
    struct nf_complex fp_z0, factor;
    unsigned int iters = 0U;

    while (iters < nf_setup_max_iters)
    {
        factor = f(z0);

        if (nf_complex_abs(&factor) < nf_setup_eps)
          break;

        fp_z0 = fp(z0);
        nf_complex_divideby(&factor, &fp_z0);
        nf_complex_subtractfrom(z0, &factor);
        iters++;
    }

    return iters;
}

#endif
