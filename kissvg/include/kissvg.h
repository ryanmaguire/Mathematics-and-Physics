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

#define kissvg_DefaultPen 0.6
#define kissvg_DefaultAxes 1.0
#define kissvg_DefaultArrow 0.08
#define kissvg_DefaultTickSize 0.2
#define kissvg_DefaultTickHeight 0.1
#define kissvg_DefaultTickDist 1.0

/*  First we'll define the basics of two dimensional Euclidean geometry, and  *
 *  then three dimensional after. But first-first, we typedef things.         */

/*  We'll define a plane point the same way we do a complex value. See        *
 *  kissvg_complex.h for this typedef.                                        */
typedef struct kissvg_TwoVector {
    double dat[2];
} kissvg_TwoVector;

/*  Simple struct for 2x2 matrices. These are primarily used for applying     *
 *  linear transformations to kissvg_TwoVector's.                             */
typedef struct kissvg_TwoByTwoMatrix {
    double dat[2][2];
} kissvg_TwoByTwoMatrix;

/*  This struct is required for most routines and is included as an attribute *
 *  of several data types like kissvg_Path2D and kissvg_Axis2D. It is used to *
 *  convert between the geometry of the actual output file                    *
 *  (.ps, .svg, .pdf, etc.) and the coordinates we actually use during our    *
 *  computations.                                                             */
typedef struct kissvg_Canvas2D {
    /*  x_scale and y_scale are the scales applied to the user's coordinates  *
     *  so that the image is the correct size in the actual file.             */
    double x_scale;
    double y_scale;

    /*  x_shift and y_shift are used to center the figure. The center is not  *
     *  taken to be (0, 0), but rather the mean of the user provided X_MIN    *
     *  and X_MAX for the x-axis, and Y_MIN and Y_MAX for the y-axis.         */
    double x_shift;
    double y_shift;
} kissvg_Canvas2D;

/*  This is the primary structure for using colors in drawings. It is a       *
 *  structure which contains an array of three double corresponding to Red,   *
 *  Green, and Blue (in that order). Functions and macros are providing for   *
 *  setting these values so one should never have to do so directly.          */
typedef struct kissvg_Color {
    double dat[3];
} kissvg_Color;

typedef enum {
    kissvg_StealthArrow,
    kissvg_TriangularArrow
} kissvg_ArrowType;

/*  This is the primary data type used for drawing 2 dimensional figures. It  *
 *  contains a lot of information, and various functions and macros are       *
 *  provided below for accessing the data and altering it.                    */
typedef struct kissvg_Path2D {
    /*  This pointer contains all of the points of the path.                  */
    kissvg_TwoVector *data;

    /*  The number of points in the data pointer.                             */
    unsigned long N_Pts;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Boolean for determining if the path is meant to be a closed path of   *
     *  an open path. By default it is false.                                 */
    kissvg_Bool is_closed;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false. If this Boolean is set to true, the various  *
     *  drawing routines will automatically set is_closed to true.            */
    kissvg_Bool fill_draw;

    /*  Boolean for determining if the path has arrows on it.                 */
    kissvg_Bool has_arrow;

    /*  Booleans for the directions of the arrows.                            */
    kissvg_Bool *reverse_arrow;

    /*  The type of arrow to draw.                                            */
    int arrow_type;

    /*  Pointer to values between 0 and 1 specifying the location of arrows.  */
    double *arrow_pos;

    /*  The number of arrow.                                                  */
    long N_Arrows;

    /*  The colors of the interior of the arrows drawn. The nth color should  *
     *  correspond to the nth element of arrow_pos.                           */
    kissvg_Color **arrow_fill_color;

    /*  The colors of the outline of the arrows. The nth color should also    *
     *  correspond to the nth element of arrow_pos. Note that if the arrow is *
     *  not placed at the end point and the arrow color differs from the line *
     *  color it may look strange.                                            */
    kissvg_Color **arrow_color;

    /*  The color of the interior of the region encloded by the path. This is *
     *  only used if the fill_draw Boolean is set.                            */
    kissvg_Color *fill_color;

    /*  The color of the path.                                                */
    kissvg_Color *line_color;

    /*  The width of the path.                                                */
    double line_width;

    /*  The radius of the arrow heads. The arrow head is defined by three     *
     *  points on a circle about the point corresponding to the arrow_pos.    */
    double *arrow_size;

    /*  The canvas for the entire drawing. Note this should be a constant for *
     *  the entire drawing and should not vary between paths.                 */
    kissvg_Canvas2D *canvas;
} kissvg_Path2D;

