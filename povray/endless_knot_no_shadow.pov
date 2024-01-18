/******************************************************************************
 *                                  LICENSE                                   *
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
 *  This is a modification of Eder Porto's drawing in POV-Ray.                *
 *  Render options used:                                                      *
 *      povray Antialias=True Height=512 Width=512 endless_knot.pov           *
 ******************************************************************************/
#include "colors.inc"

background {
    color White
}

global_settings {
    assumed_gamma 1.0
}

camera {
    location <0.0, 0.0, -25.0>
    right <1.0, 0.0, 0.0>
    up <0.0, 1.0, 0.0>
    look_at <0.0, 0.0, 0.0>
    angle 5.0
}

/*  Light cast on to the knot.                                                */
light_source {
    <0.0, 20.0, -50.0>
    color White
    area_light <5.0, 0.0, 0.0>, <0.0, 5.0, 0.0>, 10, 10
    adaptive 3
}

/*  Thickness of the tube used to sweep out the 7_4 knot (the endless knot).  */
#declare TUBE_THICKNESS = 0.07;

/*  Spline sweep through a bunch of data points. These points were found by   *
 *  Eder Porto. One can use the Lissajous parameterization for the endless    *
 *  knot, but it doesn't look quite the same. These splining points yield a   *
 *  very pleasant image.                                                      */
