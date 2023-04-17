
#include "cvp.hpp"

static inline cvp::complex g(cvp::complex z)
{
    // return (z*z*z - 1.0) / (2.0*z*z*z);
    // return (z*z*z - 1.0) / (3.0*z*z*z);
    // return (z*z*z - 1.0) / (2.0*z*z);
    return (z*z*z - 1.0) / (3.0*z*z);
}

static inline cvp::complex f(cvp::complex z)
{
    for (int n = 0; n < 10; ++n)
        z = g(z);
    return z;
}

int main(void)
{
    const char *name = "z_cubed_minus_one_by_two_z.ppm";
    cvp::complex_plot(f, cvp::color_wheel_from_complex, name);
    return 0;
}