/*  Data structure for drawing and customizing axes with KissVG. There are a  *
 *  plethora of options including tick marks and colors.                      */
typedef struct kissvg_Axis2D {

    /*  The start of the axis (x_0, y_0).                                     */
    kissvg_TwoVector start;

    /*  The end of the axis (x_1, y_1). Note that is has_arrow is set, which  *
     *  by default it will be, then the axis will be +arrow_size longer to    *
     *  account for the arrow head. This may make your figure fall out of the *
     *  page if you left no room when setting X_MIN/X_MAX/Y_MIN/Y_MAX.        */
    kissvg_TwoVector finish;

    /*  Where the ticks should start. Usually you will be plotting the x and  *
     *  y axes so it is reasonable to set this as an integer pair like (0, 0).*/
    kissvg_TwoVector tick_start;

    /*  Where the tick marks stop.                                            */
    kissvg_TwoVector tick_finish;

    /*  Boolean for determining if an arrow head should be placed on the axis.*/
    kissvg_Bool has_arrow;

    /*  Booleans for the directions of the arrows.                            */
    kissvg_Bool *reverse_arrow;

    /*  Boolean for use of tick marks. Default is False.                      */
    kissvg_Bool has_ticks;

    /*  Boolean for only have ticks "above" the axis. For the x-axis, where   *
     *  tick_start is to the left of tick_finish, the ticks will indeed be    *
     *  pointing "up". For the y-axis, with tick_start below tick_finish, the *
     *  ticks will point to the "left" since this is just a rotation of the   *
     *  x-axis. Keep this in mind when drawing. If you want up ticks for the  *
     *  x-axis but right ticks for the y-axis, use down_ticks for y.          */
    kissvg_Bool up_ticks;

    /*  Like up_ticks, but used to point the ticks "down".                    */
    kissvg_Bool down_ticks;

    /*  The distance between ticks. This should be either 0.25, 0.5, 1.0, or  *
     *  some integer. This is to get full use of tick_height,                 *
     *  tick_semi_height, and tick_semi_semi_height which divides plots ticks *
     *  of different heights on a cycle of four ticks. Any value is allowed,  *
     *  however.                                                              */
    double ticks_dx;

    /*  The major height of the ticks. This is the height of every fourth     *
     *  tick mark. That is, when the tick number is divisible by four, this   *
     *  height is used.                                                       */
    double ticks_height;

    /*  The tick height for the ticks whose number is even, but not divisible *
     *  by four.                                                              */
    double ticks_semi_height;

    /*  The tick height for the odd-numbered ticks.                           */
    double ticks_semi_semi_height;

    /**************************************************************************
     *  Below is an example of what the ticks will look like. The tallest     *
     *  are the ticks_height, smallest are ticks_semi_semi_height, and the    *
     *  middle is the ticks_semi_height. Note, by default when an axis is     *
     *  created the three ticks values are set to be the same.                *
     *                                                                        *
     *  |                               |                               |     *
     *  |               |               |               |               |     *
     *  |_______|_______|_______|_______|_______|_______|_______|_______|     *
     **************************************************************************/

    /*  The positions of the arrows, which should be number between 0 and 1.  */
    double *arrow_pos;

    /*  The number of arrows the axis contains.                               */
    long N_Arrows;

    /*  The type of arrow to draw.                                            */
    int arrow_type;

    /*  The fill colors of the arrow heads. Defaults are black.               */
    kissvg_Color **arrow_fill_color;

    /*  The colors of the outline of the arrow heads. Defaults are black.     */
    kissvg_Color **arrow_color;

    /*  The color of the axis. Default is black.                              */
    kissvg_Color *line_color;

    /*  The color of the ticks. Default is black.                             */
    kissvg_Color *tick_color;

    /*  The thickness of the axis. Default is the macro kissvg_DefaultAxes.   */
    double line_width;

    /*  The size of the arrow heads. Default is the macor kissvg_DefaultArrow.*/
    double *arrow_size;

    /*  The size of the ticks. Default is zero since ticks are not drawn by   *
     *  default and need to be set by the user.                               */
    double tick_size;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas2D *canvas;
} kissvg_Axis2D;

