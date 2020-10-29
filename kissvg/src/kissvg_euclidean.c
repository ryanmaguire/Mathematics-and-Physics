/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************
 *                            kissvg_euclidean                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide basic tools for computational Euclidean geometry.             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/src/kissvg_math.h>
#include <kissvg/src/kissvg_vector.h>
#include <kissvg/src/kissvg_matrix.h>
#include <kissvg/src/kissvg_circle.h>
#include <kissvg/src/kissvg_line.h>
#include <kissvg/src/kissvg_euclidean.h>

/*  NOTE:                                                                     *
 *      Detailed descriptions of the functions are provided in kissvg.h.      */

/*  Error checking routine for kissvg_Circle's.                               */
static void __check_circle_error(kissvg_Circle *C, const char *FuncName)
{
    /*  If the input circle is NULL, it was not set via kissvg_CreateCircle   *
     *  or kissvg_DestroyCircle was called prematurely. In either case, print *
     *  an error message and abort the computation.                           */
    if (C == NULL)
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input circle is NULL. Aborting.", FuncName);
        exit(0);
    }

    /*  If the input circle has an error set, abort the computation.          */
    if (kissvg_Has_Error(C))
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input circle has error_encoutered variable set to true.\n"
               "Printing Error Message:\n\n", FuncName);

        /*  If the error message is NULL, then it wasn't set. Print this.     */
        if (kissvg_Error_Message(C) == NULL)
            puts("Input circle did not have an error message set.\n\n");

        /*  Otherwise, simply print the message.                              */
        else
            puts(kissvg_Error_Message(C));

        /*  Abort the computation.                                            */
        exit(0);
    }

    /*  If no error occured, return to caller.                                */
    return;
}

/*  Error checking routine for kissvg_Line2D's.                               */
static void __check_line_error(kissvg_Line2D *L, const char *FuncName)
{
    /*  If the input line is NULL, it was not set via kissvg_CreateLine...    *
     *  or kissvg_DestroyLine2D was called prematurely. In either case, print *
     *  an error message and abort the computation.                           */
    if (L == NULL)
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input line is NULL. Aborting.", FuncName);
        exit(0);
    }

    /*  If the input line has an error set, abort the computation.            */
    if (kissvg_Has_Error(L))
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input line has error_encoutered variable set to true.\n"
               "Printing Error Message:\n\n", FuncName);

        /*  If the error message is NULL, then it wasn't set. Print this.     */
        if (kissvg_Error_Message(L) == NULL)
            puts("Input line did not have an error message set.\n\n");

        /*  Otherwise, simply print the message.                              */
        else
            puts(kissvg_Error_Message(L));

        /*  Abort the computation.                                            */
        exit(0);
    }

    /*  If no error occured, return to caller.                                */
    return;
}

/*  Function for computing the length of a two dimensional vector.            */
double kissvg_Euclidean_Norm_2D(kissvg_TwoVector P)
{
    /*  Declare the necessary variables for the computation.                  */
    double x_comp, y_comp;
    double norm;

    /*  Extract the x and y values of the vector P.                           */
    x_comp = kissvg_TwoVector_X_Component(P);
    y_comp = kissvg_TwoVector_Y_Component(P);

    /*  If either x or y is infinity, set the length to infinity.             */
    if (kissvg_Is_Inf(x_comp) || kissvg_Is_Inf(y_comp))
        return kissvg_Infinity;

    /*  Use kissvg_NewTwoVector to generate the output and return. sqrt is a  *
     *  C standard library function found in math.h, and math.h is included   *
     *  in the header kissvg_math.h. kissvg_SqrtDouble is an alias for this.  */
    norm = kissvg_Sqrt_Double(x_comp*x_comp + y_comp*y_comp);
    return norm;
}

/*  Function for computing the standard Euclidean dot product of 2 two        *
 *  dimensional vectors P and Q.                                              */
double kissvg_Euclidean_Dot_Product_2D(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double x0, y0;
    double x1, y1;
    double dot_product;

    /*  Extract the x and y components of the vector P.                       */
    x0 = kissvg_TwoVector_X_Component(P);
    y0 = kissvg_TwoVector_Y_Component(P);

    /*  Extract the x and y components of the vector Q.                       */
    x1 = kissvg_TwoVector_X_Component(Q);
    y1 = kissvg_TwoVector_Y_Component(Q);

    /*  Compute the dot product and return.                                   */
    dot_product = x0*x1 + y0*y1;
    return dot_product;
}

