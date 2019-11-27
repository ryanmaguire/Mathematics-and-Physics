#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void color(int red, int green, int blue)
{
    fputc((char)red, stdout);
    fputc((char)green, stdout);
    fputc((char)blue, stdout);
}

int main(int argc, char *argv[])
{
    int w = 4*512;
    int h = 4*512;
    int brightness, x, y, i;
    double pr, pi, z;
    double newRe, newIm, oldRe, oldIm;
    double zoom = 1;
    double moveX = -1.0;
    double moveY = 0.0;
    int maxIterations = 1000;

    printf("P6\n# CREATOR: E.T / mandel program\n");
    printf("%d %d\n255\n",w,h);

    //loop through every pixel
    for(y = 0; y < h; y++)
    for(x = 0; x < w; x++)
    {
        //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
        pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
        pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
        newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0

        //start the iteration process
        for(i = 0; i < maxIterations; i++)
        {
            //remember value of previous iteration
            oldRe = newRe;
            oldIm = newIm;

            //the actual iteration, the real and imaginary part are calculated
            newRe = oldRe * oldRe - oldIm * oldIm + pr;
            newIm = 2 * oldRe * oldIm + pi;

            //if the point is outside the circle with radius 2: stop
            if((newRe * newRe + newIm * newIm) > 16)
                break;
        }

        if(i == maxIterations) {
            color(0, 0, 0);
        }
        else {
            z = sqrt(newRe * newRe + newIm * newIm);
            brightness = 256.0*log2(1.75+i-log2(log2(z)))/log2(maxIterations);
            color(brightness, brightness, 255);
        }
    }
    return 0;
}
