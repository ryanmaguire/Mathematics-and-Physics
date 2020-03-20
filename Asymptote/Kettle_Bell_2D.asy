// Some boiler plate stuff.
import settings;
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

pair Origin  = (0.0,  0.);
pair equator = (1.0,  0.);
pair mid     = (1.5,  0.);

draw(unitcircle);

draw(equator{N}..mid{S}..equator{N});
draw(scale(1.0, 0.3)*arc(Origin, 1, 180, 360));
draw(scale(1.0, 0.3)*arc(Origin, 1, 0, 180), dashed);
dot(equator);