/*  Given a vector V, returns an orthogonal vector U with respect to the      *
 *  standard Euclidean dot product. That is, a vector U with <V|U> = 0        *
 *  (using bra-ket notation).                                                 */
kissvg_TwoVector kissvg_Euclidean_Orthogonal_Vector_2D(kissvg_TwoVector V)
{
    /*  Declare necessary variables.                                          */
    kissvg_TwoVector orth;
    double x_comp, y_comp;

    /*  Extract the x and y values from the input vector.                     */
    x_comp = kissvg_TwoVector_X_Component(V);
    y_comp = kissvg_TwoVector_Y_Component(V);

    /*  Simply return (-y, x) since this will be orthogonal. That is, the dot *
     *  product is <V|U> = <(x,y)|(-y,x)> = -xy + yx = 0.                     */
    orth = kissvg_New_TwoVector(-y_comp, x_comp);
    return orth;
}

/*  Function for computing the angle between the lines OP and OQ given three  *
 *  kissvg_TwoVector's O, P, and Q.                                           */
double kissvg_Euclidean_Rel_Angle_2D(kissvg_TwoVector O,
                                     kissvg_TwoVector P,
                                     kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double dot_prod;
    double abs_prod;
    double rel_angle;

    /*  We need to compute the vector from O to P and O to Q so declare these.*/
    kissvg_TwoVector OP;
    kissvg_TwoVector OQ;

    /*  Compute the vector pointing from O to P, which is simply P-O. Do the  *
     *  same thing for O and Q.                                               */
    OP = kissvg_TwoVector_Subtract(P, O);
    OQ = kissvg_TwoVector_Subtract(Q, O);

    /*  The angle formula is arccos(a dot b / norm(a)norm(b)). First we'll    *
     *  compute the dot product, then check that norm(a)norm(b) is non-zero.  */
    dot_prod = kissvg_Euclidean_Dot_Product_2D(OP, OQ);

    /*  abs_prod represents the quantity ||OP|| * ||OQ||.                     */
    abs_prod = kissvg_Euclidean_Norm_2D(OP)*kissvg_Euclidean_Norm_2D(OQ);

    /*  If norm(OP)norm(OQ) is zero, then one of these vectors is the zero    *
     *  vector, meaning the angle is undefined. We then return Not-A-Number.  */
    if (abs_prod == 0.0)
        rel_angle = kissvg_NaN;

    /*  If norm(OP)norm(OQ) is non-zero, we may use the angle formula. Note,  *
     *  acos is a C standard library function found in math.h. This header    *
     *  file is included with kissvg_math.h. kissvg_AcosDouble is an alias.   */
    else
        rel_angle = kissvg_Acos_Double(dot_prod/abs_prod);

    return rel_angle;
}

/*  Function for determining if three planar vectors are collinear.           */
kissvg_Bool kissvg_Euclidean_Is_Collinear(kissvg_TwoVector A,
                                          kissvg_TwoVector B,
                                          kissvg_TwoVector C)
{
    /*  The method simply checks the determinant of the matrix formed by      *
     *  the column vectors AB and AC. This is equivalent to seeing if the     *
     *  cross product of AB and AC is zero using the standard embedding of    *
     *  the plane into three dimensional space.                               */
    kissvg_TwoVector AB;
    kissvg_TwoVector AC;
    double ABx, ABy;
    double ACx, ACy;
    double det;

    /*  Compute the vectors pointing from A to B and A to C.                  */
    AB = kissvg_TwoVector_Subtract(B, A);
    AC = kissvg_TwoVector_Subtract(C, A);

    /*  Extract the x and y components of AB.                                 */
    ABx = kissvg_TwoVector_X_Component(AB);
    ABy = kissvg_TwoVector_Y_Component(AB);

    /*  Extract the x and y components of AC.                                 */
    ACx = kissvg_TwoVector_X_Component(AC);
    ACy = kissvg_TwoVector_Y_Component(AC);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    det = ABx*ACy - ABy*ACx;

    if (det == 0.0)
        return kissvg_True;
    else
        return kissvg_False;
}

