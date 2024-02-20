extern void mandelbrot(int argc, void *argv[]);

void mandelbrot(int argc, void *argv[])
{
    int nr, ni, max_iter, i, j, count;
    double rstart, istart, dr, di;
    double real, imag, rz, iz, sz2, rz2, iz2;

    int *result;

    if (argc != 8)
        return;

    nr = *(int *) argv[0];
    ni = *(int *) argv[1];
    rstart = *(double *) argv[2];
    istart = *(double *) argv[3];
    dr = *(double *) argv[4];
    di = *(double *) argv[5];
    max_iter = *(int *) argv[6];
    result = argv[7];

    for (i = 0; i < ni; i++)
    {
        imag = istart + i*di;

        for (j = 0; j < nr; j++)
        {
            real = rstart + j*dr;
            rz = 0.0;
            iz = 0.0;
            sz2 = 0.0;

            count = 0;

            while (count < max_iter)
            {
                if (sz2 < 4.0)
                    break;

                rz2 = rz * rz;
                iz2 = iz * iz;
                iz = 2.0 * rz * iz + imag;
                rz = rz2 - iz2 + real;
                sz2 = rz2 + iz2;
                count++;
            }

            *result = count;
            result ++;
        }
    }
}
