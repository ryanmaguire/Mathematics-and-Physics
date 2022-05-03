import math, cmath;

width = 2048;
height = 2048;
imax = 100;
zmax = 150;
x_factor = 2.0/(width - 1.0);
y_factor = 2.0/(height - 1.0);

fp = open("swipecat_fractal.ppm", "w");
fp.write("P3\n%d %d\n255\n" % (width, height));

for y in range(height):
    z_y = 1.0 - y_factor*y;
    for x in range(width):
        z_x = x_factor*x - 1.0;
        c = complex(z_x, z_y);

        if (abs(c) >= 1.0):
            fp.write("%u %u %u\n" % (255, 255, 255));
            continue;

        c = c / (1.0 - (c.real*c.real + c.imag*c.imag));
        z = 0.0;
        backgnd = 0;
        for its in range(imax):
            z = 0.5*math.pi * (cmath.exp(z) - z) + c;
            if abs(z.real) >= zmax:
                backgnd = math.log(abs(its - math.log(math.log(abs(z.real) + 1))) / 3) / 3.25;
                break;

        val = max(0.0, 1.0 - abs(1.0 - backgnd));
        if (backgnd <= 1.0):
            r = int(255.0 * val**4);
            g = int(255.0 * val**2.5);
            b = int(255.0 * val);
        else:
            r = int(255.0 * val);
            g = int(255.0 * val**1.5);
            b = int(255.0 * val**3);

        fp.write("%u %u %u\n" % (r, g, b));
fp.close();