/*  Function for computing the midpoint of 2 two dimensional vectors.         */
kissvg_TwoVector kissvg_Euclidean_Midpoint_2D(kissvg_TwoVector P,
                                              kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double x0, y0;
    double x1, y1;
    double xmid, ymid;
    kissvg_TwoVector midpoint;

    /*  Extract the x and y components of the vector P.                       */
    x0 = kissvg_TwoVector_X_Component(P);
    y0 = kissvg_TwoVector_Y_Component(P);

    /*  Extract the x and y components of the vector Q.                       */
    x1 = kissvg_TwoVector_X_Component(Q);
    y1 = kissvg_TwoVector_Y_Component(Q);

    /*  Compute the midpoint of P and Q, which is simply 0.5*(P+Q).           */
    xmid = 0.5*(x0 + x1);
    ymid = 0.5*(y0 + y1);

    /*  Use kissvg_NewTwoVector to create the new output and return.          */
    midpoint = kissvg_New_TwoVector(xmid, ymid);
    return midpoint;
}

/*  Function for determining the center of three points in the plane.         */
kissvg_Circle *kissvg_Euclidean_Find_Center_2D(kissvg_TwoVector A,
                                               kissvg_TwoVector B,
                                               kissvg_TwoVector C)
{
    /*  Declare the necessary variables.                                      */
    kissvg_TwoVector U;
    kissvg_TwoVector V;
    kissvg_TwoVector MidPointAB, MidPointAC;
    kissvg_TwoVector center;
    kissvg_Line2D *L0, *L1;
    kissvg_Circle *circle;
    double radius;
    char *err_mes;

    /*  If A, B, and C are collinear, their center is "at infinity."          */
    if (kissvg_Euclidean_Is_Collinear(A, B, C))
    {
        center = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;

        circle = kissvg_Create_Circle(center, radius, NULL);

        V = kissvg_TwoVector_Subtract(A, B);
        U = kissvg_TwoVector_Subtract(A, C);

        /*  In this case, the circle degenerates to a line. We need to        *
         *  specify a point on the line and a vector tangent to it. We can    *
         *  take any point A, B, C as our point, and either AB, AC, or BC as  *
         *  our tangent. If A and B are different points, take AB to be the   *
         *  tangent vector of the line.                                       */
        if (!(kissvg_Euclidean_Norm_2D(V) == 0.0))
            kissvg_Circle_Set_Line(circle, A, V);

        /*  If A and B are the same point, try to set the tangent as AC.      */
        else if (!(kissvg_Euclidean_Norm_2D(U) == 0.0))
            kissvg_Circle_Set_Line(circle, A, U);

        /*  If both AB and AC are the zero vector, then all three points are  *
         *  the same and it is impossible to specify a unique line. Set the   *
         *  velocity to A and store an error message in the circle. If the    *
         *  circle is used for drawing or certain computations, the error     *
         *  message will print and, pending situation, exit(0) will be called.*/
        else
        {
            err_mes = "Error Encountered: KissVG\n"
                      "\tFunction: kissvg_FindCenter2D\n\n"
                      "All three points are the same.\n";

            kissvg_Circle_Set_Error_Message(circle, err_mes);
            kissvg_Circle_Set_Line(circle, A, A);
        }
    }

    /*  Otherwise, following Euclid, we compute the bisectors of the lines AB *
     *  and AC, and then find where these intersect.                          */
    else
    {
        /*  Get the vectors AB and AC.                                        */
        U = kissvg_TwoVector_Subtract(A, B);
        V = kissvg_TwoVector_Subtract(A, C);

        /*  Find the midpoints of AB and AC.                                  */
        MidPointAB = kissvg_Euclidean_Midpoint_2D(A, B);
        MidPointAC = kissvg_Euclidean_Midpoint_2D(A, C);

        /*  We need the bisecting lines of AB and AC, which we'll compute via *
         *  the midpoints and vectors orthogonal to AB and AC.                */
        U = kissvg_Euclidean_Orthogonal_Vector_2D(U);
        V = kissvg_Euclidean_Orthogonal_Vector_2D(V);

        /*  Create bisecting lines from midpoints and orthgonal vectors.      *
         *  Since we don't need these lines to have the canvas variable set   *
         *  (we're using the lines for computations, not for drawing), simply *
         *  set the canvas variable to NULL.                                  */
        L0 = kissvg_Create_Line2D_From_Point_And_Tangent(MidPointAB, U, NULL);
        L1 = kissvg_Create_Line2D_From_Point_And_Tangent(MidPointAC, V, NULL);

        /*  The center of the circle is the intersection of the two lines, so *
         *  we simply compute this point and save it.                         */
        center = kissvg_Line2D_Intersection(L0, L1);

        /*  Lines are created via malloc and need to be free'd when done      *
         *  using the kissvg_DestroyLine2D function.                          */
        kissvg_Destroy_Line_2D(L0);
        kissvg_Destroy_Line_2D(L1);

        /*  We need to compute the radius of the circle, so get the vector    *
         *  starting at center and ending at A.                               */
        U = kissvg_TwoVector_Subtract(center, A);

        /*  The radius is the Euclidean norm of this vector, so compute this. */
        radius = kissvg_Euclidean_Norm_2D(U);
        circle = kissvg_Create_Circle(center, radius, NULL);
    }

    /* Return the output. The user can check if the circle degenerated to a   *
     *  line via the macro kissvg_CircleIsLine.                               */
    return circle;
}

