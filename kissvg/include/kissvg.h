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
 *                             kissvg_euclidean                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for computational Euclidean geometry. This includes  *
 *      basic 2D and 3D vector geometry functions, and simple constructions   *
 *      from Euclidean geometry like determining the intersections of circles.*
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) kissvg_bool.h:                                                        *
 *      Header file where kissvg_bool is typedef'd, as well as kissvg_true    *
 *      and kissvg_false.                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 18, 2020                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_H
#define _KISSVG_H

#include "kissvg_bool.h"
#include <cairo.h>

/*  First we'll define the basics of two dimensional Euclidean geometry, and  *
 *  then three dimensional after. But first-first, we typedef things.         */

/*  We'll define a plane point the same way we do a complex value. See        *
 *  kissvg_complex.h for this typedef.                                        */
typedef struct kissvg_TwoVector {
    double dat[2];
} kissvg_TwoVector;

typedef struct kissvg_TwoMatrix {
    double dat[2][2];
} kissvg_TwoMatrix;

/*  Three-Vectors (i.e. points in R^3) are defined similarly.                 */
typedef struct kissvg_ThreeVector {
    double dat[3];
} kissvg_ThreeVector;

/*  Note, one should not access the data in these structures directly, but    *
 *  rather use the functions defined below, like kissvg_TwoVectorXComponent   *
 *  and so on to access the elements, and kissvg_NewTwoVector or              *
 *  kissvg_NewThreeVector to create new vectors.                              */

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_NewTwoVector                                                   *
 *  Purpose:                                                                  *
 *      Create a new kissvg_TwoVector from two doubles, the x component and   *
 *      the y. This is the main function for defining kissvg_TwoVector's.     *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          The x component of the desired vector.                            *
 *      double y:                                                             *
 *          The y component of the desired vector.                            *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector:                                                     *
 *          An instance of the kissvg_TwoVector structure with zeroth entry   *
 *          set to x and first entry set to y. This is mathematically         *
 *          equivalent to the vector (x, y).                                  *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_NewTwoVector(double x, double y);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_NewTwoMatrix                                                   *
 *  Purpose:                                                                  *
 *      Create a new kissvg_TwoMatrix from four doubles. This returns:        *
 *           -       -                                                        *
 *          |  a   b  |                                                       *
 *          |  c   d  |                                                       *
 *           -       -                                                        *
 *  Arguments:                                                                *
 *      double a:                                                             *
 *      double b:                                                             *
 *      double c:                                                             *
 *      double d:                                                             *
 *  Outputs:                                                                  *
 *      kissvg_TwoMatrix:                                                     *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoMatrix kissvg_NewTwoMatrix(double a, double b,
                                            double c, double d);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorMatrixTransform                                       *
 *  Purpose:                                                                  *
 *      Given a matrix A and a vector P, computes AP.                         *
 *  Arguments:                                                                *
 *      kissvg_TwoMatrix A:                                                   *
 *          A 2x2 matrix.                                                     *
 *      kissvg_TwoVector P:                                                   *
 *          A two element vector.                                             *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector out:                                                 *
 *          The vector P transformed by A.                                    *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_TwoVectorMatrixTransform(kissvg_TwoMatrix A,
                                                        kissvg_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_RotationMatrix2D                                               *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector R:                                                   *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoMatrix kissvg_RotationMatrix2D(double theta);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorXComponent                                            *
 *  Purpose:                                                                  *
 *      Returns the x component of a kissvg_TwoVector. This is equivalent to  *
 *      the mathematical concept of projecting a vector along the y-axis.     *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *  Outputs:                                                                  *
 *      double x:                                                             *
 *          The x component of the kissvg_TwoVector P. If we represent P by   *
 *          (x, y), this is equivalent to returning x.                        *
 ******************************************************************************/
#define kissvg_TwoVectorXComponent(P) (P.dat[0])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorYComponent                                            *
 *  Purpose:                                                                  *
 *      Returns the y component of a kissvg_TwoVector. This is equivalent to  *
 *      the mathematical concept of projecting a vector along the x-axis.     *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *  Outputs:                                                                  *
 *      double y:                                                             *
 *          The y component of the kissvg_TwoVector P. If we represent P by   *
 *          (x, y), this is equivalent to returning y.                        *
 ******************************************************************************/
#define kissvg_TwoVectorYComponent(P) (P.dat[1])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoMatrixComponent                                             *
 *  Purpose:                                                                  *
 *      Returns the (m,n) element of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      kissvg_TwoMatrix A:                                                   *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m,n) component of the kissvg_TwoMatrix                       *
 ******************************************************************************/
