import settings;
import tube;
import graph3;
import palette;
settings.render=8;

size(200, 200);

// Declare variable for the square root of three.
real SQRT_3 = sqrt(3.0);

// Set camera location and orientation.
currentprojection=perspective(
    camera=(70, 70, 70),
    up=(0, 0, 1),
    target=(0, 0, 0),
    zoom=1.0
);

// Set up the lighting.
currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {3000Z+3000X+3*Y}
);

// The trefoil knot will be a tube, so use unitcircle.
path section=scale(0.05)*unitcircle;

// The material used for the surface.
material blob = material(diffusepen=gray(0.5)+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.1));

// Material for the knot.
material pipe = material(diffusepen=green,
                         emissivepen=gray(0.1),
                         specularpen=gray(0.3));

// Rotation matrices to make life easier.
transform3 T1 = rotate(120, Z);
transform3 T2 = rotate(240, Z);

// Bottom points of the hexagon.
triple aB = (-1, SQRT_3, 0);
triple bB = (1, SQRT_3, 0);
triple cB = (2, 0, 0);
triple dB = (1, -SQRT_3, 0);
triple eB = (-1, -SQRT_3, 0);
triple fB = (-2, 0, 0);

// Top points of the hexagon.
triple aT = (-1, SQRT_3, 2);
triple bT = (1, SQRT_3, 2);
triple cT = (2, 0, 2);
triple dT = (1, -SQRT_3, 2);
triple eT = (-1, -SQRT_3, 2);
triple fT = (-2, 0, 2);

// Function to return the "right" tube.
triple Tube1a(real t) {
    if (t<0) return bB*(t+1)-cB*t;
    else if ((t>=0) && (t<1)){
        return (cos(pi*t), sin(pi*t)+SQRT_3, 2*t);
    }
    else return aT*(2-t)+fT*(t-1);
}

// Function to return the "left" tube.
triple Tube1b(real t) {
    if (t<0) return aB*(t+1)-fB*t;
    else if ((t>=0) && (t<1)){
        return (-cos(pi*t), 0.25*sin(pi*t)+SQRT_3, 2*t);
    }
    else return bT*(2-t)+cT*(t-1);
}

// Smoothly connect the dots between the two tubes.
triple Surf1(pair t) {
    return t.y*Tube1a(t.x)+(1-t.y)*Tube1b(t.x);
}

// Draw everything.
path3 p1=   graph(Tube1a, -0.5, 1.5, n=1000, operator ..);
path3 p2=   graph(Tube1b, -0.5, 1.5, n=1000, operator ..);
path3 p3=T1*graph(Tube1a, -0.5, 1.5, n=1000, operator ..);
path3 p4=T1*graph(Tube1b, -0.5, 1.5, n=1000, operator ..);
path3 p5=T2*graph(Tube1a, -0.5, 1.5, n=1000, operator ..);
path3 p6=T2*graph(Tube1b, -0.5, 1.5, n=1000, operator ..);

surface s1=   surface(Surf1, (0,0), (1,1), 1000, 20, Spline);
surface s2=T1*surface(Surf1, (0,0), (1,1), 1000, 20, Spline);
surface s3=T2*surface(Surf1, (0,0), (1,1), 1000, 20, Spline);
surface bot=surface(aB--bB--cB--dB--eB--fB--cycle);
surface top=surface(aT--bT--cT--dT--eT--fT--cycle);

draw(tube(p1,section), light=currentlight, surfacepen=pipe);
draw(tube(p2,section), light=currentlight, surfacepen=pipe);
draw(tube(p3,section), light=currentlight, surfacepen=pipe);
draw(tube(p4,section), light=currentlight, surfacepen=pipe);
draw(tube(p5,section), light=currentlight, surfacepen=pipe);
draw(tube(p6,section), light=currentlight, surfacepen=pipe);

draw(s1,  render(merge=true), light=currentlight, surfacepen=blob);
draw(s2,  render(merge=true), light=currentlight, surfacepen=blob);
draw(s3,  render(merge=true), light=currentlight, surfacepen=blob);
draw(bot, render(merge=true), light=currentlight, surfacepen=blob);
draw(top, render(merge=true), light=currentlight, surfacepen=blob);