/*  Function for finding the closest point on a line L to a given point P.    */
kissvg_TwoVector
kissvg_Closest_Point_On_Line2D(kissvg_Line2D *L, kissvg_TwoVector P)
{
    /*  Declare all necessary variables.                                      */
    kissvg_TwoVector orth;
    kissvg_TwoVector A, B, V, out;
    kissvg_Line2D *orthline;

    /*  Create a variable for the name of the function for error checking.    */
    const char *FuncName = "kissvg_ClosestPointOnLine";

    /*  Check the input line for errors. This will abort if there are.        */
    __check_line_error(L, FuncName);

    /*  Extract a point on the line and it's tangent vector.                  */
    A = kissvg_Line2D_Point(L);
    V = kissvg_Line2D_Tangent(L);
    B = kissvg_TwoVector_Add(A, V);

    /*  If A, B, and P are collinear, then P lies on the line so return P.    */
    if (kissvg_Euclidean_Is_Collinear(A, B, P))
        return P;

    /*  Otherwise, get a vector orth which is orthogonal to the line and      *
     *  create a new line containing the input point P and with tangent set   *
     *  to orth.                                                              */
    orth = kissvg_Euclidean_Orthogonal_Vector_2D(V);
    orthline = kissvg_Create_Line2D_From_Point_And_Tangent(P, orth, NULL);

    /*  The output is the intersection of the input line with the new one.    */
    out = kissvg_Line2D_Intersection(L, orthline);

    /*  Destroy the created line and return the answer.                       */
    kissvg_Destroy_Line2D(&orthline);
    return out;
}

/*  Given a circle C and a point P in the plane, compute the closest point on *
 *  the circle to P.                                                          */
kissvg_TwoVector kissvg_Closest_Point_On_Circle(kissvg_Circle *C,
                                                kissvg_TwoVector P)
{
    /*  Declare all necessary variables.                                      */
    kissvg_TwoVector out, center;
    kissvg_TwoVector Pcirc, Vcirc;
    kissvg_Line2D *L;
    double radius, norm;

    /*  Create a variable for the name of the function for error checking.    */
    const char *FuncName = "kissvg_ClosestPointOnCircle";

    /*  Check the input circle for errors. This will abort if there are.      */
    __check_circle_error(C, FuncName);

    /*  If the input circle is a line (circle with infinite radius), use      *
     *  kissvg_ClosestPointOnLine to perform the computation.                 */
    if (kissvg_Circle_Is_Line(C))
    {

        /*  Extract the point and tangent defining the line.                  */
        Pcirc = kissvg_Circle_Point(C);
        Vcirc = kissvg_Circle_Tangent(C);

        /*  Create an actual kissvg_Line2D from these values.                 */
        L = kissvg_Create_Line2D_From_Point_And_Tangent(Pcirc, Vcirc, NULL);

        /*  Compute the closest point using this line, and then destroy L.    */
        out = kissvg_Closest_Point_On_Line2D(L, P);
        kissvg_Destroy_Line2D(&L);
    }

    /*  Otherwise the input is an actual circle so we compute as such.        */
    else
    {
        /*  Extract the center and radius from the circle.                    */
        center = kissvg_Circle_Center(C);
        radius = kissvg_Circle_Radius(C);

        /*  Get a vector pointing from P to the center of the circle and      *
         *  compute its norm.                                                 */
        out = kissvg_TwoVector_Subtract(P, center);
        norm = kissvg_Euclidean_Norm_2D(out);

        /* If the norm is zero, the input point is the center, so simple set  *
         *  (r, 0) as the closest point (we'll shift by center after).        */
        if (norm == 0.0)
            out = kissvg_New_TwoVector(radius, 0.0);

        /*  Otherwise the closest point is the one on the circle between the  *
         *  center and the given point. Compute this.                         */
        else
            out = kissvg_TwoVector_Scale(radius/norm, out);

        /*  The above computation translated to the origin. Shift by center.  */
        out = kissvg_TwoVector_Add(out, center);
    }

    return out;
}

