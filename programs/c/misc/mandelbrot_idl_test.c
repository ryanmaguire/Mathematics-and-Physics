void mandelbrot(int argc, void *argv[]){
    int nr = *(int *) argv[0];
    int ni = *(int *) argv[1];
    double rstart = *(double *) argv[2];
    double istart = *(double *) argv[3];
    double dr = *(double *) argv[4];
    double di = *(double *) argv[5];
    int max_iter = *(int *) argv[6];
    int *result =  argv[7];
    int i, j, count;
    double real, imag, rz, iz, sz2, rz2, iz2;
        for (i=0; i<ni; i++) {
        imag = istart + i*di;
        for (j=0; j<nr; j++) {
            real = rstart + j*dr;
            rz = 0.;
            iz = 0.;
            sz2 = 0.;

            count = 0;
            while ((count < max_iter) && (sz2 < 4.0)) {
                rz2 = rz * rz;
                iz2 = iz * iz;
                iz = 2.0 * rz * iz + imag;
                rz = rz2 - iz2 + real;
                sz2 = rz2 + iz2;
                count++;
            }
            *result++ = count;
        }
    }
}
