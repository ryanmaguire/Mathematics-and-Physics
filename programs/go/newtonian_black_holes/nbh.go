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
 *  Purpose:                                                                  *
 *      Provides all tools needed to raytace a Newtonian black hole.          *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/03                                                        *
 ******************************************************************************/

package main

/*  Only standard library packages are required.                              */
import (
    "fmt"   /*  Fprintf found here. */
    "math"  /*  Sqrt given here.    */
    "os"    /*  File data type.     */
    "log"   /*  log.Fatal function. */
)

/******************************************************************************
 *                              Types of Structs                              *
 ******************************************************************************/

/*  Basic struct for vectors in R^3.                                          */
type Vec3 struct {

    /*  A vector is represented by its Cartesian coordinates.                 */
    X, Y, Z float64
}

/*  Struct for working in phase space. Points in R^6 are two points in R^3.   */
type Vec6 struct {

    /*  A point in phase-space is defined by its position and velocity.       */
    P, V Vec3
}

/*  Struct for working with colors in RGB format.                             */
type Color struct {

    /*  A color is completely defined by its red, green, and blue values.     */
    Red, Green, Blue uint8
}

/*  Struct for creating and writing to ppm files.                             */
type PPM struct {

    /*  The data in a PPM struct is the File pointer it represents.           */
    Fp *os.File
}

/******************************************************************************
 *                             Types of Functions                             *
 ******************************************************************************/

/*  Used to define the force of gravity.                                      */
type Acceleration func(*Vec3) Vec3

/*  Stopper functions determine when light "stops" in the raytracing.         */
type Stopper func(*Vec3) bool

/*  Colorers determine how the detector is colored behind the black hole.     */
type Colorer func(*Vec6) Color

/*  Raytracers trace out the path of light under a given acceleration.        */
type Raytracer func(*Vec6, Acceleration, Stopper)

/******************************************************************************
 *                         Vec3 Functions and Methods                         *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3Rect                                                              *
 *  Purpose:                                                                  *
 *      Creates a 3D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (float64):                                                          *
 *          The x-component of the vector.                                    *
 *      y (float64):                                                          *
 *          The y-component of the vector.                                    *
 *      z (float64):                                                          *
 *          The z-component of the vector.                                    *
 *  Outputs:                                                                  *
 *      v (Vec3):                                                             *
 *          The vector (x, y, z).                                             *
 *  Method:                                                                   *
 *      Use the constructor syntax for structs and return.                    *
 ******************************************************************************/
