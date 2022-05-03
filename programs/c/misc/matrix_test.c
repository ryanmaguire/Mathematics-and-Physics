#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

struct matrix {
    double *data;
    unsigned int width;
    unsigned int height;
};

static struct matrix create_matrix(unsigned int width, unsigned int height, ...)
{
    struct matrix out;
    unsigned int x, y;
    va_list ap;
    double *vec;

    if ((height == 0U) || (width == 0U))
    {
        out.height = 0U;
        out.width = 0U;
        out.data = NULL;
        return out;
    }

    out.height = height;
    out.width = width;
    out.data = malloc(sizeof(*out.data) * width * height);
    va_start(ap, height);

    for (y = 0U; y < height; ++y)
    {
        vec = va_arg(ap, double *);
        for (x = 0U; x < width; ++x)
        {
            out.data[x + y*width] = vec[x];
        }
    }

    va_end(ap);
    return out;
}

static void print_matrix(struct matrix mat)
{
    unsigned int x, y;

    for (y = 0U; y < mat.height; ++y)
    {
        for (x = 0U; x < mat.width; ++x)
        {
            printf("%f ", mat.data[x + y*mat.width]);
        }
        printf("\n");
    }
}

int main(void)
{
    double a1[3] = {1.0, 2.0, 3.0};
    double a2[3] = {4.0, 5.0, 6.0};
    struct matrix mat = create_matrix(3, 2, a1, a2);

    /*  This works with C99 compatible compilers.
     *      struct matrix mat = create_matrix(3, 2, (double[3]){1.0, 2.0, 3.0}, (double[3]){4.0, 5.0, 6.0});
     */
    print_matrix(mat);
    return 0;
}






