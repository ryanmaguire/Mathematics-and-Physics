/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 19, 2020                                               *
 ******************************************************************************/

// Various modules needed for the animation.
import settings;
import graph3;
import animation;
settings.outformat="gif";

// Set render to 4 and size to 256 if you want it to render significantly
// faster. Current settings took about 2 hours to render all 200 images.
settings.render=4;
size(256);

// Details for the camera and orientation.
currentprojection=perspective(
    camera = (50, 50, 30),
    up = (0, 0, 1),
    target = (0,  0,  0),
    zoom = 0.85
);

// Function to return the Euclidean norm of a vector.
real norm(real[] Vector, int Size){
    int i;
    real normsquared = 0.0;
    for (i=0; i<Size; ++i){
        normsquared += Vector[i]^2;
    }
    return sqrt(normsquared);
}

// Necessary variables for drawing the surfaces and creating the .GIF file.
animation a;
surface s = unitsphere;

// What the ellipsoid will look like.
material blob = material(diffusepen=gray(0.7),
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

// What the plane looks like (commented out, however).
material floorblob = material(diffusepen=gray(0.8)+opacity(0.5),
                              emissivepen=gray(0.2),
                              specularpen=gray(0.2));

// Pens for drawing the polhode and herpolhode.
pen hpen = deepblue+linewidth(0.1pt);
pen ppen = deepred+linewidth(0.1pt);
pen mpen = black+linewidth(0.3pt);

// Arrow size.
real arsize = 5bp;

// Factor used in computing the moment of inertia. M is the mass.
real M = 12;
real IFactor = M/12.0;

// Number of iterations to perform and a variable for indexing.
// Is is roughly 100*2pi for convenience later.
int i;
int n = 2000;

// Increment factor used in solved ODE via Euler's method.
real diff = 0.01;

// Axes (lengths) of the ellipsoid in {x, y, z} format.
real[] EllipseAxes = {3, 4, 1};

// The moment of inertia vector for the ellipsoid.
real[] MomentOfIntertia = {
    IFactor*(EllipseAxes[1]^2 + EllipseAxes[2]^2),
    IFactor*(EllipseAxes[0]^2 + EllipseAxes[2]^2),
    IFactor*(EllipseAxes[0]^2 + EllipseAxes[1]^2)
}; 
 
// Initial conditions for the angular frequency.
real[] AngularFrequency = {1.0, 2.0, 1.0};

// Initial conditions for the Euler angles.
real[] EulerAngle = {0.1, 0.1, 0.1};

// Compute the angular momentum and the magnitude.
real[] AngularMomentum = {
    MomentOfIntertia[0]*AngularFrequency[0],
    MomentOfIntertia[1]*AngularFrequency[1],
    MomentOfIntertia[2]*AngularFrequency[2]
};

// Compute the angular momentum magnitude and kinetic energy.
real AngularMomentumMagnitude = norm(AngularMomentum, 3);
real KineticEnergy = 0.5*(
    MomentOfIntertia[0]*(AngularFrequency[0]^2)+
    MomentOfIntertia[1]*(AngularFrequency[1]^2)+
    MomentOfIntertia[2]*(AngularFrequency[2]^2)
);

// Make sure angular momentum is not zero.
assert(AngularMomentumMagnitude>0);
real Distance = sqrt(2.0*KineticEnergy)/AngularMomentumMagnitude;

// The plane the ellipsoid sits on.
real floor(pair t){
    real x = t.x;
    real y = t.y;
    return AngularMomentumMagnitude/AngularMomentum[2]*(
        Distance -
        (AngularMomentum[0]/AngularMomentumMagnitude)*x -
        (AngularMomentum[1]/AngularMomentumMagnitude)*x
    );
}

// Commenting out because not used in drawing.
// surface thefloor = surface(floor, (-0.4, -0.4), (0.5, 0.5), nx=10, ny=10);

// Functions used for Euler's method of solving Diff eqs.
real[] FrequencyDiffEQ(real[] Omega){
    real x = Omega[0];
    real y = Omega[1];
    real z = Omega[2];
    real result[] =  {
        y*z*(MomentOfIntertia[1]-MomentOfIntertia[2])/MomentOfIntertia[0],
        z*x*(MomentOfIntertia[2]-MomentOfIntertia[0])/MomentOfIntertia[1],
        x*y*(MomentOfIntertia[0]-MomentOfIntertia[1])/MomentOfIntertia[2]
    };
    return result;
}

real[] AngleDiffEQ(real[] Angles, real[] Omega){
    real phi      = Angles[0];
    real theta    = Angles[1];
    real psi      = Angles[2];
    real phidot   = (1.0/sin(theta))*(Omega[0]*sin(psi)+Omega[1]*cos(psi));
    real thetadot = Omega[0]*cos(psi)-Omega[1]*sin(psi);
    real psidot   = Omega[2]-phidot*cos(theta);
    real[] result = {phidot, thetadot, psidot};
    return result;
}

// Transforms needed to shift the ellipsoid.
real[] CurrentPerturb;
transform3 H;
real scalex  = 1.0/sqrt(MomentOfIntertia[0]);
real scaley  = 1.0/sqrt(MomentOfIntertia[1]);
real scalez  = 1.0/sqrt(MomentOfIntertia[2]);
transform3 T = scale(scalex, scaley, scalez);
real sphi, cphi, stheta, ctheta;

// Loop over the chosen time, plotting every 5th image.
// This makes the gif slightly less smooth, but saves computational time.
write("Running Computations...");
for (i=0; i<n; ++i){
    // Perform Euler's method and numerically solve ODEs.
    CurrentPerturb = FrequencyDiffEQ(AngularFrequency);
    AngularFrequency[0] += diff*CurrentPerturb[0];
    AngularFrequency[1] += diff*CurrentPerturb[1];
    AngularFrequency[2] += diff*CurrentPerturb[2];

    CurrentPerturb = AngleDiffEQ(EulerAngle, AngularFrequency);
    EulerAngle[0] += diff*CurrentPerturb[0];
    EulerAngle[1] += diff*CurrentPerturb[1];
    EulerAngle[2] += diff*CurrentPerturb[2];

    // Variables needed for the transform applied to the ellipse.
    sphi   = sin(EulerAngle[0]);
    stheta = sin(EulerAngle[1]);
    cphi   = cos(EulerAngle[0]);
    ctheta = cos(EulerAngle[1]);

    H = rotate(EulerAngle[0], (0, 0, 1))*T;
    H = rotate(EulerAngle[1], (cphi, sphi, 0))*H;
    H = rotate(EulerAngle[2], (stheta*sphi, -stheta*cphi, ctheta))*H;

    // Create the image.
    if ((i % 5) == 0) {
        save();

        // Skip the floor since it doesn't look good in .gif format.
        // draw(thefloor, surfacepen=floorblob, meshpen=black+linewidth(0.2pt));

        // Draw the ellipse with mesh lines.
        draw(H*s, surfacepen=blob, meshpen=mpen, render(merge=true));
        draw((-0.8, -0.8, -0.8)--(0.8, 0.8, 0.8), invisible);
        a.add();
        restore();
    }
}

// Render the gif.
write("Rendering GIF...");
a.movie(delay=20);