/*  Given a circle C and a point P in the plane, compute the closest point on *
 *  the circle to P.                                                          */
kissvg_TwoVector kissvg_Furthest_Point_On_Circle(kissvg_Circle *C,
                                                 kissvg_TwoVector P)
{
    /*  Declare all necessary variables.                                      */
    kissvg_TwoVector out, center;
    double radius, norm;

    /*  Create a variable for the name of the function for error checking.    */
    const char *FuncName = "kissvg_FurthestPointOnCircle";

    /*  Check the input circle for errors. This will abort if there are.      */
    __check_circle_error(C, FuncName);

    /*  If the input circle is a line (circle with infinite radius), return   *
     *  the point at infinity (inf, inf).                                     */
    if (kissvg_Circle_Is_Line(C))
        out = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);

    /*  Otherwise the input is an actual circle so we compute as such.        */
    else
    {
        /*  Extract the center and radius from the circle.                    */
        center = kissvg_Circle_Center(C);
        radius = kissvg_Circle_Radius(C);

        /*  Get a vector pointing from P to the center of the circle and      *
         *  compute its norm.                                                 */
        out = kissvg_TwoVector_Subtract(P, center);
        norm = kissvg_Euclidean_Norm_2D(out);

        /*  If the norm is zero, the input point is the center, so simple set *
         *  (-r, 0) as the furthest point (we'll shift by center after). We   *
         *  do this since the closest point is set to (r, 0) in this case and *
         *  we want closest and furthest to be antepodal points on the circle.*/
        if (norm == 0.0)
            out = kissvg_New_TwoVector(radius, 0.0);

        /*  Otherwise the furthest point is the one on the circle antepodal   *
         *  to the one between the center and the given point. Compute this.  */
        else
            out = kissvg_TwoVector_Scale(-radius/norm, out);

        /*  The above computation translated to the origin. Shift by center.  */
        out = kissvg_TwoVector_Add(out, center);
    }

    return out;
}

kissvg_TwoVector kissvg_Plane_To_Disk_Homeo(kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double px, py;
    double outx, outy;
    double norm;
    double scale_factor;

    px = kissvg_TwoVector_X_Component(P);
    py = kissvg_TwoVector_Y_Component(P);

    if ((px == 0.0) && (py == 0.0))
    {
        outx = 0.0;
        outy = 0.0;
    }
    else
    {
        norm = kissvg_Euclidean_Norm_2D(P);
        outx = px/norm;
        outy = py/norm;

        scale_factor = (-1.0 + kissvg_Sqrt_Double(4.0*norm*norm + 1.0)) /
                       (2.0*norm);

        outx *= scale_factor;
        outy *= scale_factor;
    }
    out = kissvg_New_TwoVector(outx, outy);

    return out;
}