/*  This is the primary structure for working with and drawing circles. It    *
 *  contains geometric data as well as visual data for how to draw it.        */
typedef struct kissvg_Circle {

    /*  The geometrical data of the circle. We need the center and the radius.*/
    kissvg_TwoVector center;
    double radius;

    /*  The rest are for drawing the circle. If you only need the circle for  *
     *  computations then you need not set any of these.                      */

    /*  Boolean for determining if the circle has arrows. By default circles  *
     *  do not have arrows so the arrow_fill_color and arrow_color variables  *
     *  below are not set.                                                    */
    kissvg_Bool has_arrow;

    /*  Booleans for the directions of the arrows.                            */
    kissvg_Bool *reverse_arrow;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false.                                              */
    kissvg_Bool fill_draw;

    /*  The color of the interior of the region encloded by the path. This is *
     *  only used if the fill_draw Boolean is set.                            */
    kissvg_Color *fill_color;

    /*  The positions of the arrows, which should be numbers between 0 and 1. */
    double *arrow_pos;

    /*  The number of arrows the axis contains.                               */
    long N_Arrows;

    /*  The type of arrow to draw.                                            */
    int arrow_type;

    /*  The fill colors of the arrow heads. Defaults are black.               */
    kissvg_Color **arrow_fill_color;

    /*  The colors of the outline of the arrow heads. Defaults are black.     */
    kissvg_Color **arrow_color;

    /*  The color of the axis. Default is black.                              */
    kissvg_Color *line_color;

    /*  The thickness of the axis. Default is the macro kissvg_DefaultAxes.   */
    double line_width;

    /*  The size of the arrow heads. Default is the macor kissvg_DefaultArrow.*/
    double *arrow_size;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas2D *canvas;
} kissvg_Circle;

/*  Note, one should not access the data in these structures directly, but    *
 *  rather use the functions defined below, like kissvg_TwoVectorXComponent   *
 *  and so on to access the elements, and kissvg_NewTwoVector to create       *
 *  vectors. It makes the code readable and the attributes of these           *
 *  structures are supposed to be "hidden" from the end-user.                 */

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                  Begin kissvg_TwoVector2D Functions                        *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

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
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_NewTwoVector(double x, double y);

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
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
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
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
#define kissvg_TwoVectorYComponent(P) (P.dat[1])

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
 *      The source code is contained in src/kissvg.c                          *
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
 *      The source code is contained in src/kissvg.c                          *
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
 *      kissvg_TwoVector P:                                                   *
 *          The vector we wish to scale by r.                                 *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector sum:                                                 *
 *          The vector sum P+Q.                                               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
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
 *      The source code is contained in src/kissvg.c                          *
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
 *      The source code is contained in src/kissvg.c                          *
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
 *      The source code is contained in src/kissvg.c                          *
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
 *      The source code is contained in src/kissvg.c                          *
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
 *      kissvg_Bool is_collinear:                                             *
 *          A Boolean that is true if A, B, and C are collinear, and false    *
 *          otherwise.                                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_Bool kissvg_IsCollinear(kissvg_TwoVector A,
                                      kissvg_TwoVector B,
                                      kissvg_TwoVector C);

