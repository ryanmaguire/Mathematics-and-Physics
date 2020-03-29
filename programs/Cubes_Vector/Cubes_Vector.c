#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define   BORDER  2
#define   XC(x,y,z) ((x)*16 + (y)*12)
#define   YC(x,y,z) ((x)*6 - (y)*8 - (z)*17)

static int xt = 0;
static int yt = 0;

static int white      = 0xFFFFFF;
static int blue_green = 0x00AAFF;
static int red        = 0xFF0000;
static int black      = 0x000000;

static void fcube(FILE *out, const int x, const int y,
                  const int z, const int fill)
{
    const int xc = xt + XC(x, y, z);
    const int yc = yt + YC(x, y, z);
    fprintf(out, "<path d=\"M %d %d l 16 6 l 12 -8 0 -17 -16 -6 -12 8 z\"\
                  fill=\"#%06x\" stroke=\"black\" />\n", xc, yc, fill);
    fprintf(out, "<path d=\"M%d, %dl16, 6, 12, -8m-12, 8l0, 17\"\
                 fill=\"none\" stroke=\"black\" />\n", xc, yc-17);
}

static unsigned long rrmin = 1;
static unsigned long rrmax = 4;
static int           size  = 3;
static int           center = 0;

static int surface(const int x, const int y, const int z)
{
    /* Doubled coordinates: */
    const long dx = 2*x - center,
               dy = 2*y - center,
               dz = 2*z - center;
    const unsigned long rr = dx*dx + dy*dy + dz*dz;

    return (rrmin <= rr) && (rr <= rrmax);
}

int main(int argc, char *argv[])
{
    int  width, height;
    int  x, y, z;

    /* Calculate coordinate range. */
    int xmin = XC(0,0,0);
    int ymin = YC(0,0,0);
    int xmax = XC(0,0,0);
    int ymax = YC(0,0,0);

    for (z = 0; z <= size; z++)
        for (y = 0; y <= size; y++)
            for (x = 0; x <= size; x++) {
                const int xc = XC(x,y,z);
                const int yc = YC(x,y,z);
                if (xc < xmin) xmin = xc;
                if (xc > xmax) xmax = xc;
                if (yc < ymin) ymin = yc;
                if (yc > ymax) ymax = yc;
            }

    xt = BORDER - xmin;
    width = xmax - xmin + 2*BORDER;

    yt = BORDER - ymin;
    height = ymax - ymin + 2*BORDER;

    center = size - 1;

    /* SVG preamble. */
    printf("<?xml version=\"1.0\"?>\n");
    printf("<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 %d %d\">\n", width, height);
    printf("<path d=\"M%d,%dL%d,%d,%d,%d,%d,%d,%d,%d,%d,%dz\"\
            fill=\"red\" stroke=\"#000000\"/>\n",
            xt+XC(   0,   0,   0), yt+YC(   0,   0,   0),
            xt+XC(size,   0,   0), yt+YC(size,   0,   0),
            xt+XC(size,size,   0), yt+YC(size,size,   0),
            xt+XC(size,size,size), yt+YC(size,size,size),
            xt+XC(0,   size,size), yt+YC(   0,size,size),
            xt+XC(0,      0,size), yt+YC(   0,   0,size));
    printf("<path d=\"M%d,%dL%d,%d,%d,%dM%d,%dL%d,%d\" fill=\"none\" stroke=\"#666666\"/>\n",
            xt+XC(   0,   0,   0), yt+YC(   0,   0,   0),
            xt+XC(   0,size,   0), yt+YC(   0,size,   0),
            xt+XC(size,size,   0), yt+YC(size,size,   0),
            xt+XC(   0,size,   0), yt+YC(   0,size,   0),
            xt+XC(   0,size,size), yt+YC(   0,size,size));
    for (z = 0; z < size; z++)
        for (y = size - 1; y >= 0; y--)
            for (x = 0; x < size; x++)
                if (surface(x,y,z)) fcube(stdout, x, y, z, blue_green);
    printf("</svg>\n");

    return EXIT_SUCCESS;
}