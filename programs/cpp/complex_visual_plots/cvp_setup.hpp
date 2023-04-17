

#ifndef CVP_SETUP_HPP
#define CVP_SETUP_HPP

namespace cvp {
    namespace setup {
        const double xmin = -2.0;
        const double xmax = +2.0;
        const double ymin = -2.0;
        const double ymax = +2.0;
        const unsigned int xsize = 1024U;
        const unsigned int ysize = 1024U;
        const double pxfactor = (xmax - xmin) / static_cast<double>(xsize);
        const double pyfactor = (ymax - ymin) / static_cast<double>(ysize);
    }
}

#endif
