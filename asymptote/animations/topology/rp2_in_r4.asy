import graph3;
import tube;
import palette;
import animation;
animation a;
int n_frames = 100;
real w = -1.0;
real dw = 2.0 / (real)n_frames;
real dy = 0.01;

real R = 0.05;
surface s = scale(R, R, R)*unitsphere;

real x, y, z;

/*  Size of the created image.                                                */
size(1024);

/*  Camera setup.                                                             */
currentprojection = perspective(
    camera = (20, -20,40),
    up     = (0,  -1, 0),
    target = (0,   0, 0),
    zoom   = 1
);

/*  Lighting for the drawing.                                                 */
currentlight = light(
    new pen[] {
        rgb(0.38, 0.38, 0.45),
        rgb(0.6, 0.6, 0.67),
        rgb(0.5, 0.5, 0.57)
    },
    specularfactor=3,
    new triple[] {
        (-2,-1.5,-0.5),
        (2,1.1,-2.5),
        (-0.5,0,2)
    }
);

/*  Loop over the frames and create the GIF.                                  */
for (w = -1.0; w < 1.0; w += dw)
{
    /*  Create the surface.                                                   */
    for (y = -1.0; y < 1.0; y += dy)
    {
        if (y == 0.0)
            continue;

        z = w/y;
        x = 1.0 - y*y - z*z;

        if (x < 0.0)
            continue;

        x = sqrt(x);
        draw(shift(x, y, z)*s, render(merge=true));
        draw(shift(-x, y, z)*s, render(merge=true));
    }
    draw(unitsphere, surfacepen=invisible);

    /*  Add this frame to the GIF.                                            */
    a.add();

    /*  Erase the screen for the next image.                                  */
    erase();
}

/*  Render the GIF.                                                           */
a.movie(delay=50);
