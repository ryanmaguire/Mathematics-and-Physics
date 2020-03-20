// Some boiler plate stuff.
import settings;
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

path p;
real xshift = 1.2;
real yshift = 0.6;
real arsize = 5bp;

p = scale(0.1, 0.15)*arc((0.0, 0.0), 1.0, -90, 90);
draw(shift(xshift, yshift)*p);

p = scale(0.1, 0.15)*arc((0.0, 0.0), 1.0, 90, 270);
draw(shift(xshift, yshift)*p, dashed);

p = (0.5, 0.38){SE}..(1.2, 0.1){E}..(1.9, 0.38){NE};
draw(p);

p = (1.2, 0.1){W}..(0.2, 0.3){NW}..
    (1.2, 0.75) {dir(0)}..  (2.2, 0.3){SW}..cycle;
draw(p);

p = (0.64, 0.267){NE}..(1.2, 0.45)..(1.76, 0.267){SE};
draw(p);