func Vec3Rect(x, y, z float64) Vec3 {
    return Vec3{x, y, z}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3Add                                                               *
 *  Purpose:                                                                  *
 *      Adds two 3D vectors in R^3.                                           *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a 3D vector.                                         *
 *      w (*Vec3):                                                            *
 *          Another pointer to a 3D vector.                                   *
 *  Outputs:                                                                  *
 *      sum (Vec3):                                                           *
 *          The sum of v and w.                                               *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is, given two       *
 *      vectors v = (vx, vy, vz) and w = (wx, wy, wz), the sum is:            *
 *                                                                            *
 *          sum = v + w                                                       *
 *              = (vx, vy, vz) + (wx, wy, wz)                                 *
 *              = (vx + wx, vy + wy, vz + wz)                                 *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
func Vec3Add(v, w *Vec3) Vec3 {
    return Vec3{v.X + w.X, v.Y + w.Y, v.Z + w.Z}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3AddTo                                                             *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^3 and stores the result in the first variable.  *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector. The sum is stored here.                    *
 *      w (*Vec3):                                                            *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform vector addition component-wise and store the result in v.     *
 ******************************************************************************/
func Vec3AddTo(v, w *Vec3) {
    v.X += w.X
    v.Y += w.Y
    v.Z += w.Z
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3Subtract                                                          *
 *  Purpose:                                                                  *
 *      Subtracts two vectors in R^3.                                         *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *      w (*Vec3):                                                            *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      diff (Vec3):                                                          *
 *          The vector difference of v and w, v - w.                          *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is, given two    *
 *      vectors v = (vx, vy, vz) and w = (wx, wy, wz), the difference is:     *
 *                                                                            *
 *          diff = v - w                                                      *
 *               = (vx, vy, vz) - (wx, wy, wz)                                *
 *               = (vx - wx, vy - wy, vz - wz)                                *
 *                                                                            *
 *      This is computed and the difference is returned.                      *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. Vec3Subtract(&v, &w)           *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
func Vec3Subtract(v, w *Vec3) Vec3 {
    return Vec3{v.X - w.X, v.Y - w.Y, v.Z - w.Z}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3SubtractFrom                                                      *
 *  Purpose:                                                                  *
 *      Subtracts two vectors and stores the result in the first variable.    *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector. The difference is stored here.             *
 *      w (*Vec3):                                                            *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform vector subtraction component-wise and store the result in v.  *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. Vec3SubtractFrom(&v, &w)       *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
func Vec3SubtractFrom(v, w *Vec3) {
    v.X -= w.X
    v.Y -= w.Y
    v.Z -= w.Z
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3Scale                                                             *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication.                                       *
 *  Arguments:                                                                *
 *      a (float64):                                                          *
 *          A real number.                                                    *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      prod (Vec3):                                                          *
 *          The scalar product a*v.                                           *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is, if v is   *
 *      the vector v = (x, y, z), then the product is:                        *
 *                                                                            *
 *          prod = a*v                                                        *
 *               = a*(x, y, z)                                                *
 *               = (a*x, a*y, a*z)                                            *
 *                                                                            *
 *      This is computed and the product is returned.                         *
 ******************************************************************************/
func Vec3Scale(a float64, v *Vec3) Vec3 {
    return Vec3{a*v.X, a*v.Y, a*v.Z}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3ScaleBy                                                           *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and stores the result in place.        *
 *  Arguments:                                                                *
 *      a (float64):                                                          *
 *          A real number.                                                    *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in v.*
 ******************************************************************************/
func Vec3ScaleBy(a float64, v *Vec3) {
    v.X *= a
    v.Y *= a
    v.Z *= a
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3ScaledAddTo                                                       *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and vector addition, v += a*w          *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *      a (float64):                                                          *
 *          A real number.                                                    *
 *      w (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform the operation component-wise.                                 *
 ******************************************************************************/
func Vec3ScaledAddTo(v *Vec3, a float64, w *Vec3) {
    v.X += a*w.X
    v.Y += a*w.Y
    v.Z += a*w.Z
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.Dot                                                              *
 *  Purpose:                                                                  *
 *      Performs the Euclidean dot product in R^3.                            *
 *  Arguments:                                                                *
 *      w (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      dot (float64):                                                        *
 *          The dot product v . w.                                            *
 *  Method:                                                                   *
 *      The Euclidean dot product sums the products of the components. Given  *
 *      two vectors v = (vx, vy, vz) and w = (wx, wy, wz), the dot product is:*
 *                                                                            *
 *          v.w = (vx, vy, vz) . (wx, wy, wz)                                 *
 *              = vx*wx + vy*wy + vz*wz                                       *
 *                                                                            *
 *      This is computed and the sum of products is returned.                 *
 ******************************************************************************/
func (v *Vec3) Dot(w *Vec3) float64 {
    return v.X*w.X + v.Y*w.Y + v.Z*w.Z
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.Cross                                                            *
 *  Purpose:                                                                  *
 *      Performs the Euclidean cross product in R^3.                          *
 *  Arguments:                                                                *
 *      w (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      cross (Vec3):                                                         *
 *          The cross product v x w.                                          *
 *  Method:                                                                   *
 *      The Euclidean cross is given by the right-hand rule. v x w is the     *
 *      the unique vector orthogonal to v and w with right-handed orientation *
 *      and magnitude given by ||v|| ||w|| sin(theta), theta being the angle  *
 *      between v and w. This can be computed explicitly as follows. Given    *
 *      v = (vx, vy, vz) and w = (wx, wy, wz), the cross product is:          *
 *                                                                            *
 *          cross = v x w                                                     *
 *                = (vx, vy, vz) x (wx, wy, wz)                               *
 *                = (vy*wz - vz*wy, vz*wx - vx*wz, vx*wy - vy*wx)             *
 *                                                                            *
 *      These components are computed and the cross product is returned.      *
 ******************************************************************************/
func (v *Vec3) Cross(w *Vec3) Vec3 {

    /*  Compute each component of the cross product and return.               */
    var cross Vec3
    cross.X = v.Y*w.Z - v.Z*w.Y
    cross.Y = v.Z*w.X - v.X*w.Z
    cross.Z = v.X*w.Y - v.Y*w.X
    return cross
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.CrossWith                                                        *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vector in-place.                    *
 *  Arguments:                                                                *
 *      w (*Vec3):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the cross product component-wise and store the resut in v.    *
 ******************************************************************************/
func (v *Vec3) CrossWith(w *Vec3) {

    /*  Naively computing the cross product and storing the result in v will  *
     *  cause overwrite problems and we will not get the correct result. To   *
     *  avoid this first save the x and y components of v before computing.   */
    var X float64 = v.X
    var Y float64 = v.Y

    /*  Perform the cross product component-wise.                             */
    v.X = Y*w.Z - v.Z*w.Y
    v.Y = v.Z*w.X - X*w.Z
    v.Z = X*w.Y - Y*w.X
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.Norm                                                             *
 *  Purpose:                                                                  *
 *      Computes the Euclidean, or L2, norm of a vector in R^3.               *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          A pointer to a vector in R^3.                                     *
 *  Outputs:                                                                  *
 *      norm_v (float64):                                                     *
 *          The norm, or magnitude, or length of the vector v.                *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          ||v|| = ||(x, y, z)||                                             *
 *                = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      Compute and return the norm.                                          *
 ******************************************************************************/
func (v *Vec3) Norm() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y + v.Z*v.Z)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.NormSq                                                           *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean, or L2, norm for vectors in R^3. *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      normsq_v (float64):                                                   *
 *          The square of the norm, or magnitude, or length of the vector v.  *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          ||v||^2 = ||(x, y, z)||^2                                         *
 *                  = x^2 + y^2 + z^2                                         *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
func (v *Vec3) NormSq() float64 {
    return v.X*v.X + v.Y*v.Y + v.Z*v.Z
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.Rho                                                              *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the azimuthal part of a vector.             *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      rho (float64):                                                        *
 *          The magnitude of the azimuthal part of v. This is the cylindrical *
 *          radius of v in cylindrical coordinates.                           *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          rho = ||(x, y)||                                                  *
 *              = sqrt(x^2 + y^2)                                             *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
func (v *Vec3) Rho() float64 {

    /*  Use Pythagoras and compute the square root of the sum of the squares. */
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec3.RhoSq                                                            *
 *  Purpose:                                                                  *
 *      Computes the square of the azimuthal part of a vector.                *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      rho (float64):                                                        *
 *          The square of the azimuthal part of v.                            *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          rho^2 = ||(x, y)||^2                                              *
 *                = x^2 + y^2                                                 *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
func (v *Vec3) RhoSq() float64 {

    /*  Use Pythagoras and compute.                                           */
    return v.X*v.X + v.Y*v.Y
}

/******************************************************************************
 *                         Vec6 Functions and Methods                         *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6FromReals                                                         *
 *  Purpose:                                                                  *
 *      Creates a 6D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (float64):                                                          *
 *          The x-component of the position vector.                           *
 *      y (float64):                                                          *
 *          The y-component of the position vector.                           *
 *      z (float64):                                                          *
 *          The z-component of the position vector.                           *
 *      vx (float64):                                                         *
 *          The x-component of the velocity vector.                           *
 *      vy (float64):                                                         *
 *          The y-component of the velocity vector.                           *
 *      vz (float64):                                                         *
 *          The z-component of the velocity vector.                           *
 *  Outputs:                                                                  *
 *      u (Vec6):                                                             *
 *          The vector (x, y, z, vx, vy, vz).                                 *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
func Vec6FromReals(x, y, z, vx, vy, vz float64) {
    var u Vec6
    u.P.X = x
    u.P.Y = y
    u.P.Z = z
    u.V.X = vx
    u.V.Y = vy
    u.V.Z = vz
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6Add                                                               *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^6.                                              *
 *  Arguments:                                                                *
 *      u0 (*Vec6):                                                           *
 *          A pointer to a vector.                                            *
 *      u1 (*Vec6):                                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      sum (Vec6):                                                           *
 *          The vector sum of u0 and u1.                                      *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is, given two       *
 *      vectors u0 = (p0, v0) and u1 = (p1, v1), the sum is:                  *
 *                                                                            *
 *          sum = u0 + u1                                                     *
 *              = (p0, v0) + (p1, v1)                                         *
 *              = (p0 + p1, v0 + v1)                                          *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
func Vec6Add(u0, u1 *Vec6) Vec6 {
    return Vec6{Vec3Add(&u0.P, &u1.P), Vec3Add(&u0.V, &u1.V)}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6AddTo                                                             *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^6 and stores the result in the first variable.  *
 *  Arguments:                                                                *
 *      u0 (*Vec6):                                                           *
 *          A pointer to a vector. The sum is stored here.                    *
 *      u1 (*Vec6):                                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform vector addition component-wise and store the result in u0.    *
 ******************************************************************************/
func Vec6AddTo(u0, u1 *Vec6) {
    Vec3AddTo(&u0.P, &u1.P)
    Vec3AddTo(&u0.V, &u1.V)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6Subtract                                                          *
 *  Purpose:                                                                  *
 *      Subtracts two vectors in R^6.                                         *
 *  Arguments:                                                                *
 *      u0 (*Vec6):                                                           *
 *          A pointer to a vector.                                            *
 *      u1 (*Vec6):                                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      diff (Vec6):                                                          *
 *          The vector difference of u0 and u1, u0 - u1.                      *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is, given two    *
 *      vectors u0 = (p0, v0) and u1 = (p1, v1), the difference is:           *
 *                                                                            *
 *          diff = u0 - u1                                                    *
 *               = (p0, v0) - (p1, v1)                                        *
 *               = (p0 - p1, v0 - v1)                                         *
 *                                                                            *
 *      This is computed and the difference is returned.                      *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. Vec6Subtract(&u0, &u1)         *
 *      computes the difference u0 - u1 (and not u1 - u0).                    *
 ******************************************************************************/
func Vec6Subtract(u0, u1 *Vec6) Vec6 {
    return Vec6{Vec3Subtract(&u0.P, &u1.P), Vec3Subtract(&u0.V, &u1.V)}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6SubtractFrom                                                      *
 *  Purpose:                                                                  *
 *      Subtracts two vectors and stores the result in the first variable.    *
 *  Arguments:                                                                *
 *      u0 (*Vec6):                                                           *
 *          A pointer to a vector. The difference is stored here.             *
 *      u1 (*Vec6):                                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform vector subtraction component-wise and store the result in u0. *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. Vec6SubtractFrom(&u0, &u1)     *
 *      computes the difference u0 - u1 (and not u1 - u0).                    *
 ******************************************************************************/
func Vec6SubtractFrom(u0, u1 *Vec6) {
    Vec3SubtractFrom(&u0.P, &u1.P)
    Vec3SubtractFrom(&u0.V, &u1.V)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6Scale                                                             *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication.                                       *
 *  Arguments:                                                                *
 *      a (float64):                                                          *
 *          A real number.                                                    *
 *      u (*Vec6):                                                            *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      prod (Vec6):                                                          *
 *          The scalar product a*u.                                           *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is, if u is   *
 *      the vector u = (p, v), then the product is:                           *
 *                                                                            *
 *          prod = a*u                                                        *
 *               = a*(p, v)                                                   *
 *               = (a*p, a*v)                                                 *
 *                                                                            *
 *      This is computed and the product is returned.                         *
 ******************************************************************************/
func Vec6Scale(a float64, u *Vec6) Vec6 {
    return Vec6{Vec3Scale(a, &u.P), Vec3Scale(a, &u.V)}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6ScaleBy                                                           *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and stores the result in place.        *
 *  Arguments:                                                                *
 *      a (float64):                                                          *
 *          A real number.                                                    *
 *      u (*Vec6):                                                            *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in u.*
 ******************************************************************************/
func Vec6ScaleBy(a float64, u *Vec6) {
    Vec3ScaleBy(a, &u.P)
    Vec3ScaleBy(a, &u.V)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6.Dot                                                              *
 *  Purpose:                                                                  *
 *      Performs the Euclidean dot product in R^6.                            *
 *  Arguments:                                                                *
 *      u1 (*Vec6):                                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      dot (float64):                                                        *
 *          The dot product u0 . u1.                                          *
 *  Method:                                                                   *
 *      The Euclidean dot product sums the products of the components. Given  *
 *      two vectors u0 = (p0, v0) and u1 = (p1, v1), the dot product is:      *
 *                                                                            *
 *          u0 . u1 = (p0, v0) . (p1, v1)                                     *
 *                  = (p0 . p1) + (v0 . v1)                                   *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
func (u0 *Vec6) Dot(u1 *Vec6) float64 {
    return u0.P.Dot(&u1.P) + u0.V.Dot(&u1.V)
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6.NormSq                                                           *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean, or L2, norm for vectors in R^6. *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      normsq_u (float64):                                                   *
 *          The square of the norm, or magnitude, or length of the vector u.  *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given u = (p, v) we have:     *
 *                                                                            *
 *          ||u||^2 = ||(p, v)||^2                                            *
 *                  = ||p||^2 + ||v||^2                                       *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
func (u *Vec6) NormSq() float64 {
    return u.P.NormSq() + u.V.NormSq()
}

/******************************************************************************
 *  Function:                                                                 *
 *      Vec6.Norm                                                             *
 *  Purpose:                                                                  *
 *      Computes the Euclidean, or L2, norm for vectors in R^6.               *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      norm_u (float64):                                                     *
 *          The norm, or magnitude, or length of the vector u.                *
 *  Method:                                                                   *
 *      Return the square root of the Vec6.NormSq function.                   *
 ******************************************************************************/
func (u *Vec6) Norm() float64 {
    return math.Sqrt(u.NormSq())
}

/******************************************************************************
 *                       Setup Parameters and Functions                       *
 ******************************************************************************/

/*  The z value for the source.                                               */
const Z_Src float64 = 10.0

/*  The start and end parameters for the "source". The source is the          *
 *  square [start, end] x [start, end] at height z_src.                       */
const Start float64 = -10.0
const End float64 = 10.0

/*  The height of the detector plane.                                         */
const Z_Detector float64 = -10.0

/*  The square of the height of the detector, used frequently.                */
const Z_Detector_Sq float64 = 100.0

/*  The radius of the black hole.                                             */
var Black_Hole_Radius float64 = 1.0

/*  The square of the black hole radius, also used frequently.                */
var Black_Hole_Radius_Sq float64 = 1.0

/*  Number of pixels in the x and y axes.                                     */
const X_Size uint32 = 1024
const Y_Size uint32 = 1024

/*  Factor used for converting from pixels to points in space. These have the *
 *  values (setup_end - setup_start) / (size - 1), where size is the number   *
 *  of pixels in the x and y axes, respectively. If you change X_Size or      *
 *  Y_Size, reset these numbers too.                                          */
const PX_Factor float64 = 0.019550342130987292
const PY_Factor float64 = 0.019550342130987292

/*  Threshold for highlighting features (usually the origin).                 */
const Highlight_Threshold float64 = 0.02

/*  For two black holes, the centers lie on the x axis.                       */
const BHX1 float64 = -3.0
const BHX2 float64 = +3.0

/******************************************************************************
 *  Function:                                                                 *
 *      ResetRadius                                                           *
 *  Purpose:                                                                  *
 *      Resets the radius of the black hole.                                  *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          The new radius.                                                   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
func ResetRadius(r float64) {
    Black_Hole_Radius = r
    Black_Hole_Radius_Sq = r*r
}
/*  End of ResetRadius.                                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      PixelToPoint                                                          *
 *  Purpose:                                                                  *
 *      Converts a pixel (x, y) on the PPM to a point in space.               *
 *  Arguments:                                                                *
 *      x (uint32):                                                           *
 *          The x coordinate of the pixel.                                    *
 *      y (uint32):                                                           *
 *          The y coordinate of the pixel.                                    *
 *  Outputs:                                                                  *
 *      p (Vec3):                                                             *
 *          The corresponding point in space to the given pixel.              *
 *  Method:                                                                   *
 *      The point on the detector lies on the z = Z_Src plane. Use this and   *
 *      convert the (x, y) components of the pixel to the (x, y) components   *
 *      on the detector.                                                      *
 ******************************************************************************/
func PixelToPoint(x, y uint32) Vec3 {
    var xpt float64 = Start + PX_Factor*float64(x)
    var ypt float64 = Start + PY_Factor*float64(y)
    return Vec3{xpt, ypt, Z_Src}
}
/*  End of PixelToPoint.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      Stop                                                                  *
 *  Purpose:                                                                  *
 *      Determines if a photon is still in motion for one black hole.         *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          The vector corresponding to the given photon.                     *
 *  Outputs:                                                                  *
 *      stop (bool):                                                          *
 *          Boolean for if the photon is still moving.                        *
 ******************************************************************************/
func Stop(v *Vec3) bool {

    /*  Case 1: The photon has reached the detector.                          */
    if (v.Z < Z_Detector) {
        return true

    /*  Case 2: The black hole swallowed the photon.                          */
    } else if (v.NormSq() < Black_Hole_Radius_Sq) {
        return true

    /*  Otherwise, the photon is still moving. Don't stop.                    */
    } else {
        return false
    }
}
/*  End of Stop.                                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      Stop2                                                                 *
 *  Purpose:                                                                  *
 *      Determines if a photon is still in motion for two black holes.        *
 *  Arguments:                                                                *
 *      v (*Vec3):                                                            *
 *          The vector corresponding to the given photon.                     *
 *  Outputs:                                                                  *
 *      stop (bool):                                                          *
 *          Boolean for if the photon is still moving.                        *
 ******************************************************************************/
func Stop2(p *Vec3) bool {

    /*  The black holes lie on the x axis. Compute the displacements to p.    */
    var r1 Vec3 = Vec3{p.X - BHX1, p.Y, p.Z}
    var r2 Vec3 = Vec3{p.X - BHX2, p.Y, p.Z}

    /*  Case 1: The photon has reached the detector.                          */
    if (p.Z < Z_Detector) {
        return true

    /*  Case 2: The first black hole swallowed the photon.                    */
    } else if (r1.NormSq() < Black_Hole_Radius_Sq) {
        return true

    /*  Case 3: The second black hole swallowed the photon.                   */
    } else if (r2.NormSq() < Black_Hole_Radius_Sq) {
        return true

    /*  Otherwise, the photon is still moving. Don't stop.                    */
    } else {
        return false
    }
}
/*  End of Stop2.                                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      Gravity                                                               *
 *  Purpose:                                                                  *
 *      Computes the acceleration given by the inverse square law from        *
 *      Newton's universal law of gravitation.                                *
 *  Arguments:                                                                *
 *      p (*Vec3):                                                            *
 *          The position vector of the particle.                              *
 *  Outputs:                                                                  *
 *      a (Vec3):                                                             *
 *          The acceleration of the particle.                                 *
 ******************************************************************************/
func Gravity(p *Vec3) Vec3 {

    /*  Given a vector p, Newton's universal law of gravitation says the      *
     *  acceleration is proportional to p/||p||^3 = p_hat/||p||^2, where      *
     *  p_hat is the unit vector for p. We can compute p/||p||^3 in terms     *
     *  of the norm of p and the square of the norm of p. We have:            */
    var factor float64 = 1.0 / (p.Norm() * p.NormSq())

    /*  The acceleration is the minus of p times this factor. The reason it   *
     *  is minus p is because gravity pulls inward, so the acceleration is    *
     *  towards the black hole.                                               */
    return Vec3{-p.X*factor, -p.Y*factor, -p.Z*factor}
}
/*  End of Gravity.                                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      Gravity2                                                              *
 *  Purpose:                                                                  *
 *      Computes the acceleration given by the inverse square law from        *
 *      Newton's universal law of gravitation for two gravitating objects.    *
 *      This is done using the principle of superposition.                    *
 *  Arguments:                                                                *
 *      p (*Vec3):                                                            *
 *          The position vector of the particle.                              *
 *  Outputs:                                                                  *
 *      a (Vec3):                                                             *
 *          The acceleration of the particle.                                 *
 ******************************************************************************/
func Gravity2(p *Vec3) Vec3 {

    /*  The force from one black hole is -R / ||R||^3, where R is the         *
     *  relative position vector from the point p to the center of the        *
     *  black hole. Compute this expression for both black holes.             */
    var f1 Vec3 = Vec3{BHX1 - p.X, -p.Y, -p.Z}
    var f2 Vec3 = Vec3{BHX2 - p.X, -p.Y, -p.Z}

    /*  We'll use the principle of superposition for the two black holes. */
    var factor1 float64 = 1.0 / (f1.Norm() * f1.NormSq())
    var factor2 float64 = 1.0 / (f2.Norm() * f2.NormSq())
    Vec3ScaleBy(factor1, &f1)
    Vec3ScaleBy(factor2, &f2)

    /*  The net force is computed by the principle of superposition.          *
     *  Add the two individual forces and return.                             */
    Vec3AddTo(&f1, &f2)
    return f1
}
/*  End of Gravity2.                                                          */

/******************************************************************************
 *                         PPM Functions and Methods                          *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Create                                                            *
 *  Purpose:                                                                  *
 *      Creates a PPM file with a given file name.                            *
 *  Arguments:                                                                *
 *      name (const char *):                                                  *
 *          The file name of the output PPM (ex. "black_hole.ppm").           *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) Create(name string) {

    /*  Variable for the error message if os.Create fails.                    */
    var err error

    /*  Open the file and give it write permissions.                          */
    ppm.Fp, err = os.Create(name)

    if (err != nil) {
        log.Fatal(err)
    }
}
/*  End of PPM.Create.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.InitFromVals                                                      *
 *  Purpose:                                                                  *
 *      Print the preamble to the PPM file. A PPM file wants Pn followed by   *
 *      three numbers. P6 means we're encoding an RGB image in binary format. *
 *      The first two numbers are the number of pixels in the x and y axes.   *
 *      The last number is the size of our color spectrum, which is 255.      *
 *  Arguments:                                                                *
 *      x (uint32):                                                           *
 *          The number of pixels in the x axis.                               *
 *      y (uint32):                                                           *
 *          The number of pixels in the y axis.                               *
 *      type (int):                                                           *
 *          The type of the PPM, options are 1 through 6.                     *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) InitFromVals(x, y uint32, ptype int) {

    /*  For integers between 1 and 5 we can pass the value to the preamble.   */
    if (0 < ptype && ptype < 6) {
        fmt.Fprintf(ppm.Fp, "P%d\n%d %d\n255\n", ptype, x, y)

    /*  The only other legal value is 6. All illegal values default to 6.     */
    } else {
        fmt.Fprintf(ppm.Fp, "P6\n%d %d\n255\n", x, y)
    }
}
/*  End of PPM.InitFromVals.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Init                                                              *
 *  Purpose:                                                                  *
 *      Initialize a PPM using the default values.                            *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Pass the default parameters to PPM.InitFromVals.                      *
 ******************************************************************************/
func (ppm *PPM) Init() {
    ppm.InitFromVals(X_Size, Y_Size, 6)
}
/*  End of PPM.Init.                                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Close                                                             *
 *  Purpose:                                                                  *
 *      Closes the file pointer in a PPM struct.                              *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) Close() {

    /*  Ensure the pointer is not nil before trying to close it.              */
    if (ppm.Fp != nil) {
        ppm.Fp.Close()
    }
}
/*  End of PPM.Close.                                                         */

/******************************************************************************
 *                        Color Functions and Methods                         *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToFile                                                     *
 *  Purpose:                                                                  *
 *      Writes a color to a File pointer.                                     *
 *  Arguments:                                                                *
 *      fp (*os.File):                                                        *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToFile(fp *os.File) {
    rgb := []byte{c.Red, c.Green, c.Blue}
    fp.Write(rgb)
}
/*  End of Color.WriteToFile.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToPPM                                                      *
 *  Purpose:                                                                  *
 *      Writes a color to a PPM.                                              *
 *  Arguments:                                                                *
 *      fp (*os.File):                                                        *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToPPM(ppm *PPM) {
    c.WriteToFile(ppm.Fp)
}
/*  End of Color.WriteToPPM.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorScale                                                            *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (*Color):                                                           *
 *          A pointer to a color.                                             *
 *      t (float64):                                                          *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (Color):                                                     *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
func ColorScale(c *Color, t float64) Color {
    var r uint8 = uint8(t * float64(c.Red))
    var g uint8 = uint8(t * float64(c.Green))
    var b uint8 = uint8(t * float64(c.Blue))
    return Color{r, g, b}
}
/*  End of ColorScale.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorScaleBy                                                          *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (*Color):                                                           *
 *          A pointer to a color.                                             *
 *      t (float64):                                                          *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func ColorScaleBy(c *Color, t float64) {
    c.Red = uint8(t * float64(c.Red))
    c.Green = uint8(t * float64(c.Green))
    c.Blue = uint8(t * float64(c.Blue))
}
/*  End of ColorScaleBy.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      Black                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color black in RGB format.                                *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      black (Color):                                                        *
 *          The color black in RGB.                                           *
 *  Method:                                                                   *
 *      Set each of the RGB components to zero and return.                    *
 ******************************************************************************/
func Black() Color {
    return Color{0x00, 0x00, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Red                                                                   *
 *  Purpose:                                                                  *
 *      Returns the color red in RGB format.                                  *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      red (Color):                                                          *
 *          The color red in RGB.                                             *
 *  Method:                                                                   *
 *      Set the green and blue components to zero, and the red component to t.*
 ******************************************************************************/
func Red(t float64) Color {

    /*  8-bit colors have a max intensity of 255. Scale this by t.            */
    var val uint8 = uint8(t * 255.0)
    return Color{val, 0x00, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Green                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color green in RGB format.                                *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      green (Color):                                                        *
 *          The color green in RGB.                                           *
 *  Method:                                                                   *
 *      Set the red and blue components to zero, and the green component to t.*
 ******************************************************************************/
func Green(t float64) Color {

    /*  8-bit colors have a max intensity of 255. Scale this by t.            */
    var val uint8 = uint8(t * 255.0)
    return Color{0x00, val, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Blue                                                                  *
 *  Purpose:                                                                  *
 *      Returns the color blue in RGB format.                                 *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      blue (Color):                                                         *
 *          The color blue in RGB.                                            *
 *  Method:                                                                   *
 *      Set the red and green components to zero, and the blue component to t.*
 ******************************************************************************/
func Blue(t float64) Color {

    /*  8-bit colors have a max intensity of 255. Scale this by t.            */
    var val uint8 = uint8(t * 255.0)
    return Color{0x00, 0x00, val}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Yellow                                                                *
 *  Purpose:                                                                  *
 *      Returns the color yellow in RGB format.                               *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      yellow (Color):                                                       *
 *          The color yellow in RGB.                                          *
 *  Method:                                                                   *
 *      Set the red and green components to t, and the blue component to zero.*
 ******************************************************************************/
func Yellow(t float64) Color {

    /*  8-bit colors have a max intensity of 255. Scale this by t.            */
    var val uint8 = uint8(t * 255.0)
    return Color{val, val, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      White                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color white in RGB format.                                *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      white (Color):                                                        *
 *          The color white in RGB.                                           *
 *  Method:                                                                   *
 *      Set the red, green, and blue components to t.                         *
 ******************************************************************************/
func White(t float64) Color {
    var val uint8 = uint8(t * 255.0)
    return Color{val, val, val}
}

/******************************************************************************
 *  Function:                                                                 *
 *      ColorAdd                                                              *
 *  Purpose:                                                                  *
 *      Adds two colors by averaging over their components.                   *
 *  Arguments:                                                                *
 *      c0 (*Color):                                                          *
 *          A pointer to the first color.                                     *
 *      c1 (*Color):                                                          *
 *          A pointer to the second color.                                    *
 *  Outputs:                                                                  *
 *      sum (Color):                                                          *
 *          The sum of the two colors.                                        *
 *  Method:                                                                   *
 *      Convert the components to float64 and take their average.             *
 ******************************************************************************/
func ColorAdd(c0, c1 *Color) Color {

    /*  Declare a variable for the output.                                    */
    var sum Color

    /*  Avoid overflow by converting to doubles and then taking the average.  */
    var r float64 = 0.5*(float64(c0.Red) + float64(c1.Red))
    var g float64 = 0.5*(float64(c0.Green) + float64(c1.Green))
    var b float64 = 0.5*(float64(c0.Blue) + float64(c1.Blue))

    /*  Convert back to unsigned char's and store these in the color.         */
    sum.Red = uint8(r)
    sum.Green = uint8(g)
    sum.Blue = uint8(b)
    return sum
}
/*  End of ColorAdd.                                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorAddTo                                                            *
 *  Purpose:                                                                  *
 *      Adds two colors by averaging over their components.                   *
 *  Arguments:                                                                *
 *      c0 (*Color):                                                          *
 *          A pointer to the first color.                                     *
 *      c1 (*Color):                                                          *
 *          A pointer to the second color.                                    *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Convert the components to float64 and take their average.             *
 ******************************************************************************/
func ColorAddTo(c0, c1 *Color) {

    /*  Avoid overflow by converting to doubles and then taking the average.  */
    var r float64 = 0.5*(float64(c0.Red) + float64(c1.Red))
    var g float64 = 0.5*(float64(c0.Green) + float64(c1.Green))
    var b float64 = 0.5*(float64(c0.Blue) + float64(c1.Blue))

    /*  Convert back to unsigned char's and store these in the color.         */
    c0.Red = uint8(r)
    c0.Green = uint8(g)
    c0.Blue = uint8(b)
}
/*  End of ColorAddTo.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      CheckerBoard                                                          *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector.                      *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func CheckerBoard(u *Vec6) Color {

    /*  Factor for darkening the checker board.                               */
    var cfact float64 = Z_Detector_Sq / u.P.NormSq()

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    } else if (uint32(math.Ceil(u.P.X) + math.Ceil(u.P.Y)) & 1 == 1) {
        return White(cfact)
    } else {
        return Red(cfact)
    }
}
/*  End of CheckerBoard.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      CheckerBoardHighlight                                                 *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern and highlights the origin.            *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func CheckerBoardHighlight(u *Vec6) Color {

    /*  Factor for darkening the checker board.                               */
    var cfact float64 = Z_Detector_Sq / u.P.NormSq()

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()

    /*  If the point is close to the origin, highlight it blue.               */
    } else if (u.P.RhoSq() < Highlight_Threshold) {
        return Blue(1.0)

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    } else if (uint32(math.Ceil(u.P.X) + math.Ceil(u.P.Y)) & 1 == 1) {
        return White(cfact)
    } else {
        return Red(cfact)
    }
}
/*  End of CheckerBoardHighlight.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      BrightCheckerBoard                                                    *
 *  Purpose:                                                                  *
 *      Creates a brighter checker-board pattern on the detector.             *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func BrightCheckerBoard(u *Vec6) Color {

    /*  Factor for darkening the checker board.                               */
    var cfact float64 = 0.5*(Z_Detector_Sq / u.P.NormSq() + 1.0)

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    } else if (uint32(math.Ceil(u.P.X) + math.Ceil(u.P.Y)) & 1 == 1) {
        return White(cfact)
    } else {
        return Red(cfact)
    }
}
/*  End of BrightCheckerBoard.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      CheckerBoardFour                                                      *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector with four colors.     *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func CheckerBoardFour(u *Vec6) Color {

    /*  Factor for darkening the checker board.                               */
    var cfact float64 = Z_Detector_Sq / u.P.NormSq()

    /*  Integers that determine the color.                                    */
    var nx uint32 = uint32(math.Ceil(u.P.X)) & 1
    var ny uint32 = uint32(math.Ceil(u.P.Y)) & 1
    var n uint32 = nx + (ny << 1)

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()
    }

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    switch (n) {
        case 0:
            return White(cfact)
        case 1:
            return Yellow(cfact)
        case 2:
            return Green(cfact)
        default:
            return Red(cfact)
    }
}
/*  End of CheckerBoardFour.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      CheckerBoardFourHighlight                                             *
 *  Purpose:                                                                  *
 *      Creates a four-colored checker-board and highlights the origin.       *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func CheckerBoardFourHighlight(u *Vec6) Color {

    /*  Factor for darkening the checker board.                               */
    var cfact float64 = Z_Detector_Sq / u.P.NormSq()

    /*  Integers that determine the color.                                    */
    var nx uint32 = uint32(math.Ceil(u.P.X)) & 1
    var ny uint32 = uint32(math.Ceil(u.P.Y)) & 1
    var n uint32 = nx + (ny << 1)

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()

    /*  If the point is close to the origin, highlight it blue.               */
    } else if (u.P.RhoSq() < Highlight_Threshold) {
        return Blue(1.0)
    }

    /*  Otherwise use a bit-wise trick to color the plane.                    */
    switch (n) {
        case 0:
            return White(cfact)
        case 1:
            return Yellow(cfact)
        case 2:
            return Green(cfact)
        default:
            return Red(cfact)
    }
}
/*  End of CheckerBoardFourHighlight.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      AngleGradientColor                                                    *
 *  Purpose:                                                                  *
 *      Creates a rainbow gradient of color based on the angle the velocity   *
 *      vector of the particle makes with the detector on impact.             *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func AngleGradientColor(u *Vec6) Color {

    /*  Declare unsigned char's for computing the output color.               */
    var red, green, blue uint8

    /*  We want the zenith angle of the velocity vector. This can be          *
     *  computed using the cylindrical coordinates of the vector.             */
    var angle float64 = math.Atan2(math.Abs(u.V.Z), u.V.RhoSq())

    /*  Scale the angle so that it falls between 0 and 255.                   */
    var scaled float64 = 255.0 * angle / (0.5*math.Pi)

    /*  Use an RGB rainbow gradient to color the current pixel. We'll set     *
     *  blue to correspond to the least value and red for the greatest,       *
     *  with a continuous gradient in between. First blue to cyan.            */
    if (scaled < 64.0) {
        red = 0x00
        green = uint8(4.0*scaled)
        blue = 0xFF

    /*  Next, cyan to green.                                                  */
    } else if (scaled < 128.0) {
        red = 0x00
        green = 0xFF
        blue = uint8(255.0 - 4.0*(scaled - 64.0))

    /*  Green to yellow.                                                      */
    } else if (scaled < 192.0) {
        red = uint8(4.0*(scaled - 128.0))
        green = 0xFF
        blue = 0x00

    /*  Yellow to red.                                                        */
    } else if (scaled < 255.0) {
        red = 0xFF
        green = uint8(255.0 - 4.0*(scaled - 192.0))
        blue = 0x00

    /*  And lastly, red.                                                      */
    } else {
        red = 0xFF
        green = 0x00
        blue = 0x00
    }

    return Color{red, green, blue}
}
/*  End of AngleGradientColor.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorGradientCheckerBoard                                             *
 *  Purpose:                                                                  *
 *      Creates a checker-board pattern on the detector and adds the rainbow  *
 *      gradient defined in AngleGradientColor.                               *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          The position and velocity of the particle as it hit the detector. *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given on the detector.                                  *
 ******************************************************************************/
func ColorGradientCheckerBoard(u *Vec6) Color {

    /*  Declare necessary variables.                                          */
    var rainbow, checker_board Color

    /*  If the photon didn't make it, color the pixel black.                  */
    if (u.P.Z > Z_Detector) {
        return Black()
    }

    /*  Take the average of the checkerboard and the raindbow gradient.       */
    rainbow = AngleGradientColor(u)
    checker_board = BrightCheckerBoard(u)
    return ColorAdd(&checker_board, &rainbow)
}
/*  End of ColorGradientCheckerBoard.                                         */

/******************************************************************************
 *                  Euler's Method Functions and Constants.                   *
 ******************************************************************************/

/*  Time step used in Euler's method. The user may change this.               */
var Euler_Time_Increment float64 = 0.01

/*  The max number of iterations in Euler's method.                           */
var Euler_Max_Iters uint32 = 65535

/*  Function for reseting the max number of iterations allowed.               */
func EulerResetMaxIters(n uint32) {
    Euler_Max_Iters = n
}

/******************************************************************************
 *  Function:                                                                 *
 *      EulerPath                                                             *
 *  Purpose:                                                                  *
 *      Given a vector-valued acceleration a = acc(r), a starting position p, *
 *      an initial velocity v, and a stopping condition stop, perform Euler's *
 *      method method to numerically solve the system of motion. The initial  *
 *      conditions (p, v) are given as the 6D vector u.                       *
 *  Arguments:                                                                *
 *      u (*Vec6):                                                            *
 *          A pointer to a 6D vector that represents the initial position and *
 *          velocity vectors of the particle.                                 *
 *      acc (acceleration):                                                   *
 *          A function that describes the equation of motion for the particle.*
 *      stop (stopper):                                                       *
 *          A stopper function that determines when to stop Euler's method.   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Apply Euler's method. Given initial conditions (p0, v0) and time      *
 *      increment dt, we iteratively compute:                                 *
 *                                                                            *
 *          v_{n+1} = dt*acc(p_{n+1}) + v_{n}                                 *
 *          p_{n+1} = dt*v_{n+1} + p_{n}                                      *
 *                                                                            *
 *      Do this until the stopper function tells you to stop, or until you've *
 *      done to many iterations.                                              *
 ******************************************************************************/
func EulerPath(u *Vec6, acc Acceleration, stop Stopper) {

    /*  Use of this function with nbh makes a very naive assumption. Newton's *
     *  Second Law states that F = ma, where a is the acceleration. For       *
     *  gravity we obtain the vector-valued differential equation:            *
     *      -GMm p / ||p||^3 = m d^2/dt^2 p                                   *
     *  Where G is the universal gravitational constant, and M is the mass of *
     *  the black hole (m being the mass of the object under consideration).  *
     *  We can take G*M to be 1 for simplicity, since we never specified the  *
     *  units we're in. Now, if m is any non-zero value we can cancel to get: *
     *      p / ||p||^3 = d^2/dt^2 p                                          *
     *  Solving this vector-valued differential equation results in the       *
     *  trajectory of the object. The only problem is it is generally         *
     *  believed that photons, which are particles of light, have zero mass.  *
     *  So let's pretend they have a mass that is so stupidly small it would  *
     *  be impossible to measure, but not zero. Given this we could apply     *
     *  Newtonian mechanics to get a rough sketch of a black hole.            */
    var a Vec3

    /*  In the main use of this function the black hole is of radius r at     *
     *  the origin and our detector is the plane z = z0. Our source of light  *
     *  is some plane z = z1. So the light is coming down and heading towards *
     *  our detector. We'll increment time using a small value dt, and we'll  *
     *  keep incrementing until the light either hits the detector or is      *
     *  absorbed by the black hole. dt is given by the time_increment value,  *
     *  and the stopping condition (hitting the detector, or being absorbed   *
     *  by a black hole) is determined by the "stop" function.                */
    var n uint32

    /*  It is possible that a photon was captured into orbit, but not         *
     *  absorbed into the black hole. To avoid an infinite loop abort the     *
     *  computation once n gets too large.                                    */
    for n = 0; n < Euler_Max_Iters; n += 1 {

        /*  We numerically solve d^2/dt^2 p = F(p) in two steps. First we     *
         *  compute the velocity dp/dt, meaning we need to solve dv/dt = F(p).*
         *  We solve numerically with Euler's method. Then we use this v to   *
         *  compute p via dp/dt = v, again solving numerically with Euler's   *
         *  method. So long as dt is small, the error should be small as well.*/
        a = acc(&u.P)
        Vec3ScaledAddTo(&u.P, Euler_Time_Increment, &u.V)
        Vec3ScaledAddTo(&u.V, Euler_Time_Increment, &a)

        /*  Check if we can stop.                                             */
        if (stop(&u.P)) {
            break
        }
    }
}
/*  End of EulerPath.                                                         */

/******************************************************************************
 *                            Raytracing Routines                             *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Run                                                                   *
 *  Purpose:                                                                  *
 *      Runs the raytracing routines without parallelizing the computation.   *
 *  Arguments:                                                                *
 *      acc (Acceleration):                                                   *
 *          Function describing the equation of motion.                       *
 *      stop (Stopper):                                                       *
 *          Stopper function for determining when the photon stops moving.    *
 *      color (Colorer):                                                      *
 *          Color function for coloring the detector.                         *
 *      path (Raytracer):                                                     *
 *          The method of numerical raytracing. Options are Euler's method    *
 *          and fourth order Runge-Kutta.                                     *
 *      name (const char *):                                                  *
 *          The name of the output ppm file.                                  *
 ******************************************************************************/
func Run(acc Acceleration, stop Stopper,
         color Colorer, path Raytracer, name string) {

    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    var v_start Vec3 = Vec3{0.0, 0.0, -1.0}

    /*  The initial conditions of a particle of light.                        */
    var u Vec6

    /*  Variables for looping over the x and y coordinates of the detector.   */
    var x, y uint32

    /*  Factor used for printing a progress report.                           */
    var prog_factor float64 = 100.0 / float64(Y_Size)

    /*  Variable for the color.                                               */
    var c Color

    /*  Open the file and give it write permissions.                          */
    var ppm PPM

    ppm.Create(name)

    /*  If the constructor fails the FILE pointer will be NULL. Check this.   */
    if (ppm.Fp == nil) {
        return
    }

    /*  Otherwise initialize the ppm with default values in "setup".          */
    ppm.Init()

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential. If we wanted to *
     *  introduce parallel processing, we would need to store the colors in   *
     *  an array, and then create the PPM from that array. For the simplicity *
     *  of the code, this is not done.                                        */
    for y = 0; y < Y_Size; y += 1 {
        for x = 0; x < X_Size; x += 1 {

            /*  We're incrementing p across our detector.                     */
            u.P = PixelToPoint(x, y)

            /*  Set the starting velocity.                                    */
            u.V = v_start

            /*  Raytrace where the photon that hit p came from.               */
            path(&u, acc, stop)

            /*  Get the color for the current pixel.                          */
            c = color(&u)

            /*  Write the color to the PPM file.                              */
            c.WriteToPPM(&ppm)
        }
        /*  End of x for-loop.                                                */

        /*  Print a status update.                                            */
        if ((y % 20) == 0) {
            fmt.Printf("Progress: %.4f%%  \r", prog_factor*float64(y))
        }
    }
    /*  End of y for-loop.                                                    */

    /*  Print a final progress report.                                        */
    fmt.Printf("Progress: 100.0000%%\nDone\n")

    /*  Close the file and return.                                            */
    ppm.Close()
}
/*  End of Run.                                                               */
