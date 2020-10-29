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
 *                              kissvg_defs                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Typedef the various structs that are used frequently in KissVG.       *
 *  Data Types:                                                               *
 *      kissvg_TwoVector:                                                     *
 *          Primary tool for two-dimensional/planar geometry and drawing. It  *
 *          is a data type used to represent the ordered pair (x, y).         *
 *      kissvg_TwoByTwoMatrix:                                                *
 *          A data type representing a 2x2 matrix. Used for applying linear   *
 *          transformations to a kissvg_TwoVector.                            *
 *      kissvg_Canvas:                                                        *
 *          A struct which contains all of the necessary data to transform    *
 *          the intrinsic geometry of the output file (.ps, .svg, or whatever *
 *          is being produced) to the coordinate geometry of the user.        *
 *      kissvg_Path2D:                                                        *
 *          A struct containing a pointer to a kissvg_TwoVector, as well as   *
 *          data for the drawing like color, line width, etc.                 *
 *      kissvg_Pen:                                                           *
 *          A struct containing red, green, and blue values (r g, b). The     *
 *          values use real numbers between 0 and 1, and not chars between 0  *
 *          and 255. It contains information about the transparency of the    *
 *          object and it's linewidth.                                        *
 *      kissvg_Palette:                                                       *
 *          A struct with lots of data about how to draw an object. This      *
 *          includes line pens, fill pens, tick marks, labels, arrows, etc.   *
 *      kissvg_ArrowType:                                                     *
 *          An integer corresponding to various arrow styles.                 *
 *      kissvg_Arrow:                                                         *
 *          A struct containing data pertaining to arrows stored in paths.    *
 *          This includes size, color, fill color, and more.                  *
 *      kissvg_Circle:                                                        *
 *          Data structure for circles, including a kissvg_TwoVector for the  *
 *          center and a double for the radius. In addition it contains data  *
 *          for drawing the circle.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       October 3, 2020                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_DEFS_H_
#define _KISSVG_DEFS_H_

/*  Several of the structs have Booleans, which we typedef here.              */
typedef enum {kissvg_False, kissvg_True} kissvg_Bool;

/*  Enumeration for legal file outputs. Currently PostScript (.ps), Scalable  *
 *  Vector Graphics (.svg), and Portable Document Format (.pdf) are allowed.  */
typedef enum {
    kissvg_PS,
    kissvg_SVG,
    kissvg_PDF
} kissvg_FileType;

/*  We'll define a plane point the same way we do a complex value.            */
typedef struct kissvg_TwoVector {
    double dat[2];
} kissvg_TwoVector;

/*  Simple struct for 2x2 matrices. These are primarily used for applying     *
 *  linear transformations to kissvg_TwoVector's.                             */
typedef struct kissvg_TwoByTwoMatrix {
    double dat[2][2];
} kissvg_TwoByTwoMatrix;

/*  This struct is required for most routines and is included as an attribute *
 *  of several data types. It is used to convert between the geometry of the  *
 *  actual output file (.ps, .svg, .pdf, etc.) and the coordinates we use for *
 *  computations.                                                             */
typedef struct kissvg_Canvas kissvg_Canvas;

/*  This function pointer is stored inside a kissvg_Canvas struct. The        *
 *  function takes in the canvas and a double and transforms the user's       *
 *  coordinates to the coordinates of the actual file.                        */
typedef double (*kissvg_CanvasTransform) (kissvg_Canvas *, double);

/*  Actual definition of kissvg_Canvas struct.                                */
struct kissvg_Canvas {
    kissvg_FileType filetype;

    /*  The size of the figure, in inches.                                    */
    double x_inches;
    double y_inches;

    /*  x_scale and y_scale are the scales applied to the user's coordinates  *
     *  so that the image is the correct size in the actual file.             */
    double x_scale;
    double y_scale;

    /*  x_shift and y_shift are used to center the figure. The center is not  *
     *  taken to be (0, 0), but rather the value corresponding to             *
     *  (x_inches, y_inches)/2.                                               */
    double x_shift;
    double y_shift;

    /*  Transform functions are stored inside the canvas for ease of access.  */
    kissvg_CanvasTransform X_Transform;
    kissvg_CanvasTransform Y_Transform;
};

/*  This is the primary structure for using colors in drawings. It is a       *
 *  structure which contains an array of three double corresponding to Red,   *
 *  Green, and Blue (in that order). Functions and macros are providing for   *
 *  setting these values so one should never have to do so directly. The      *
 *  Boolean has_transparency is used for determining if alpha composting      *
 *  should be used with the value alpha.                                      */
typedef struct kissvg_Pen {
    double dat[3];
    double alpha;
    double linewidth;
    kissvg_Bool has_transparency;
} kissvg_Pen;

/*  Struct for adding labels to figures.                                      */
typedef struct kissvg_Label2D {
    char *label_content;
    int font_size;
    int baseline_skip;
    double margins[4];
    kissvg_TwoVector anchor;
    kissvg_TwoVector shift;
    kissvg_Pen *pen;
} kissvg_Label2D;

/*  Enumerated list of arrow types. Currently only three are provided, which  *
 *  are modeled after the tikz arrows. A no-arrow option is also provided. If *
 *  you want to flip the direction, use the Reverse option, i.e. something    *
 *  like kissvg_Stealth_Arrow_Reverse.                                        */
typedef enum {
    kissvg_No_Arrow,
    kissvg_Stealth_Arrow,
    kissvg_Reverse_Stealth_Arrow,
    kissvg_Triangular_Arrow,
    kissvg_Reverse_Triangular_Arrow,
    kissvg_Latex_Arrow,
    kissvg_Reverse_Latex_Arrow
} kissvg_ArrowType;