extern kissvg_TwoVector kissvg_LineLineIntersection(kissvg_TwoVector P0,
                                                    kissvg_TwoVector V0,
                                                    kissvg_TwoVector P1,
                                                    kissvg_TwoVector V1);

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
 *      kissvg_TwoVector center:                                              *
 *          The center of A, B, C. That is, the point such that there exists  *
 *          a circle centered about it that contains the points A, B, C. If   *
 *          A, B, and C are collinear, center is (inf, inf).                  *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_FindCenter2D(kissvg_TwoVector A,
                                            kissvg_TwoVector B,
                                            kissvg_TwoVector C);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_PlaneToDiskHomeo                                               *
 *  Purpose:                                                                  *
 *      Transform, smoothly, the plane to the unit disk. This is the inverse  *
 *      of the diffeomorphism:                                                *
 *                                                                            *
 *                                  2 (x, y)                                  *
 *          f(x, y) =  -----------------------------------                    *
 *                      (1 - ||(x, y)||) (1 + ||(x, y)||)                     *
 *                                                                            *
 *      which stetches the unit disk out to the entire plane.                 *
 *  Arguments:                                                                *
 *      kissvg_TwoVector A:                                                   *
 *          A kissvg_TwoVector.                                               *
 *  Outputs:                                                                  *
 *      kissvg_Twovector B:                                                   *
 *          B transformed to the unit disk.                                   *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_PlaneToDiskHomeo(kissvg_TwoVector P);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                 Begin kissvg_TwoByTwoMatrix Functions                      *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoByTwoMatrixComponent                                        *
 *  Purpose:                                                                  *
 *      Returns the (m,n) element of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      kissvg_TwoByTwoMatrix A:                                              *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m,n) component of the kissvg_TwoByTwoMatrix                  *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