kissvg_TwoVector *kissvg_Circle_Intersection(kissvg_Circle *C0,
                                             kissvg_Circle *C1)
{
    kissvg_TwoVector center0, center1;
    double r0, r1;
    double dist;
    double a, h;
    double x0, y0;
    double x1, y1;
    double x2, y2;
    double x_factor, y_factor;

    double inter0_x, inter0_y;
    double inter1_x, inter1_y;

    kissvg_TwoVector *intersections;

    /*  Create a variable for the name of the function for error checking.    */
    const char *FuncName = "kissvg_FurthestPointOnCircle";

    /*  Check the input circles for errors. This will abort if there are.     */
    __check_circle_error(C0, FuncName);
    __check_circle_error(C1, FuncName);

    /*  Extract the centers from the circles.                                 */
    center0 = kissvg_Circle_Center(C0);
    center1 = kissvg_Circle_Center(C1);

    /*  Extract the radii.                                                    */
    r0 = kissvg_Circle_Radius(C0);
    r1 = kissvg_Circle_Radius(C1);

    if (r0 <= 0.0)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CircleCircleIntersection\n\n"
            "r0 is not positive."
        );
        exit(0);
    }
    else if (r1 <= 0.0)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CircleCircleIntersection\n\n"
            "r1 is not positive."
        );
        exit(0);
    }

    dist = kissvg_Euclidean_Norm_2D(
        kissvg_TwoVector_Subtract(center0, center1)
    );

    /*  If any of these scenarios are true, the intersection set is empty.    */
    if ((dist > (r0+r1))                  ||
        (dist < kissvg_Abs_Double(r1-r0)) ||
        ((dist == 0.0) && (r0 != r1)))
        intersections = NULL;

    /*  If this is true, the two circels are the same and there are           *
     *  infinitely many solutions.                                            */
    else if ((dist == 0.0) && (r0 == r1))
    {
        intersections = malloc(sizeof(*intersections));
        intersections[0] = kissvg_New_TwoVector(kissvg_Infinity,
                                                kissvg_Infinity);
    }

    /*  Otherwise, there is a legitimate solution.                            */
    else
    {
        /*  Allocate memory for two solutions, even if they're the same.      */
        intersections = malloc(sizeof(*intersections)*2);

        /*  Extract the x and y coordinates of the centers.                   */
        x0 = kissvg_TwoVector_X_Component(center0);
        y0 = kissvg_TwoVector_Y_Component(center0);

        x1 = kissvg_TwoVector_X_Component(center1);
        y1 = kissvg_TwoVector_Y_Component(center1);

        /*  Compute some necessary variables.                                 */
        a = (r0*r0 - r1*r1 + dist*dist) / (2.0*dist);
        h = sqrt(r0*r0 - a*a);

        x2 = x0 + (a/dist) * (x1-x0);
        y2 = y0 + (a/dist) * (y1-y0);

        /*  If these variables are zero, both solutions are identical. This   *
         *  is fine, the output will still have two solutions allocated.      */
        x_factor = h*(y1 - y0)/dist;
        y_factor = h*(x1 - x0)/dist;

        /*  Compute the solutions.                                            */
        inter0_x = x2 + x_factor;
        inter0_y = y2 - y_factor;
        inter1_x = x2 - x_factor;
        inter1_y = y2 + y_factor;

        /*  Store the solutions in the intersections variable.                */
        intersections[0] = kissvg_New_TwoVector(inter0_x, inter0_y);
        intersections[1] = kissvg_New_TwoVector(inter1_x, inter1_y);
    }

    return intersections;
}

