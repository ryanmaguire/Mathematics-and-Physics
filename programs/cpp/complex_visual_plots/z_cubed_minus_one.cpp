
#include "cvp.hpp"

static inline cvp::complex f(cvp::complex z)
{
    return z*z*z - 1.0;
}

int main(void)
{
    const char *name = "z_cubed_minus_one.ppm";
    cvp::complex_plot(f, cvp::color_wheel_from_complex, name);
    return 0;
}
