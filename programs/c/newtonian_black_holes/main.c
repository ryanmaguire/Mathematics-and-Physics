/*  All header files for nbh are including here.                              */
#include "nbh.h"

/*  Main function for performing the raytracing.                              */
int main(void)
{
    /*  Name of the output ppm file.                                          */
    const char *name = "newtonian_black_hole.ppm";
#ifdef _OPENMP
    nbh_prun(nbh_gravity, nbh_stop, nbh_checker_board, nbh_euler_path, name);
#else
    nbh_run(nbh_gravity, nbh_stop, nbh_checker_board, nbh_euler_path, name);
#endif
    return 0;
}
