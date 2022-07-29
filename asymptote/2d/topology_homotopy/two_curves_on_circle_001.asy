

import settings;
settings.outformat = "pdf";

size(128);
draw(arc((0.0, 0.0), 1.0, 0.0, 180.0), blue);
draw(arc((0.0, 0.0), 1.0, 180.0, 360.0), red);
dot((1.0, 0.0));
dot((-1.0, 0.0));