#define kissvg_TwoByTwoMatrixComponent(A, m, n) (A.dat[m][n])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_NewTwoByTwoMatrix                                              *
 *  Purpose:                                                                  *
 *      Create a new kissvg_TwoByTwoMatrix from four doubles. This returns:   *
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
 *      kissvg_TwoByTwoMatrix:                                                *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoByTwoMatrix kissvg_NewTwoByTwoMatrix(double a, double b,
                                                      double c, double d);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVectorMatrixTransform                                       *
 *  Purpose:                                                                  *
 *      Given a matrix A and a vector P, computes AP.                         *
 *  Arguments:                                                                *
 *      kissvg_TwoByTwoMatrix A:                                              *
 *          A 2x2 matrix.                                                     *
 *      kissvg_TwoVector P:                                                   *
 *          A two element vector.                                             *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector out:                                                 *
 *          The vector P transformed by A.                                    *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_TwoVectorMatrixTransform(kissvg_TwoByTwoMatrix A,
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
 *      kissvg_TwoByTwoMatrix R:                                              *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoByTwoMatrix kissvg_RotationMatrix2D(double theta);

extern kissvg_TwoByTwoMatrix kissvg_TwoByTwoMatrixScale(
    double r, kissvg_TwoByTwoMatrix P
);

extern kissvg_TwoByTwoMatrix kissvg_InverseTwoByTwoMatrix(
    kissvg_TwoByTwoMatrix A
);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                   Begin kissvg_Canvas2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Use these macros to access the data in a pointer to kissvg_Canvas2D.      */
#define kissvg_Canvas2DXScale(canvas) (canvas->x_scale)
#define kissvg_Canvas2DYScale(canvas) (canvas->y_scale)
#define kissvg_Canvas2DXShift(canvas) (canvas->x_shift)
#define kissvg_Canvas2DYShift(canvas) (canvas->y_shift)

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_CreateCanvas2D                                                 *
 *  Purpose:                                                                  *
 *      Create a kissvg_Canvas2D from two double arrays.                      *
 *  Arguments:                                                                *
 *      double scales[2]:                                                     *
 *          The x and y values used to scale the coordinate system to the     *
 *          geometry of the actual file.                                      *
 *      double shifts[2]:                                                     *
 *          The x and y values used to translate the figure so that it is     *
 *          centered in the actual file.                                      *
 *  Outputs:                                                                  *
 *      kissvg_Canvas2D canvas:                                               *
 *          The canvas for the image.                                         *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      Malloc is used in this file to allocate the appropriate memory. You   *
 *      must called kissvg_DestroyCanvas2D when you are done with the canvas. *
 ******************************************************************************/
extern kissvg_Canvas2D *kissvg_CreateCanvas2D(const double scales[2],
                                              const double shifts[2]);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_DestroyCanvas2D                                                *
 *  Purpose:                                                                  *
 *      Destory a kissvg_Canvas2D and free its memory.                        *
 *  Arguments:                                                                *
 *      kissvg_Canvas2D canvas:                                               *
 *          The canvas to be destroyed.                                       *
 *  Outputs:                                                                  *
 *      None, this is a void function.                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      This function must be called if kissvg_CreateCanvas2D was used. Since *
 *      kissvg_CreateCanvas2D should be used for every image, this function   *
 *      should always be called at the end.                                   *
 ******************************************************************************/
extern void kissvg_DestroyCanvas2D(kissvg_Canvas2D *canvas);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Color Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  The following are pre-defined colors for ease of use.                     */
static kissvg_Color __kissvg_Blue      = {{0.0, 0.2, 1.0}};
static kissvg_Color __kissvg_Green     = {{0.0, 1.0, 0.1}};
static kissvg_Color __kissvg_Red       = {{1.0, 0.1, 0.1}};
static kissvg_Color __kissvg_Black     = {{0.0, 0.0, 0.0}};
static kissvg_Color __kissvg_DarkGray  = {{0.3, 0.3, 0.3}};
static kissvg_Color __kissvg_Gray      = {{0.6, 0.6, 0.6}};
static kissvg_Color __kissvg_LightGray = {{0.8, 0.8, 0.8}};
static kissvg_Color __kissvg_White     = {{1.0, 1.0, 1.0}};

/*  Set the kissvg_ColorName pointers to point to __kissvg_ColorName.         */
kissvg_Color *kissvg_Blue      = &__kissvg_Blue;
kissvg_Color *kissvg_Green     = &__kissvg_Green;
kissvg_Color *kissvg_Red       = &__kissvg_Red;
kissvg_Color *kissvg_Black     = &__kissvg_Black;
kissvg_Color *kissvg_DarkGray  = &__kissvg_DarkGray;
kissvg_Color *kissvg_Gray      = &__kissvg_Gray;
kissvg_Color *kissvg_LightGray = &__kissvg_LightGray;
kissvg_Color *kissvg_White     = &__kissvg_White;

/*  Macros for accessing the data in the kissvg_Color struct.                 */
#define kissvg_RedColor(color) (color->dat[0])
#define kissvg_GreenColor(color) (color->dat[1])
#define kissvg_BlueColor(color) (color->dat[2])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_CreateColor                                                    *
 *  Purpose:                                                                  *
 *      Create a kissvg_Color from three doubles.                             *
 *  Arguments:                                                                *
 *      double red:                                                           *
 *          The amount of red in the color.                                   *
 *      double green:                                                         *
 *          The amount of green in the color.                                 *
 *      double blue:                                                          *
 *          The amount of blue in the color.                                  *
 *  Outputs:                                                                  *
 *      kissvg_Color color:                                                   *
 *          The color with rgb value (red, green, blue).                      *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      Malloc is used in this file to allocate the appropriate memory. You   *
 *      must called kissvg_DestroyColor when you are done with the color.     *
 ******************************************************************************/
extern kissvg_Color *kissvg_CreateColor(double red, double green, double blue);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_DestroyColor                                                   *
 *  Purpose:                                                                  *
 *      Destory a kissvg_Color and free its memory.                           *
 *  Arguments:                                                                *
 *      kissvg_Color color:                                                   *
 *          The color to be destroyed.                                        *
 *  Outputs:                                                                  *
 *      None, this is a void function.                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      This function must be called if kissvg_CreateColor was used.          *
 ******************************************************************************/
extern void kissvg_DestroyColor(kissvg_Color *color);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Path2D Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

#define kissvg_Path2DData(path) (path->data)
#define kissvg_Path2DSize(path) (path->N_Pts)

#define kissvg_Path2DIsClosed(path) (path->is_closed)
#define kissvg_Path2DIsFill(path) (path->fill_draw)
#define kissvg_Path2DHasArrow(path) (path->has_arrow)
#define kissvg_Path2DHasError(path) (path->error_occured)
#define kissvg_Path2DArrowType(path) (path->arrow_type)

#define kissvg_Path2DClosePath(path) (path->is_closed = kissvg_True)
#define kissvg_Path2DSetFillDraw(path) (path->filldraw = kissvg_True)
#define kissvg_Path2DSetError(path) (path->error_occured = kissvg_True)

#define kissvg_Path2DNumberOfArrows(path) (path->N_Arrows)

#define kissvg_Path2DArrowPos(path, n) (path->arrow_pos[n])
#define kissvg_Path2DArrowColor(path, n) (path->arrow_color[n])
#define kissvg_Path2DArrowFillColor(path, n) (path->arrow_fill_color[n])
#define kissvg_Path2DReverseArrow(path, n) (path->reverse_arrow[n])

#define kissvg_Path2DFillColor(path) (path->fill_color)
#define kissvg_Path2DLineColor(path) (path->line_color)

#define kissvg_Path2DLineWidth(path) (path->line_width)
#define kissvg_Path2DArrowSize(path, n) (path->arrow_size[n])

#define kissvg_Path2DCanvas(path) (path->canvas)

#define kissvg_Path2DXScale(path) (kissvg_Canvas2DXScale(path->canvas))
#define kissvg_Path2DYScale(path) (kissvg_Canvas2DYScale(path->canvas))
#define kissvg_Path2DXShift(path) (kissvg_Canvas2DXShift(path->canvas))
#define kissvg_Path2DYShift(path) (kissvg_Canvas2DYShift(path->canvas))

extern void kissvg_Path2DSetErrorMessage(kissvg_Path2D *path, char *message);
extern void kissvg_Path2DSetLineWidth(kissvg_Path2D *path, double linewidth);
extern void kissvg_Path2DSetLineColor(kissvg_Path2D *path, kissvg_Color *color);
extern void kissvg_Path2DSetFillColor(kissvg_Path2D *path, kissvg_Color *color);
extern void kissvg_Path2DSetArrowType(kissvg_Path2D *path, int arrow_type);

extern void kissvg_Path2DCreateArrow(kissvg_Path2D *path, double pos,
                                     double arrow_size,
                                     kissvg_Color *arrow_fill_color,
                                     kissvg_Color *arrow_color,
                                     kissvg_Bool reverse_arrow);

extern void kissvg_Path2DAddArrow(kissvg_Path2D *path, double pos,
                                  double arrow_size,
                                  kissvg_Color *arrow_fill_color,
                                  kissvg_Color *arrow_color,
                                  kissvg_Bool reverse_arrow);

extern kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start,
                                          kissvg_Canvas2D *canvas);

