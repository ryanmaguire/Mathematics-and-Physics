#include <stdio.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_ppm_plot.h>

double coeffsa[32] = {
    0.0,  341.0,    0.0, 0.0, 0.0, 0.0,  67518.0,   0.0, 0.0, 0.0,
    0.0, -398505.0, 0.0, 0.0, 0.0, 0.0, -1060200.0, 0.0, 0.0, 0.0,
    0.0,  326895.0, 0.0, 0.0, 0.0, 0.0,  10602.0,   0.0, 0.0, 0.0,
    0.0, -19.0
};

double coeffsb[31] = {
    -19.0,     0.0, 0.0, 0.0, 0.0, -10602.0,   0.0, 0.0, 0.0, 0.0,
     326895.0, 0.0, 0.0, 0.0, 0.0,  1060200.0, 0.0, 0.0, 0.0, 0.0,
    -398505.0, 0.0, 0.0, 0.0, 0.0, -67518.0,   0.0, 0.0, 0.0, 0.0,
     341.0
};

static tmpl_ComplexDouble func(tmpl_ComplexDouble z)
{
    tmpl_ComplexDouble f, g, out;

    f = tmpl_CDouble_Poly_Real_Coeffs(coeffsa, 31, z);
    g = tmpl_CDouble_Poly_Real_Coeffs(coeffsb, 30, z);
    out = tmpl_CDouble_Divide(f, g);
    return out;
}

int main(void)
{
    FILE *fp;
    unsigned int x, y, n, nfile, N;
    double z_x, z_y, norm, dN;
    double rcp_factor;
    tmpl_ComplexDouble z_0, z_1, z_2, dist;

    unsigned int size = 4*1024;
    unsigned int maxIterations = 12;

    double x_min = -100.0;
    double x_max =  100.0;
    double y_min = -100.0;
    double y_max =  100.0;
    const double eps = 1.0e-4;
    char filename[17];
    rcp_factor = 1.0/(size-1.0);
    N = 400;
    dN = 0.9;

    for (nfile = 0U; nfile < N; ++nfile)
    {
        sprintf(filename, "weird_polynomial_%03d.ppm", nfile);
        fp = fopen(filename, "w");
        fprintf(fp, "P6\n%d %d\n255\n", size, size);

        for (y=0; y<size; ++y)
        {
            z_y = (size - y - 1.0) * (y_max - y_min) * rcp_factor + y_min;
            for (x=0; x<size; ++x)
            {
                z_x = x * (x_max - x_min) * rcp_factor + x_min;
                z_0 = tmpl_CDouble_Rect(z_x, z_y);

                for(n = 0; n < maxIterations; n++)
                {
                    z_1 = func(z_0);
                    z_2 = func(z_1);
                    dist = tmpl_CDouble_Subtract(z_0, z_2);
                    norm = tmpl_CDouble_Abs(dist);

                    if(norm < eps)
                        break;
                    else
                        z_0 = z_1;
                }

                if(n == maxIterations)
                    tmpl_Color(0, 0, 0, fp);
                else
                    tmpl_RGB_Linear_Gradient(n, 0, maxIterations, fp);
            }

        }

        printf("Current: %d    Total: %d\n", nfile, N);
        fclose(fp);
        x_min *= dN;
        x_max *= dN;
        y_min *= dN;
        y_max *= dN;
    }
    return 0;
}