sphere_sweep {
    cubic_spline 110,
    <-0.846662727, -0.189982364, +0.112322182>, TUBE_THICKNESS
    <-0.849324727, -0.284050273, +0.059746545>, TUBE_THICKNESS
    <-0.822448182, -0.365780545, -0.005013182>, TUBE_THICKNESS
    <-0.767159273, -0.427801455, -0.073407636>, TUBE_THICKNESS
    <-0.687604636, -0.464353545, -0.135966000>, TUBE_THICKNESS
    <-0.591028182, -0.472237364, -0.182910364>, TUBE_THICKNESS
    <-0.487438273, -0.451913545, -0.205333091>, TUBE_THICKNESS
    <-0.388481364, -0.408552727, -0.197014182>, TUBE_THICKNESS
    <-0.304549727, -0.351728000, -0.156545818>, TUBE_THICKNESS
    <-0.241069909, -0.292087636, -0.088996000>, TUBE_THICKNESS
    <-0.193920727, -0.234495000, -0.005960273>, TUBE_THICKNESS
    <-0.147334636, -0.173318818, +0.075334909>, TUBE_THICKNESS
    <-0.086260909, -0.101366455, +0.134616909>, TUBE_THICKNESS
    <-0.011979182, -0.020864818, +0.155094273>, TUBE_THICKNESS
    <+0.061509000, +0.059406545, +0.130700636>, TUBE_THICKNESS
    <+0.120432636, +0.130565455, +0.068244636>, TUBE_THICKNESS
    <+0.162308909, +0.189540273, -0.016710909>, TUBE_THICKNESS
    <+0.199244909, +0.243907727, -0.106555364>, TUBE_THICKNESS
    <+0.248032273, +0.303880818, -0.185393273>, TUBE_THICKNESS
    <+0.316452273, +0.370048273, -0.239837455>, TUBE_THICKNESS
    <+0.402150182, +0.434014545, -0.261210727>, TUBE_THICKNESS
    <+0.497139545, +0.484952000, -0.247388545>, TUBE_THICKNESS
    <+0.591207545, +0.514055455, -0.202005545>, TUBE_THICKNESS
    <+0.674473545, +0.516256818, -0.132766455>, TUBE_THICKNESS
    <+0.738644636, +0.490301818, -0.049500273>, TUBE_THICKNESS
    <+0.777833182, +0.438263545, +0.036991000>, TUBE_THICKNESS
    <+0.788865455, +0.364903364, +0.115931273>, TUBE_THICKNESS
    <+0.771562000, +0.277157818, +0.177184273>, TUBE_THICKNESS
    <+0.729148273, +0.183448273, +0.212021455>, TUBE_THICKNESS
    <+0.668688818, +0.092912636, +0.214197182>, TUBE_THICKNESS
    <+0.600678273, +0.013511636, +0.181714909>, TUBE_THICKNESS
    <+0.537428727, -0.051324909, +0.118311818>, TUBE_THICKNESS
    <+0.488334273, -0.106690545, +0.033765818>, TUBE_THICKNESS
    <+0.453702000, -0.165998182, -0.056795364>, TUBE_THICKNESS
    <+0.422115545, -0.240305455, -0.135735636>, TUBE_THICKNESS
    <+0.379881000, -0.328230182, -0.189104818>, TUBE_THICKNESS
    <+0.322211636, -0.419226545, -0.210222091>, TUBE_THICKNESS
    <+0.251974182, -0.501648000, -0.199445909>, TUBE_THICKNESS
    <+0.174441727, -0.567278000, -0.162381818>, TUBE_THICKNESS
    <+0.093658455, -0.611944273, -0.106939364>, TUBE_THICKNESS
    <+0.011365000, -0.634213364, -0.041616545>, TUBE_THICKNESS
    <-0.072361818, -0.633855000, +0.025472545>, TUBE_THICKNESS
    <-0.157726909, -0.610869182, +0.086520727>, TUBE_THICKNESS
    <-0.243424727, -0.565588636, +0.133567455>, TUBE_THICKNESS
    <-0.325718273, -0.500086636, +0.158959455>, TUBE_THICKNESS
    <-0.398873636, -0.419431364, +0.156502182>, TUBE_THICKNESS
    <-0.457515727, -0.332453636, +0.123533545>, TUBE_THICKNESS
    <-0.501183727, -0.249904273, +0.063099727>, TUBE_THICKNESS
    <-0.538324636, -0.178489364, -0.015200636>, TUBE_THICKNESS
    <-0.580943091, -0.114651182, -0.096495909>, TUBE_THICKNESS
    <-0.633749182, -0.047024636, -0.165939818>, TUBE_THICKNESS
    <-0.691981727, +0.032837091, -0.212449000>, TUBE_THICKNESS
    <-0.746272364, +0.125343727, -0.229778000>, TUBE_THICKNESS
    <-0.787227091, +0.224735727, -0.216493273>, TUBE_THICKNESS
    <-0.807576545, +0.322694364, -0.175461727>, TUBE_THICKNESS
    <-0.803045909, +0.410414364, -0.112570636>, TUBE_THICKNESS
    <-0.772329818, +0.479909545, -0.035934000>, TUBE_THICKNESS
    <-0.716912909, +0.524831727, +0.045028364>, TUBE_THICKNESS
    <-0.640967455, +0.541008818, +0.119924364>, TUBE_THICKNESS
    <-0.551250909, +0.527340273, +0.178412909>, TUBE_THICKNESS
    <-0.456645455, +0.486462182, +0.211099909>, TUBE_THICKNESS
    <-0.367159364, +0.425209273, +0.211432727>, TUBE_THICKNESS
    <-0.291930545, +0.353999182, +0.177747364>, TUBE_THICKNESS
    <-0.236155273, +0.283633818, +0.114805091>, TUBE_THICKNESS
    <-0.196992273, +0.219411636, +0.033689091>, TUBE_THICKNESS
    <-0.160491364, +0.155803818, -0.050012182>, TUBE_THICKNESS
    <-0.110296273, +0.083237091, -0.117792364>, TUBE_THICKNESS
    <-0.043156000, +0.000994818, -0.151810364>, TUBE_THICKNESS
    <+0.029564273, -0.083295182, -0.141955636>, TUBE_THICKNESS
    <+0.093146455, -0.160597273, -0.091862818>, TUBE_THICKNESS
    <+0.145798909, -0.227302364, -0.018144273>, TUBE_THICKNESS
    <+0.203110000, -0.288120182, +0.056674909>, TUBE_THICKNESS
    <+0.279465091, -0.345584818, +0.113115636>, TUBE_THICKNESS
    <+0.375452727, -0.392196364, +0.139864273>, TUBE_THICKNESS
    <+0.481883909, -0.416743636, +0.134284182>, TUBE_THICKNESS
    <+0.585525091, -0.411624273, +0.100906091>, TUBE_THICKNESS
    <+0.673654455, -0.374816273, +0.048560727>, TUBE_THICKNESS
    <+0.736264091, -0.309467818, -0.011949909>, TUBE_THICKNESS
    <+0.767312909, -0.222387727, -0.069619273>, TUBE_THICKNESS
    <+0.764855727, -0.122790909, -0.114132000>, TUBE_THICKNESS
    <+0.731579909, -0.021095182, -0.136785091>, TUBE_THICKNESS
    <+0.675113636, +0.072998364, -0.131870545>, TUBE_THICKNESS
    <+0.607384636, +0.154088818, -0.098543636>, TUBE_THICKNESS
    <+0.540551636, +0.225734091, -0.043408273>, TUBE_THICKNESS
    <+0.479221909, +0.298582273, +0.018100636>, TUBE_THICKNESS
    <+0.416535455, +0.377522636, +0.066964818>, TUBE_THICKNESS
    <+0.344020000, +0.456616455, +0.090948909>, TUBE_THICKNESS
    <+0.260753909, +0.526111545, +0.087263000>, TUBE_THICKNESS
    <+0.170704545, +0.578252091, +0.059797727>, TUBE_THICKNESS
    <+0.077890909, +0.608916909, +0.015976091>, TUBE_THICKNESS
    <-0.015460364, +0.616596000, -0.035396455>, TUBE_THICKNESS
    <-0.108709273, +0.601161091, -0.085258909>, TUBE_THICKNESS
    <-0.200985364, +0.563508364, -0.124549909>, TUBE_THICKNESS
    <-0.289806000, +0.506094909, -0.144668909>, TUBE_THICKNESS
    <-0.370998818, +0.434296091, -0.138832818>, TUBE_THICKNESS
    <-0.440929091, +0.356738091, -0.104507636>, TUBE_THICKNESS
    <-0.501234909, +0.283147545, -0.046095909>, TUBE_THICKNESS
    <-0.560465727, +0.218157364, +0.023731909>, TUBE_THICKNESS
    <-0.626121364, +0.155957364, +0.088133273>, TUBE_THICKNESS
    <-0.696742727, +0.085745545, +0.133721000>, TUBE_THICKNESS
    <-0.763627000, +0.002377000, +0.153353727>, TUBE_THICKNESS
    <-0.816381818, -0.091742091, +0.145341909>, TUBE_THICKNESS
    <-0.846662727, -0.189982364, +0.112322182>, TUBE_THICKNESS
    <-0.849324727, -0.284050273, +0.059746545>, TUBE_THICKNESS
    <-0.822448182, -0.365780545, -0.005013182>, TUBE_THICKNESS
    <-0.767159273, -0.427801455, -0.073407636>, TUBE_THICKNESS
    <-0.687604636, -0.464353545, -0.135966000>, TUBE_THICKNESS
    <-0.591028182, -0.472237364, -0.182910364>, TUBE_THICKNESS
    <-0.487438273, -0.451913545, -0.205333091>, TUBE_THICKNESS
    <-0.388481364, -0.408552727, -0.197014182>, TUBE_THICKNESS

    /*  Blue-Green. 25% green mixed with 100% blue, in RGB format.            */
    pigment {
        color rgb <0.0, 0.25, 1.0>
    }

    /*  Data for the surface of the "thickened knot." It is fairly bright     *
     *  and reflective, but not too metallic looking.                         */
    finish {
        ambient 0.20
        diffuse 0.70
        brilliance 3.00
        phong 0.25
        phong_size 8.00
    }
}