extern void kissvg_AppendPath2D(kissvg_Path2D *path, kissvg_TwoVector P);
extern void kissvg_DestroyPath2D(kissvg_Path2D *path);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Axis2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

#define kissvg_Axis2DArrowType(axis) (axis->arrow_type)

extern void kissvg_Axis2DSetTicks(kissvg_Axis2D *axis, kissvg_Bool ticks);
extern void kissvg_Axis2DUseUpTicks(kissvg_Axis2D *axis);
extern void kissvg_Axis2DUseDownTicks(kissvg_Axis2D *axis);

extern void kissvg_Axis2DCreateTicks(kissvg_Axis2D *axis,
                                     kissvg_TwoVector P,
                                     kissvg_TwoVector Q);

extern void kissvg_Axis2DSetTickSize(kissvg_Axis2D *axis, double tick_size);
extern void kissvg_Axis2DSetTickDist(kissvg_Axis2D *axis, double tick_dist);
extern void kissvg_Axis2DSetTickHeight(kissvg_Axis2D *axis, double tick_height);
extern void kissvg_Axis2DSetTickSemiHeight(kissvg_Axis2D *axis,
                                           double tick_semi_height);

extern void kissvg_Axis2DSetAxisStart(kissvg_Axis2D *axis, kissvg_TwoVector P);
extern void kissvg_Axis2DSetAxisFinish(kissvg_Axis2D *axis, kissvg_TwoVector P);
extern void kissvg_Axis2DSetCanvas(kissvg_Axis2D *axis,
                                   kissvg_Canvas2D *canvas);