#define kissvg_TwoMatrixComponent(P, m, n) (P.dat[m][n])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorAdd                                                   *
 *  Purpose:                                                                  *
 *      Given two kissvg_TwoVector's, compute the vector sum of them.         *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *      kissvg_TwoVector Q:                                                   *
 *          The vector we wish to add to P.                                   *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector sum:                                                 *
 *          The vector sum P+Q.                                               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_TwoVectorAdd(kissvg_TwoVector P,
                                            kissvg_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorSubtract                                              *
 *  Purpose:                                                                  *
 *      Given two kissvg_TwoVector's P and Q, compute P-Q.                    *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *      kissvg_TwoVector Q:                                                   *
 *          The vector we wish to subtract from P.                            *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector sum:                                                 *
 *          The vector subtraction P-Q.                                       *
 *  NOTE:                                                                     *
 *      Unlike kissvg_TwoVectorAdd, the order of the inputs for               *
 *      kissvg_TwoVectorSubtract matters. This routine compute P - Q, and not *
 *      Q - P. That is, we subtract the second argument from the first one.   *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_TwoVectorSubtract(kissvg_TwoVector P,
                                                 kissvg_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorScale                                                 *
 *  Purpose:                                                                  *
 *      Scale a vector P by a scalar (real number) r.                         *
 *  Arguments:                                                                *
 *      double r:                                                             *
 *          An arbitrary real number.                                         *
 *      kissvg_TwoVector P:                                                  *
 *          The vector we wish to scale by r.                                 *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector sum:                                                 *
 *          The vector sum P+Q.                                               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_TwoVectorScale(double r, kissvg_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_EuclideanNorm2D                                                *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a kissvg_TwoVector.                    *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *  Outputs:                                                                  *
 *      double norm:                                                          *
 *          The Euclidean norm of P. If we represent P by (x, y), norm is     *
 *          defined by norm = sqrt(x^2 + y^2).                                *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern double kissvg_EuclideanNorm2D(kissvg_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_DotProduct2D                                                   *
 *  Purpose:                                                                  *
 *      Given two kissvg_TwoVector's P and Q, compute the dot product.        *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *      kissvg_TwoVector Q:                                                   *
 *          Another vector.                                                   *
 *  Outputs:                                                                  *
 *      double dot_prod:                                                      *
 *          The Euclidean dot product of P and Q. If we represent P and Q by  *
 *          (x0, y0) and (x1, y1), dot_prod is defined to be                  *
 *          dot_prod = x0*x1 + y0*y1.                                         *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern double kissvg_DotProduct2D(kissvg_TwoVector P, kissvg_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_MidPoint2D                                                     *
 *  Purpose:                                                                  *
 *      Compute the midpoint of two kissvg_TwoVector's.                       *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *      kissvg_TwoVector Q:                                                   *
 *          Another vector.                                                   *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector mid:                                                 *
 *          The midpoint of P and Q, defined to be (P + Q) / 2.               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_MidPoint2D(kissvg_TwoVector P,
                                          kissvg_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_RelAngle2D                                                     *
 *  Purpose:                                                                  *
 *      Compute the angle between P and Q with respect to the point O.        *
 *                                                                            *
 *     y^                                                                     *
 *      |                           Q *                                       *
 *      |                            /                                        *
 *      |                           /                                         *
 *      |                          /                                          *
 *      |                         /                                           *
 *      |                        /__                                          *
 *      |                       /    \  Theta                                 *
 *      |                      /      |                                       *
 *      |                     *----------------*                              *
 *      |                     O                P                              *
 *      |                                                                     *
 *      |                                                                     *
 *     -|-------------------------------------------------->                  *
 *                                                         x                  *
 *  Arguments:                                                                *
 *      kissvg_TwoVector P:                                                   *
 *          An arbitrary kissvg_TwoVector.                                    *
 *      kissvg_TwoVector Q:                                                   *
 *          Another vector.                                                   *
 *  Outputs:                                                                  *
 *      double angle:                                                         *
 *          The angle between P and Q relative to O.                          *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern double kissvg_RelAngle2D(kissvg_TwoVector O,
                                kissvg_TwoVector P,
                                kissvg_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_MidPoint2D                                                     *
 *  Purpose:                                                                  *
 *      Determine if three kissvg_TwoVector's are collinear.                  *
 *  Arguments:                                                                *
 *      kissvg_TwoVector A:                                                   *
 *          A kissvg_TwoVector.                                               *
 *      kissvg_TwoVector B:                                                   *
 *          Another vector.                                                   *
 *      kissvg_TwoVector C:                                                   *
 *          A third vector.                                                   *
 *  Outputs:                                                                  *
 *      kissvg_bool is_collinear:                                             *
 *          A Boolean that is true if A, B, and C are collinear, and false    *
 *          otherwise.                                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_bool kissvg_IsCollinear(kissvg_TwoVector A,
                                      kissvg_TwoVector B,
                                      kissvg_TwoVector C);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_FindCenter2D                                                   *
 *  Purpose:                                                                  *
 *      Find the center of three kissvg_TwoVector's. If the points are        *
 *      collinear the return is (inf, inf). In other words, three collinear   *
 *      points have their center "at infinity."                               *
 *  Arguments:                                                                *
 *      kissvg_TwoVector A:                                                   *
 *          A kissvg_TwoVector.                                               *
 *      kissvg_TwoVector B:                                                   *
 *          Another vector.                                                   *
 *      kissvg_TwoVector C:                                                   *
 *          A third vector.                                                   *
 *  Outputs:                                                                  *
 *      kissvg_Two_vector center:                                             *
 *          The center of A, B, C. That is, the point such that there exists  *
 *          a circle centered about it that contains the points A, B, C. If   *
 *          A, B, and C are collinear, center is (inf, inf).                  *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg_euclidean.c                *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_FindCenter2D(kissvg_TwoVector A,
                                            kissvg_TwoVector B,
                                            kissvg_TwoVector C);

extern kissvg_TwoVector kissvg_PlaneToDiskHomeo(kissvg_TwoVector P);

extern kissvg_TwoVector *kissvg_CircleCircleIntersection(kissvg_TwoVector P0,
                                                         double r0,
                                                         kissvg_TwoVector P1,
                                                         double r1);

extern kissvg_bool CircleCircleIntersectionIsEmpty(kissvg_TwoVector *Intersect);
extern kissvg_bool CircleCircleIntersectionIsAll(kissvg_TwoVector *Intersect);

typedef struct kissvg_Path2D {
    kissvg_TwoVector *data;
    unsigned long N_Pts;
    kissvg_bool is_closed;
    kissvg_bool kissvg_error_occured;
    kissvg_bool filldraw;
    kissvg_bool has_arrow;
    char *kissvg_error_message;
    double linewidth;
    double arrow_fill_color[3];
    double arrow_color[3];
    double fill_color[3];
    double line_color[3];
    double arrowsize;
} kissvg_Path2D;

#define kissvg_Path2DSize(path) (path->N_Pts)
#define kissvg_Path2DData(path) (path->data)
#define kissvg_Path2DSetError(path) (path->kissvg_error_occured = 1)
#define kissvg_Path2DClosePath(path) (path->is_closed = kissvg_true)
#define kissvg_Path2DIsClosed(path) (path->is_closed)
#define kissvg_Path2DSetFillDraw(path) (path->filldraw = kissvg_true)
#define kissvg_Path2DIsFill(path) (path->filldraw)
#define kissvg_Path2DFillColor(path) (path->fill_color)
#define kissvg_Path2DLineColor(path) (path->line_color)
#define kissvg_Path2DLineWidth(path) (path->linewidth)
#define kissvg_Path2DHasArrow(path) (path->has_arrow)
#define kissvg_Path2DCreateArrow(path) (path->has_arrow = kissvg_true)
#define kissvg_Path2DArrowSize(path) (path->arrowsize)

#define kissvg_Path2DSetErrorMessage(path, message)                            \
    (strcpy(path->kissvg_error_message, message))

extern void kissvg_Path2DSetLineWidth(kissvg_Path2D *path, double linewidth);
extern void kissvg_Path2DSetArrowSize(kissvg_Path2D *path, double linewidth);

extern kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start);
extern void kissvg_DestroyPath2D(kissvg_Path2D *path);

extern void kissvg_Path2DSetFillColors(kissvg_Path2D *path,
                                       double red,
                                       double green,
                                       double blue);

extern void kissvg_AppendPath2D(kissvg_Path2D *path,
                                kissvg_TwoVector P);

extern void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);
extern void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);

#endif
/*  End of include guard.                                                     */
