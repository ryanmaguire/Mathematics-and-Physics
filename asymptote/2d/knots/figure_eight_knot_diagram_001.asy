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
 ******************************************************************************/

/*  Needed for making the output a PDF file.                                  */
import settings;

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  These points are the projection onto the xy plane of the control points   *
 *  in R^3 given by Jim Belk for his 3D drawing of the figure-eight knot,     *
 *  originally written in POV-Ray. We'll be creating a knot diagram, so we    *
 *  must project to the xy plane.                                             */
path g = (-0.743926, -0.323044) ..
         (-0.712114, -0.43569) ..
         (-0.657593, -0.539064) ..
         (-0.580001, -0.628497) ..
         (-0.480129, -0.698632) ..
         (-0.361141, -0.743997) ..
         (-0.229443, -0.759909) ..
         (-0.0949831, -0.743633) ..
         (0.0290111, -0.695571) ..
         (0.127664, -0.620327) ..
         (0.187943, -0.526887) ..
         (0.202792, -0.42621) ..
         (0.17111, -0.32591) ..
         (0.0972916, -0.227153) ..
         (-0.00303469, -0.130199) ..
         (-0.105695, -0.0395859) ..
         (-0.192521, 0.0426878) ..
         (-0.258908, 0.125519) ..
         (-0.306283, 0.222655) ..
         (-0.332389, 0.339841) ..
         (-0.332078, 0.471357) ..
         (-0.302211, 0.604663) ..
         (-0.243592, 0.725428) ..
         (-0.160735, 0.820618) ..
         (-0.0609402, 0.880171) ..
         (0.0467134, 0.897821) ..
         (0.152292, 0.871534) ..
         (0.245965, 0.803746) ..
         (0.31894, 0.701332) ..
         (0.364616, 0.575224) ..
         (0.379764, 0.439493) ..
         (0.365485, 0.30926) ..
         (0.327266, 0.196744) ..
         (0.27163, 0.10534) ..
         (0.200056, 0.0254783) ..
         (0.110533, -0.0587019) ..
         (0.00963576, -0.154385) ..
         (-0.0823127, -0.256527) ..
         (-0.141554, -0.357878) ..
         (-0.154315, -0.455221) ..
         (-0.118171, -0.545017) ..
         (-0.0372333, -0.619017) ..
         (0.0777866, -0.667792) ..
         (0.211105, -0.685624) ..
         (0.346655, -0.671631) ..
         (0.471388, -0.628678) ..
         (0.576552, -0.561812) ..
         (0.657697, -0.476737) ..
         (0.713605, -0.378719) ..
         (0.744743, -0.271947) ..
         (0.751811, -0.159612) ..
         (0.73477, -0.0444363) ..
         (0.692907, 0.0705058) ..
         (0.625781, 0.18087) ..
         (0.534857, 0.280625) ..
         (0.425349, 0.362575) ..
         (0.306944, 0.420442) ..
         (0.19151, 0.452695) ..
         (0.0866572, 0.465806) ..
         (-0.0108419, 0.470164) ..
         (-0.112128, 0.467972) ..
         (-0.224385, 0.450555) ..
         (-0.344022, 0.409211) ..
         (-0.460559, 0.342175) ..
         (-0.563557, 0.253287) ..
         (-0.646168, 0.148681) ..
         (-0.705409, 0.0343619) ..
         (-0.740931, -0.084795) ..
         (-0.753536, -0.204989) ..
         (-0.743926, -0.323044) ..
         (-0.712114, -0.43569) ..
         (-0.657593, -0.539064);

    /*  Create subpaths to give the illusion of one strand crossing over      *
     *  another. Drawing g altogether means we can't tell which crossings     *
     *  are over or under.                                                    */
    path g1 = subpath(g, 9, 19);
    path g2 = subpath(g, 20, 35);
    path g3 = subpath(g, 37, 55);
    path g4 = subpath(g, 56, 75);
    path g5 = subpath(g, 0, 8);

    draw(g1);
    draw(g2);
    draw(g3);
    draw(g4);
    draw(g5);