/*  Struct containing all of the information for arrows.                      */
typedef struct kissvg_Arrow {

    /*  The type of arrow to draw. (Stealth, triangle, LaTeX, or none).       */
    kissvg_ArrowType arrow_type;

    /*  The position of the arrow, which should be number between 0 and 1.    */
    double arrow_pos;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  The color of the interior of the arrow drawn.                         */
    kissvg_Pen *fill_pen;

    /*  The color of the outline of the arrow.                                */
    kissvg_Pen *line_pen;

    /*  The radius of the arrow head. The arrow head is defined by three      *
     *  points on a circle about the point corresponding to the arrow_pos.    */
    double arrow_size;
} kissvg_Arrow;

/*  Struct stored in paths and circles containing all of the info on how to   *
 *  draw the object.                                                          */
typedef struct kissvg_Palette {

    /*  Boolean for determining if there are lables along the path.           */
    kissvg_Bool has_labels;

    /*  Pointer to the labels of the path.                                    */
    kissvg_Label2D **labels;

    /*  The number of labels on the path.                                     */
    unsigned long N_Labels;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false. If this Boolean is set to true, the various  *
     *  drawing routines will automatically set is_closed to true.            */
    kissvg_Bool has_fill_draw;

    /*  Boolean for determining if the path has arrows on it.                 */
    kissvg_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    kissvg_Arrow **arrows;

    /*  The number of arrow.                                                  */
    unsigned long N_Arrows;

    /*  The color of the interior of the region enclosed by the path. This is *
     *  only used if the has_fill_draw Boolean is set.                        */
    kissvg_Pen *fill_pen;

    /*  The color of the path.                                                */
    kissvg_Pen *line_pen;

    /*  Where the ticks should start. This is parameterized by the arc length *
     *  of the object. That is, if you set tick_start = 0 there will be a     *
     *  tick at the very start of the path.                                   */
    double tick_start;

    /*  Where the tick marks stop.                                            */
    double tick_finish;

    /*  Boolean for use of tick marks. Default is False.                      */
    kissvg_Bool has_ticks;

    /*  Boolean for only having ticks "above" the axis. For the x-axis, where *
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
     *  tick_semi_height, and tick_semi_semi_height which plots ticks of      *
     *  different heights on a cycle of four. Any value is allowed, however.  */
    double tick_dx;

    /*  The major height of the ticks. This is the height of every fourth     *
     *  tick mark. That is, when the tick number is divisible by four, this   *
     *  height is used.                                                       */
    double tick_height;

    /*  The tick height for the ticks whose number is even, but not divisible *
     *  by four.                                                              */
    double tick_semi_height;

    /*  The tick height for the odd-numbered ticks.                           */
    double tick_semi_semi_height;

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

    /*  The color of the ticks. Default is black.                             */
    kissvg_Pen *tick_pen;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas *canvas;
} kissvg_Palette;

/*  This is the primary data type used for drawing 2 dimensional figures.     */
typedef struct kissvg_Path2D {

    /*  This pointer contains all of the points of the path.                  */
    kissvg_TwoVector *data;

    /*  The number of points in the data pointer.                             */
    unsigned long N_Pts;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Boolean for determining if the object is meant to be closed or not.   *
     *  If you wish to use fill draw with the object, this must be true.      */
    kissvg_Bool is_closed;

    /*  Data for how to draw the path and the geometry of the page.           */
    kissvg_Palette *palette;
} kissvg_Path2D;

/*  This is the primary structure for working with and drawing circles. It    *
 *  contains geometric data as well as visual data for how to draw it.        */
typedef struct kissvg_Circle {

    /*  The geometrical data of the circle. We need the center and the radius.*/
    kissvg_TwoVector center;
    double radius;

    /*  Several routines allow for the possibility of a circle degenerating   *
     *  to a line, which is a circle with center "at infinity." In these      *
     *  scenarios the functions set the circle to be a line defined by a      *
     *  point P which lies on it, and its tangent vector V. The is_line       *
     *  is for determining if a circle is actually a line.                    */
    kissvg_Bool is_line;
    kissvg_TwoVector P;
    kissvg_TwoVector V;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Data for how to draw the path and the geometry of the page.           */
    kissvg_Palette *palette;
} kissvg_Circle;

/*  A data type for conviently dealing with lines.                            */
typedef struct kissvg_Line2D {

    /*  A point that lies on the line.                                        */
    kissvg_TwoVector P;

    /*  The tangent/velocity vector of the line. That is, the direction the   *
     *  line points in.                                                       */
    kissvg_TwoVector V;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Data for how to draw the path and the geometry of the page.           */
    kissvg_Palette *palette;
} kissvg_Line2D;

/*  Note, one should not access the data in these structures directly, but    *
 *  rather use the functions and macros defined in kissvg.h, like             *
 *  kissvg_TwoVector_X_Component and so on to access the elements, and        *
 *  kissvg_New_TwoVector to create vectors. It makes the code readable and    *
 *  the attributes of these structures are supposed to be "hidden" from the   *
 *  end-user.                                                                 */

/*  The following macros are universal all of the data types where the        *
 *  attribute applies. For example, Path2D, Circle, and Line2D all have a     *
 *  kissvg_Palette Boolean which may be set via kissvg_Set_Palette.           */
#define kissvg_Has_Error(obj)            ((obj)->error_occured)
#define kissvg_Get_Palette(obj)          ((obj)->palette)
#define kissvg_Set_Palette(obj, palette) ((obj)->palette = palette)
#define kissvg_Set_Error(obj, error)     ((obj)->error_occured = error)
#define kissvg_Error_Message(obj)        ((obj)->error_message)

#endif
/*  End of kissvg_defs.h include guard.                                       */