extern void kissvg_Axis2DSetArrowType(kissvg_Axis2D *axis, int arrow_type);

extern void kissvg_Axis2DSetTickSemiSemiHeight(kissvg_Axis2D *axis,
                                               double tick_semi_semi_height);

extern void kissvg_Axis2DSetTickColor(kissvg_Axis2D *axis, kissvg_Color *color);
extern void kissvg_Axis2DSetLineWidth(kissvg_Axis2D *axis, double linewidth);
extern void kissvg_Axis2DSetLineColor(kissvg_Axis2D *axis, kissvg_Color *color);

extern void kissvg_Axis2DCreateArrow(kissvg_Axis2D *axis, double pos,
                                     double arrow_size,
                                     kissvg_Color *arrow_fill_color,
                                     kissvg_Color *arrow_color,
                                     kissvg_Bool reverse_arrow);

extern void kissvg_Axis2DAddArrow(kissvg_Axis2D *axis, double pos,
                                  double arrow_size,
                                  kissvg_Color *arrow_fill_color,
                                  kissvg_Color *arrow_color,
                                  kissvg_Bool reverse_arrow);

extern kissvg_Axis2D *kissvg_CreateAxis2D(kissvg_TwoVector start,
                                          kissvg_TwoVector finish,
                                          kissvg_Canvas2D *canvas);

extern void kissvg_ResetAxis2D(kissvg_Axis2D* axis,
                               kissvg_TwoVector start,
                               kissvg_TwoVector finish);

extern void kissvg_DestroyAxis2D(kissvg_Axis2D *axis);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Circle Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

#define kissvg_CircleCenter(circle) (circle->center)
#define kissvg_CircleRadius(circle) (circle->radius)

extern void kissvg_CircleSetCanvas(kissvg_Circle *circle,
                                   kissvg_Canvas2D *canvas);

extern void kissvg_CircleSetArrowType(kissvg_Circle *circle, int arrow_type);
extern void kissvg_CircleSetLineWidth(kissvg_Circle *circle, double linewidth);
extern void kissvg_CircleSetLineColor(kissvg_Circle *circle,
                                      kissvg_Color *color);
extern void kissvg_CircleSetFillColor(kissvg_Circle *circle,
                                      kissvg_Color *color);

extern void kissvg_CircleCreateArrow(kissvg_Circle *path, double pos,
                                     double arrow_size,
                                     kissvg_Color *arrow_fill_color,
                                     kissvg_Color *arrow_color,
                                     kissvg_Bool reverse_arrow);

extern void kissvg_CircleAddArrow(kissvg_Circle *path, double pos,
                                  double arrow_size,
                                  kissvg_Color *arrow_fill_color,
                                  kissvg_Color *arrow_color,
                                  kissvg_Bool reverse_arrow);

extern kissvg_Circle *kissvg_CreateCircle(kissvg_TwoVector P, double r,
                                          kissvg_Canvas2D *canvas);
extern void kissvg_DestroyCircle(kissvg_Circle *circle);

extern kissvg_TwoVector *kissvg_CircleCircleIntersection(kissvg_Circle *C1,
                                                         kissvg_Circle *C2);

extern kissvg_Circle **kissvg_ApolloniusProblem(kissvg_Circle *circle1,
                                                kissvg_Circle *circle2,
                                                kissvg_Circle *circle3,
                                                kissvg_Canvas2D *canvas);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                       Begin Drawing Functions                              *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/


extern void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);
extern void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);
extern void kissvg_DrawAxis2D(cairo_t *cr, kissvg_Axis2D *axis);

extern void kissvg_DrawCircle2D(cairo_t *cr, kissvg_Circle *circle);
extern void kissvg_FillDrawCircle2D(cairo_t *cr, kissvg_Circle *circle);

#endif
/*  End of include guard.                                                     */