kissvg_Circle **kissvg_Apollonius_Problem(kissvg_Circle *C0,
                                          kissvg_Circle *C1,
                                          kissvg_Circle *C2)
{
    kissvg_Circle **solutions;
    kissvg_Palette *palette;
    kissvg_TwoVector center1, center2, center3;
    kissvg_TwoVector center;
    double r1, r2, r3;
    double x1, x2, x3;
    double y1, y2, y3;
    double rcp;
    long n;

    /*  There are eight solutions, so set N to 8.                             */
    long N = 8;

    double a12, b12, c12, d12;
    double a13, b13, c13, d13;

    double A, B, C, D;
    double x, y, radius;

    double alpha, beta, gamma;

    double s1[8] = {-1.0, -1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0};
    double s2[8] = {-1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0,  1.0};
    double s3[8] = {-1.0,  1.0, -1.0,  1.0, -1.0,  1.0, -1.0,  1.0};

    /*  Create a variable for the name of the function for error checking.    */
    const char *FuncName = "kissvg_ApolloniusProblem";

    /*  Check the input circles for errors. This will abort if there are.     */
    __check_circle_error(C0, FuncName);
    __check_circle_error(C1, FuncName);
    __check_circle_error(C2, FuncName);

    palette = kissvg_Get_Palette(C0);

    /*  There are, in general, eight solutions so allocate eight slots.       */
    solutions = malloc(sizeof(*solutions) * N);

    center1 = kissvg_Circle_Center(C0);
    center2 = kissvg_Circle_Center(C1);
    center3 = kissvg_Circle_Center(C2);

    r1 = kissvg_Circle_Radius(C0);
    r2 = kissvg_Circle_Radius(C1);
    r3 = kissvg_Circle_Radius(C2);

    x1 = kissvg_TwoVector_X_Component(center1);
    y1 = kissvg_TwoVector_Y_Component(center1);

    x2 = kissvg_TwoVector_X_Component(center2);
    y2 = kissvg_TwoVector_Y_Component(center2);

    x3 = kissvg_TwoVector_X_Component(center3);
    y3 = kissvg_TwoVector_Y_Component(center3);

    for (n=0; n<N; ++n)
    {
        a12 = 2.0*(x1 - x2);
        b12 = 2.0*(y1 - y2);
        c12 = 2.0*(s2[n]*r2 - s1[n]*r1);
        d12 = (x2*x2 + y2*y2 - r2*r2) - (x1*x1 + y1*y1 - r1*r1);

        a13 = 2.0*(x1 - x3);
        b13 = 2.0*(y1 - y3);
        c13 = 2.0*(s3[n]*r3 - s1[n]*r1);
        d13 = (x3*x3 + y3*y3 - r3*r3) - (x1*x1 + y1*y1 - r1*r1);

        rcp = a12*b13 - b12*a13;

        if (rcp == 0.0)
        {
            if (((a12 == 0.0) && (b12 == 0.0)) ||
                ((a13 == 0.0) && (b13 == 0.0)))
            {
                puts("Warning: KissVG\n"
                     "\tFunction: kissvg_ApolloniusProblem\n\n"
                     "\tTwo of the Circles are Identical.");
                center = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
                radius = kissvg_Infinity;
            }
            else
            {

            }
            center = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
            radius = kissvg_Infinity;

            solutions[n] = kissvg_Create_Circle(center, radius, palette);
        }
        else
        {
            rcp = 1.0/rcp;
            A = (-b13*d12 + b12*d13)*rcp;
            B = (-b13*c12 + b12*c13)*rcp;
            C = ( a13*d12 - a12*d13)*rcp;
            D = ( a13*c12 - a12*c13)*rcp;

            alpha = -1.0 + B*B + D*D;
            beta = 2.0*(A*B + C*D + r1*s1[n] - B*x1 - D*y1);
            gamma = A*A + C*C - r1*r1 + x1*x1 + y1*y1 - 2.0*(A*x1 + C*y1);

            radius = (-beta - sqrt(beta*beta - 4.0*alpha*gamma))/(2.0*alpha);

            if (radius < 0.0)
                radius = (-beta+sqrt(beta*beta - 4.0*alpha*gamma))/(2.0*alpha);

            x = A + B*radius;
            y = C + D*radius;

            center = kissvg_New_TwoVector(x, y);

            solutions[n] = kissvg_Create_Circle(center, radius, palette);
        }
    }
    return solutions;
}

kissvg_TwoVector kissvg_Line2D_Intersection(kissvg_Line2D *L0,
                                            kissvg_Line2D *L1)
{
    kissvg_TwoVector P0, P1;
    kissvg_TwoVector V0, V1;
    kissvg_TwoVector inter;
    kissvg_TwoVector P1P0;
    kissvg_TwoVector times;
    kissvg_TwoByTwoMatrix A, inverseA;
    double v0x, v0y;
    double v1x, v1y;
    double t0;
    double det;

    P0 = kissvg_Line2D_Point(L0);
    V0 = kissvg_Line2D_Tangent(L0);

    P1 = kissvg_Line2D_Point(L1);
    V1 = kissvg_Line2D_Tangent(L1);

    v0x = kissvg_TwoVector_X_Component(V0);
    v0y = kissvg_TwoVector_Y_Component(V0);

    v1x = kissvg_TwoVector_X_Component(V1);
    v1y = kissvg_TwoVector_Y_Component(V1);

    det = v1x*v0y -v0x*v1y;

    if (det == 0.0)
    {
        inter = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);

        return inter;
    }
    else
    {
        P1P0 = kissvg_TwoVector_Subtract(P1, P0);
        A = kissvg_New_TwoByTwoMatrix(v0x, -v1x, v0y, -v1y);
        inverseA = kissvg_Inverse_TwoByTwoMatrix(A);
        times = kissvg_TwoVector_Matrix_Transform(inverseA, P1P0);
        t0 = kissvg_TwoVector_X_Component(times);

        inter = kissvg_TwoVector_Add(P0, kissvg_TwoVector_Scale(t0, V0));
        return inter;
    }
}
