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

/*  Sqrt found here.                                                          */
import "math"

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
    return Vec3Rect(v.X + w.X, v.Y + w.Y, v.Z + w.Z)
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
    return Vec3Rect(v.X - w.X, v.Y - w.Y, v.Z - w.Z)
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
 *                = (vy*wz - wz*vy, vz*wx - vx*wz, vx*wy - vy*wx)             *
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
 *      v (*Vec6):                                                            *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in v.*
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
