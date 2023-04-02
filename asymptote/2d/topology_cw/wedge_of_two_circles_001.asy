import settings;
settings.outformat = "pdf";

size(128);
draw(circle((-1.0, 0.0), 1.0));
draw(circle((1.0, 0.0), 1.0));
filldraw(circle((0.0, 0.0), 0.05), blue, black);

