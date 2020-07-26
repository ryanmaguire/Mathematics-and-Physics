// Boilerplate stuff.
import settings;
import graph3;

if(!settings.multipleView)  settings.batchView=false;
settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
viewportmargin = (2, 2);

// Commonly used materials in 3D drawing.
// Material of the pretzel and the sphere.
material blob, redpipe, bluepipe;

blob = material(
    diffusepen=gray(0.7), emissivepen=gray(0.2), specularpen=gray(0.2)
);

redpipe = material(
    diffusepen=red, emissivepen=gray(0.2), specularpen=gray(0.2)
);

bluepipe = material(
    diffusepen=blue+0.3*green, emissivepen=gray(0.2), specularpen=gray(0.2)
);

// Common objects.

// The equation for a torus centered at the origin with inner radius iR and
// outer radius oR. The pair t should lie in [0,2pi]x[0,2pi]
triple TorusEquation(pair t, real iR, real oR) {
    return ((oR+iR*cos(t.y))*cos(t.x), (oR+iR*cos(t.y))*sin(t.x), iR*sin(t.y));
}
