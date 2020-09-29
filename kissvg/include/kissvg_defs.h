/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_DEFS_H
#define _KISSVG_DEFS_H

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
 *  (.ps, .svg, .pdf, etc.) and the coordinates we use for computations.      */
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
 *  setting these values so one should never have to do so directly. The      *
 *  Boolean has_transparency is used for determining if alpha composting      *
 *  should be used with the value alpha.                                      */
typedef struct kissvg_Color {
    double dat[3];
    double alpha;
    kissvg_Bool has_transparency;
} kissvg_Color;

/*  Enumerated list of arrow types. Currently only three are provided, which  *
 *  are modeled after the tikz arrows. A no-arrow option is also provided.    */
typedef enum {
    kissvg_NoArrow,
    kissvg_StealthArrow,
    kissvg_TriangularArrow,
    kissvg_LatexArrow
} kissvg_ArrowType;

/*  Struct containing all of the information for arrows. This struct is       *
 *  contained in the Path2D, Circle, and Axis2D structs.                      */
typedef struct kissvg_Arrow {

    /*  Booleans for the direction of the arrow.                              */
    kissvg_Bool reverse_arrow;

    /*  The type of arrow to draw. (Stealth, triangle, LaTeX, or none).       */
    kissvg_ArrowType arrow_type;

    /*  The position of the arrow, which should be number between 0 and 1.    */
    double arrow_pos;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  The color of the interior of the arrow drawn.                         */
    kissvg_Color *fill_color;

    /*  The color of the outline of the arrow.                                */
    kissvg_Color *line_color;

    /*  The radius of the arrow head. The arrow head is defined by three      *
     *  points on a circle about the point corresponding to the arrow_pos.    */
    double arrow_size;

    /*  The width of the boundary of the arrow. This only matters if the fill *
     *  colors is different than the line color.                              */
    double line_width;
} kissvg_Arrow;

/*  This is the primary data type used for drawing 2 dimensional figures. It  *
 *  contains a lot of information, and various functions and macros are       *
 *  provided below for accessing the data and altering it.                    */
typedef struct kissvg_Path2D {

    /*  This pointer contains all of the points of the path.                  */
    kissvg_TwoVector *data;

    /*  The number of points in the data pointer.                             */
    unsigned long N_Pts;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Boolean for determining if the path is meant to be a closed path or   *
     *  an open path. By default it is false.                                 */
    kissvg_Bool is_closed;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false. If this Boolean is set to true, the various  *
     *  drawing routines will automatically set is_closed to true.            */
    kissvg_Bool has_filldraw;

    /*  Boolean for determining if the path has arrows on it.                 */
    kissvg_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    kissvg_Arrow **arrows;

    /*  The number of arrow.                                                  */
    unsigned long N_Arrows;

    /*  The color of the interior of the region enclosed by the path. This is *
     *  only used if the fill_draw Boolean is set.                            */
    kissvg_Color *fill_color;

    /*  The color of the path.                                                */
    kissvg_Color *line_color;

    /*  The width of the path.                                                */
    double line_width;

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
     *  page if you left no room when setting X_MIN, X_MAX, Y_MIN, orY_MAX.   */
    kissvg_TwoVector finish;

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Where the ticks should start. Usually you will be plotting the x and  *
     *  y axes so it is reasonable to set this as an integer pair like (0, 0).*/
    kissvg_TwoVector tick_start;

    /*  Where the tick marks stop.                                            */
    kissvg_TwoVector tick_finish;

    /*  Boolean for determining if the path has arrows on it.                 */
    kissvg_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    kissvg_Arrow **arrows;

    /*  The number of arrow.                                                  */
    long N_Arrows;

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

    /*  The color of the axis. Default is black.                              */
    kissvg_Color *line_color;

    /*  The color of the ticks. Default is black.                             */
    kissvg_Color *tick_color;

    /*  The thickness of the axis. Default is the macro kissvg_DefaultAxes.   */
    double line_width;

    /*  The size of the ticks. Default is zero since ticks are not drawn by   *
     *  default and need to be set by the user.                               */
    double tick_width;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas2D *canvas;
} kissvg_Axis2D;

/*  This is the primary structure for working with and drawing circles. It    *
 *  contains geometric data as well as visual data for how to draw it.        */
typedef struct kissvg_Circle {

    /*  The geometrical data of the circle. We need the center and the radius.*/
    kissvg_TwoVector center;
    double radius;

    kissvg_Bool is_line;
    kissvg_TwoVector P;
    kissvg_TwoVector V;

    /*  The rest are for drawing the circle. If you only need the circle for  *
     *  computations then you need not set any of these. When a circle is     *
     *  created via kissvg_CreateCircle, many reasonable defaults are set so  *
     *  you can still draw without having to explicitly set values.           */

    /*  Boolean for determining if an error occured.                          */
    kissvg_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Boolean for determining if the circle has arrows. By default circles  *
     *  do not have arrows so the arrow_fill_color and arrow_color variables  *
     *  below are not set.                                                    */
    kissvg_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    kissvg_Arrow **arrows;

    /*  The number of arrow.                                                  */
    long N_Arrows;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false.                                              */
    kissvg_Bool has_filldraw;

    /*  The color of the interior of the region enclosed by the path. This is *
     *  only used if the fill_draw Boolean is set.                            */
    kissvg_Color *fill_color;

    /*  The color of the axis. Default is black.                              */
    kissvg_Color *line_color;

    /*  The thickness of the axis. Default is the macro kissvg_DefaultAxes.   */
    double line_width;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas2D *canvas;
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

    /*  Boolean for determining if the line has arrows.                       */
    kissvg_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    kissvg_Arrow **arrows;

    /*  The number of arrow.                                                  */
    long N_Arrows;

    /*  The color of the axis. Default is black.                              */
    kissvg_Color *line_color;

    /*  The thickness of the axis. Default is the macro kissvg_DefaultAxes.   */
    double line_width;

    /*  The canvas of the entire drawing.                                     */
    kissvg_Canvas2D *canvas;
} kissvg_Line2D;

/*  Note, one should not access the data in these structures directly, but    *
 *  rather use the functions defined below, like kissvg_TwoVectorXComponent   *
 *  and so on to access the elements, and kissvg_NewTwoVector to create       *
 *  vectors. It makes the code readable and the attributes of these           *
 *  structures are supposed to be "hidden" from the end-user.                 */

#endif
/*  End of kissvg_defs.h include guard.                                       */
