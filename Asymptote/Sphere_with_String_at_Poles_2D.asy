// Some boiler plate stuff.
import settings;
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

pair O     = (0,  0);
pair nPole = (0,  1);
pair sPole = (0, -1);
pair mid   = (1.5, 0);

draw(unitcircle);

draw(nPole{N}..mid{S}..sPole{N});
draw(scale(1.0, 0.3)*arc(O, 1, 180, 360));
draw(scale(1.0, 0.3)*arc(O, 1, 0, 180), dashed);
dot(nPole);
dot(sPole);
