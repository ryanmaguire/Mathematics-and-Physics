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
 *                                  kissvg                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file provides many of the functions described in kissvg.h. See   *
 *      that header file for more details.                                    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       October 2, 2020                                               *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>
#include <cairo/src/cairo.h>
#include <cairo/src/cairo-pdf.h>
#include <cairo/src/cairo-svg.h>
#include <cairo/src/cairo-ps.h>

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                   Begin kissvg_Canvas2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Function for transforming user coordinates to the coordinate of the file. *
 *  That is, the user coordinates are of the form (x, y), a point in the      *
 *  Cartesian plane, whereas the file coordinates depend on the .svg/.ps/.pdf *
 *  file. This function transforms the x coordinate.                          */
static double __kissvg_CanvasTransformX(kissvg_Canvas2D *canvas, double x)
{
    return kissvg_Canvas2DXShift(canvas) + kissvg_Canvas2DXScale(canvas) * x;
}

/*  Same as __kissvg_CanvasTransformX but for the y coordinate.               */
static double __kissvg_CanvasTransformY(kissvg_Canvas2D *canvas, double y)
{
    return kissvg_Canvas2DYShift(canvas) - kissvg_Canvas2DYScale(canvas) * y;
}

/*  Create a canvas for a two dimensional drawing. This should be done once,  *
 *  and only once, for every two dimensional drawing you make. It contains    *
 *  the geometry of the file, the geometry of the user, and transformations   *
 *  to swap between the two.                                                  */
kissvg_Canvas2D *kissvg_CreateCanvas2D(double x_inches, double y_inches,
                                       double x_min, double x_max,
                                       double y_min, double y_max,
                                       kissvg_Bool one_to_one_apect_ratio,
                                       kissvg_FileType filetype)
{
    /*  Declare necessary variables.                                          */
    kissvg_Canvas2D *canvas;
    double xshift, yshift, xscale, yscale;

    /*  Allocate memory for the canvas.                                       */
    canvas = malloc(sizeof(*canvas));

    /*  Check to make sure malloc didn't fail. Abort if it did.               */
    if (canvas == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateCanvas2D\n\n"
             "Malloc failed to create canvas and returned NULL. Aborting.\n\n");
        exit(0);
    }

    /*  Compute the scales to go from Cartesian geometry to file coordinates. */
    xscale = x_inches/(x_max - x_min);
    yscale = y_inches/(y_max - y_min);

    /*  If 1-1 aspect ratio has been requested, choose the smaller of x_scale *
     *  and y_scale and set both variables to this value. This ensures the    *
     *  drawing does not fall outside of the bounds.                          */
    if (one_to_one_apect_ratio)
    {
        xscale = (xscale < yscale ? xscale : yscale);
        yscale = xscale;
    }

    /*  Set the shifts to center the figure in the file.                      */
    xshift = 0.5*x_inches - 0.5*(x_min + x_max)*xscale;
    yshift = 0.5*y_inches - 0.5*(y_min + y_max)*yscale;

    /*  Set the canvas attributes to the computed values.                     */
    canvas->x_scale = xscale;
    canvas->y_scale = yscale;
    canvas->x_shift = xshift;
    canvas->y_shift = yshift;

    /*  Set the TransformX and TransformY functions to point to the addresses *
     *  associated to the __kissvg_CanvasTransformX and                       *
     *  __kissvg_CanvasTransformY functions, respectively.                    */
    canvas->TransformX = &__kissvg_CanvasTransformX;
    canvas->TransformY = &__kissvg_CanvasTransformY;

    /*  Set the filetype attribute to the requested type and return.          */
    canvas->filetype = filetype;
    return canvas;
}

/*  Main function for destroying a two dimensional canvas. This should always *
 *  be called at the end of a two dimensional drawing to avoid memory leaks.  */
void kissvg_DestroyCanvas2D(kissvg_Canvas2D **canvas_pointer)
{
    /*  Check that the input pointer was not NULL.                            */
    if (canvas_pointer == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_DestroyCanvas2D\n\n"
             "Input canvas_pointer is NULL. Aborting.");
        exit(0);
    }

    /*  The only thing malloc'd by kissvg_CreateCanvas2D is the canvas itself *
     *  so we only need to free this. If you already destroyed this, the      *
     *  canvas variable is set to NULL after being free'd to prevent you from *
     *  free'ing it twice. However, it's best to just keep track of what      *
     *  you've created and destroyed.                                         */
    if (*canvas_pointer == NULL)
    {
        puts("Warning: KissVG\n"
             "\tFunction: kissvg_DestroyCanvas2D\n\n"
             "You are calling kissvg_DestroyCanvas2D on a canvas that is\n"
             "NULL. You likely already destroyed this canvas. Returning.\n");
    }
    else
    {
        /*  If canvas is not NULL, we can safely free it.                     */
        free(*canvas_pointer);

        /*  After freeing, set canvas to NULL to prevent user's from trying   *
         *  to free this twice.                                               */
        *canvas_pointer = NULL;
    }

    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Color Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Function for creating a color in RGB (red-green-blue) format with real    *
 *  values between 0 and 1. If the transparent Boolean is set to true, one    *
 *  may use the alpha value to set the opacity of the color.                  */
kissvg_Color *kissvg_CreateColor(double red, double green, double blue,
                                 kissvg_Bool transparent, double alpha)
{
    /*  Declare the necessary variable.                                       */
    kissvg_Color *color;

    /*  Allocate memory for the color.                                        */
    color = malloc(sizeof(*color));

    /*  Check to make sure malloc didn't fail. Abort if it did.               */
    if (color == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateColor\n\n"
             "Malloc failed to create color and returned NULL. Aborting.\n\n");
        exit(0);
    }

    /*  Set the attributes for the color and return.                          */
    color->dat[0] = red;
    color->dat[1] = green;
    color->dat[2] = blue;
    color->has_transparency = transparent;
    color->alpha = alpha;

    return color;
}

/*  Function for destroying new colors. Note you should NOT call this         *
 *  function on predefined colors like kissvg_Black since these are not       *
 *  created using malloc, so free'ing them causes errors.                     */
void kissvg_DestroyColor(kissvg_Color **color_pointer)
{
    /*  Check that the input pointer was not NULL.                            */
    if (color_pointer == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_DestroyColor\n\n"
             "Input color_pointer is NULL. Aborting.");
        exit(0);
    }

    /*  The only thing malloc'd by kissvg_CreateColor is the color itself     *
     *  so we only need to free this. If you already destroyed this, the      *
     *  color variable is set to NULL after being free'd to prevent you from  *
     *  free'ing it twice. However, it's best to just keep track of what      *
     *  you've created and destroyed.                                         */
    if (*color_pointer == NULL)
    {
        puts("Warning: KissVG\n"
             "\tFunction: kissvg_DestroyColor\n\n"
             "You are calling kissvg_DestroyColor on a color that is\n"
             "NULL. You likely already destroyed this color. Returning.\n");
    }
    else
    {
        /*  If color is not NULL, we can safely free it.                      */
        free(*color_pointer);

        /*  After freeing, set color to NULL to prevent user's from trying    *
         *  to free this twice.                                               */
        *color_pointer = NULL;
    }

    return;
}

/*  The following are pre-defined colors for ease of use.                     */
static kissvg_Color __kissvg_Blue      = {{0.00, 0.20, 1.00}, 0, kissvg_False};
static kissvg_Color __kissvg_Green     = {{0.00, 1.00, 0.10}, 0, kissvg_False};
static kissvg_Color __kissvg_Red       = {{1.00, 0.10, 0.10}, 0, kissvg_False};
static kissvg_Color __kissvg_Black     = {{0.00, 0.00, 0.00}, 0, kissvg_False};
static kissvg_Color __kissvg_White     = {{1.00, 1.00, 1.00}, 0, kissvg_False};
static kissvg_Color __kissvg_DarkGray  = {{0.30, 0.30, 0.30}, kissvg_False, 0};
static kissvg_Color __kissvg_Gray      = {{0.60, 0.60, 0.60}, kissvg_False, 0};
static kissvg_Color __kissvg_LightGray = {{0.80, 0.80, 0.80}, kissvg_False, 0};
static kissvg_Color __kissvg_Aqua      = {{0.10, 1.00, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Purple    = {{0.70, 0.00, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Violet    = {{0.50, 0.00, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Pink      = {{1.00, 0.40, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Yellow    = {{1.00, 1.00, 0.20}, kissvg_False, 0};
static kissvg_Color __kissvg_Crimson   = {{0.80, 0.00, 0.13}, kissvg_False, 0};
static kissvg_Color __kissvg_DarkGreen = {{0.25, 0.50, 0.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Orange    = {{1.00, 0.40, 0.10}, kissvg_False, 0};
static kissvg_Color __kissvg_LightBlue = {{0.60, 0.80, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Teal      = {{0.00, 0.50, 0.50}, kissvg_False, 0};
static kissvg_Color __kissvg_DarkBlue  = {{0.00, 0.00, 0.60}, kissvg_False, 0};
static kissvg_Color __kissvg_Lavender  = {{0.80, 0.83, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Magenta   = {{1.00, 0.11, 0.81}, kissvg_False, 0};
static kissvg_Color __kissvg_DeepPink  = {{1.00, 0.08, 0.58}, kissvg_False, 0};
static kissvg_Color __kissvg_Marine    = {{0.30, 0.30, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Lime      = {{0.75, 0.90, 0.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Carrot    = {{1.00, 0.65, 0.30}, kissvg_False, 0};
static kissvg_Color __kissvg_Brown     = {{0.30, 0.15, 0.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Azure     = {{0.00, 0.50, 1.00}, kissvg_False, 0};
static kissvg_Color __kissvg_Silver    = {{0.75, 0.75, 0.75}, kissvg_False, 0};
static kissvg_Color __kissvg_Sand      = {{0.93, 0.84, 0.25}, kissvg_False, 0};

/*  Set the kissvg_ColorName pointers to point to __kissvg_ColorName.         */
kissvg_Color *kissvg_Blue      = &__kissvg_Blue;
kissvg_Color *kissvg_Green     = &__kissvg_Green;
kissvg_Color *kissvg_Red       = &__kissvg_Red;
kissvg_Color *kissvg_Black     = &__kissvg_Black;
kissvg_Color *kissvg_White     = &__kissvg_White;
kissvg_Color *kissvg_DarkGray  = &__kissvg_DarkGray;
kissvg_Color *kissvg_Gray      = &__kissvg_Gray;
kissvg_Color *kissvg_LightGray = &__kissvg_LightGray;
kissvg_Color *kissvg_Aqua      = &__kissvg_Aqua;
kissvg_Color *kissvg_Purple    = &__kissvg_Purple;
kissvg_Color *kissvg_Violet    = &__kissvg_Violet;
kissvg_Color *kissvg_Pink      = &__kissvg_Pink;
kissvg_Color *kissvg_Yellow    = &__kissvg_Yellow;
kissvg_Color *kissvg_Crimson   = &__kissvg_Crimson;
kissvg_Color *kissvg_DarkGreen = &__kissvg_DarkGreen;
kissvg_Color *kissvg_Orange    = &__kissvg_Orange;
kissvg_Color *kissvg_LightBlue = &__kissvg_LightBlue;
kissvg_Color *kissvg_Teal      = &__kissvg_Teal;
kissvg_Color *kissvg_DarkBlue  = &__kissvg_DarkBlue;
kissvg_Color *kissvg_Lavender  = &__kissvg_Lavender;
kissvg_Color *kissvg_Magenta   = &__kissvg_Magenta;
kissvg_Color *kissvg_DeepPink  = &__kissvg_DeepPink;
kissvg_Color *kissvg_Marine    = &__kissvg_Marine;
kissvg_Color *kissvg_Lime      = &__kissvg_Lime;
kissvg_Color *kissvg_Carrot    = &__kissvg_Carrot;
kissvg_Color *kissvg_Brown     = &__kissvg_Brown;
kissvg_Color *kissvg_Azure     = &__kissvg_Azure;
kissvg_Color *kissvg_Silver    = &__kissvg_Silver;
kissvg_Color *kissvg_Sand      = &__kissvg_Sand;

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Arrow Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

static void __check_arrow_error(kissvg_Arrow *arrow, char *FuncName)
{
    /*  If the input arrow is NULL, it was not set via kissvg_CreateArrow     *
     *  or kissvg_DestroyArrow was called prematurely. In either case, print  *
     *  an error message and abort the computation.                           */
    if (arrow == NULL)
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input arrow is NULL. Aborting.", FuncName);
        exit(0);
    }

    /*  If the input arrow has an error set, abort the computation.           */
    if (kissvg_HasError(arrow))
    {
        printf("Error Encountered: KissVG\n"
               "\tFunction: %s\n\n"
               "Input arrow has error_encoutered variable set to true.\n"
               "Printing Error Message:\n\n", FuncName);

        /*  If the error message is NULL, then it wasn't set. Print this.     */
        if (kissvg_ErrorMessage(arrow) == NULL)
            puts("Input circle did not have an error message set.\n\n");

        /*  Otherwise, simply print the message.                              */
        else
            puts(kissvg_ErrorMessage(arrow));

        /*  Abort the computation.                                            */
        exit(0);
    }

    /*  If no error occured, return to caller.                                */
    return;
}

/*  Function for reversing the direction of an arrow head.                    */
void kissvg_ArrowSetReverse(kissvg_Arrow *arrow, kissvg_Bool reverse)
{
    /*  Check that the input arrow doesn't have errors.                       */
    __check_arrow_error(arrow, "kissvg_ArrowSetReverse");

    /*  Set reverse arrow to the requested Boolean and return.                */
    arrow->reverse_arrow = reverse;
    return;
}

/*  Function for setting the arrow type of a given arrow.                     */
void kissvg_ArrowSetType(kissvg_Arrow *arrow, kissvg_ArrowType type)
{
    /*  Check that the input arrow doesn't have any errors.                   */
    __check_arrow_error(arrow, "kissvg_ArrowSetType");

    /*  Set the arrow_type to the requested value and return.                 */
    arrow->arrow_type = type;
    return;
}

/*  Function for setting the position of a given arrow.                       */
void kissvg_ArrowSetPos(kissvg_Arrow *arrow, double pos)
{
    /*  Check that the input arrow doesn't have errors.                       */
    __check_arrow_error(arrow, "kissvg_ArrowSetPos");

    /*  Set arrow_pos to the request position. Note that no error checks are  *
     *  performed on this value, though it should lie between 0 and 1,        *
     *  inclusively. In the drawing routines, values below zero are set to    *
     *  zero and values above one are set to one.                             */
    arrow->arrow_pos = pos;
    return;
}

/*  Function for setting the size of the arrow head of a given arrow. Arrow   *
 *  heads are defined by three points on a circle and this value is the       *
 *  circle's radius.                                                          */
void kissvg_ArrowSetSize(kissvg_Arrow *arrow, double size)
{
    /*  Check that the input arrow doesn't have errors.                       */
    __check_arrow_error(arrow, "kissvg_ArrowSetSize");

    /*  Set the arrow size to the requested value and return.                 */
    arrow->arrow_size = size;
    return;
}

/*  Function for creating arrows. This is used by various path, axis, and     *
 *  circle functions for storing arrows in those data types.                  */
kissvg_Arrow *kissvg_CreateArrow(double pos,
                                 double arrow_size,
                                 kissvg_Color *arrow_fill_color,
                                 kissvg_Color *arrow_color,
                                 kissvg_Bool reverse_arrow,
                                 kissvg_ArrowType type,
                                 double arrow_line_width)
{
    /*  Declare necessary variables.                                          */
    kissvg_Arrow *arrow;
    char *mes;
    long mes_len;

    /*  Allocate memory for the arrow.                                        */
    arrow = malloc(sizeof(*arrow));

    /*  Check to see if malloc failed.                                        */
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateArrow\n\n"
             "Malloc failed to create arrow and returned NULL. Aborting.\n\n");
        exit(0);
    }

    /*  If the size value is negative, set this as an error message.          */
    if (arrow_size < 0.0)
    {
        kissvg_SetError(arrow, kissvg_True);
        mes = "Error Encountered: KissVG\n"
              "\tFunction: kissvg_CreateArrow\n\n"
              "Input size is negative. Values must be non-negative.\n\n";

        /*  Get the length of the above string. Add one to it since we need   *
         *  to leave room for the null terminator "\0".                       */
        mes_len = strlen(mes) + 1;

        /*  Allocate memory for the error message and copy mes to this.       */
        arrow->error_message = malloc(sizeof(*arrow->error_message) * mes_len);
        strcpy(mes, arrow->error_message);
    }

    /*  If arrow_size is non-negative, set error_occured to false.            */
    else
        kissvg_SetError(arrow, kissvg_False);

    kissvg_ArrowSetPos(arrow, pos);
    kissvg_ArrowSetSize(arrow, arrow_size);
    kissvg_ArrowSetReverse(arrow, reverse_arrow);
    kissvg_ArrowSetType(arrow, type);
    kissvg_SetFillColor(arrow, arrow_fill_color);
    kissvg_SetLineColor(arrow, arrow_color);
    kissvg_SetLineWidth(arrow, arrow_line_width);

    return arrow;
}

void kissvg_DestroyArrow(kissvg_Arrow *arrow)
{
    char *err_mes;

    /*  If the arrow has an error message attached to it, free this.          */
    if (kissvg_HasError(arrow))
    {
        /*  Extract the error message from the arrow and set this as err_mes. */
        err_mes = kissvg_ErrorMessage(arrow);

        /*  Check that the pointer isn't NULL before free'ing.                */
        if (err_mes != NULL)
            free(err_mes);
    }

    /*  If you already destroyed this, the arrow variable is set to NULL      *
     *  after being free'd to prevent you from free'ing it twice. However,    *
     *  it's best to just keep track of what you've created and destroyed.    */
    if (arrow == NULL)
    {
        puts("Warning: KissVG\n"
             "\tFunction: kissvg_DestroyCanvas2D\n\n"
             "You are calling kissvg_DestroyCanvas2D on a canvas that is\n"
             "NULL. You likely already destroyed this canvas. Returning.");
    }

    /*  Otherwise, the only thing left to free is the arrow itself.           */
    else
    {
        /*  If canvas is not NULL, we can safely free it.                     */
        free(arrow);

        /*  After freeing, set canvas to NULL to prevent user's from trying   *
         *  to free this twice.                                               */
        arrow = NULL;
    }

    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Path2D Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

static kissvg_TwoVector __GetPos(kissvg_Path2D *path, double pos)
{
    double norm;
    double path_length;
    double *path_norms;
    double current_length, pos_length;
    long n, N_Pts, current_pos;

    kissvg_TwoVector P0, P1, Q, out;
    kissvg_TwoVector *data;

    data = kissvg_Path2DData(path);
    N_Pts = kissvg_Path2DNumberOfPoints(path);
    path_norms = malloc(sizeof(*path_norms) * (N_Pts-1));

    P0 = kissvg_Path2DData(path)[0];
    P1 = kissvg_Path2DData(path)[1];
    Q = kissvg_TwoVectorSubtract(P1, P0);

    norm = kissvg_EuclideanNorm2D(Q);
    path_length = norm;
    path_norms[0] = norm;

    for (n=1; n<N_Pts-1; ++n)
    {
        P0 = kissvg_Path2DData(path)[n];
        P1 = kissvg_Path2DData(path)[n+1];
        Q = kissvg_TwoVectorSubtract(P1, P0);

        norm = kissvg_EuclideanNorm2D(Q);

        path_length += norm;
        path_norms[n] = path_length;
    }

    if (pos < 0.0)
        pos = 0.0;
    else if (pos > 1.0)
        pos = 1.0;

    if ((data == NULL) || (N_Pts == 0))
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: __GetPos\n\n"
             "Input path has NULL data. Aborting.");
        exit(0);
    }

    if (pos == 0.0)
        out = data[0];
    else if (pos == 1.0)
        out = data[N_Pts-1];
    else
    {
        current_pos = 0;
        current_length = path_norms[0];
        pos_length = pos * path_length;

        for (n=0; n<N_Pts-1; ++n)
        {
            if (pos_length < current_length)
                break;
            current_pos += 1;
            current_length = path_norms[current_pos];
        }

        P0 = kissvg_Path2DData(path)[current_pos];
        P1 = kissvg_Path2DData(path)[current_pos+1];
        Q = kissvg_TwoVectorSubtract(P1, P0);
        norm = kissvg_EuclideanNorm2D(Q);

        if (norm == 0.0)
            out = P0;
        else
        {
            Q = kissvg_TwoVectorScale(1.0/norm, Q);
            norm = pos_length-path_norms[current_pos-1];
            Q = kissvg_TwoVectorScale(norm, Q);
            out  = kissvg_TwoVectorAdd(P0, Q);
        }
    }
    free(path_norms);
    return out;
}

void kissvg_Path2DCreateArrow(kissvg_Path2D *path, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    kissvg_SetHasArrows(path, kissvg_True);
    path->N_Arrows = 1;
    path->arrows = malloc(sizeof(*path->arrows));

    path->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                         arrow_color, reverse_arrow, type,
                                         arrow_line_width);
    return;
}

void kissvg_Path2DAddArrow(kissvg_Path2D *path, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    path->N_Arrows += 1;
    path->arrows = realloc(path->arrows, sizeof(*path->arrows)*path->N_Arrows);

    path->arrows[path->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                        arrow_fill_color,
                                                        arrow_color,
                                                        reverse_arrow, type,
                                                        arrow_line_width);

    return;
}

kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Path2D *path;

    path = malloc(sizeof(*path));

    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreatePath2D\n\n"
             "Malloc failed and returned NULL for path.");
        exit(0);
    }

    path->data = malloc(sizeof(*path->data));

    if (path->data == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreatePath2D\n\n"
             "Malloc failed and returned NULL for path->data.");
        exit(0);
    }

    path->data[0] = start;
    path->N_Pts = 1;

    kissvg_SetLineColor(path, kissvg_Black);
    kissvg_SetFillColor(path, kissvg_Black);
    kissvg_SetLineWidth(path, kissvg_DefaultPen);
    kissvg_SetClosedPath(path, kissvg_False);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_SetFillDraw(path, kissvg_False);
    kissvg_SetError(path, kissvg_False);
    kissvg_SetCanvas(path, canvas);

    return path;
}

void kissvg_AppendPath2D(kissvg_Path2D *path, kissvg_TwoVector P)
{
    long new_path_size;

    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_AppendPath2D\n\n"
             "Input path is NULL.");
        exit(0);
    }

    new_path_size = kissvg_Path2DNumberOfPoints(path) + 1;
    path->data = realloc(path->data, sizeof(*path->data) * new_path_size);

    if (path->data == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_AppendPath2D\n\n"
             "Realloc failed and returned NULL.");
        exit(0);
    }

    path->data[new_path_size-1] = P;
    path->N_Pts = new_path_size;

    return;
}

void kissvg_DestroyPath2D(kissvg_Path2D *path)
{
    long n, N_Arrows;
    kissvg_Arrow *current_arrow;
    free(path->data);

    N_Arrows = kissvg_NumberOfArrows(path);

    if (kissvg_HasArrows(path))
    {
        for (n=0; n<N_Arrows; ++n)
        {
            current_arrow = kissvg_nthArrow(path, n);
            kissvg_DestroyArrow(current_arrow);
        }
    }

    free(path);
    return;
}

void kissvg_Path2DCreateLabel(kissvg_Path2D *path, char *label_content,
                              double pos, int font_size,
                              int baseline_skip, double margins[4],
                              kissvg_TwoVector shift,
                              kissvg_Color *line_color)
{
    kissvg_Canvas2D *canvas;
    kissvg_Label2D *label;
    kissvg_TwoVector anchor;

    canvas = kissvg_GetCanvas(path);
    kissvg_SetHasLabels(path, kissvg_True);
    path->N_Labels = 1;
    path->labels = malloc(sizeof(*path->labels));
    label = path->labels[0];
    anchor = __GetPos(path, pos);
    label = kissvg_CreateLabel2D(label_content, anchor, canvas);

    kissvg_Label2DSetShift(label, shift);
    kissvg_Label2DSetMargins(label, margins);
    kissvg_Label2DSetFontSize(label, font_size);
    kissvg_Label2DSetBaselineSkip(label, baseline_skip);
    kissvg_SetCanvas(label, canvas);
    kissvg_SetLineColor(label, line_color);
    return;
}

void kissvg_Path2DAddLabel(kissvg_Path2D *path, char *label_content,
                           double pos, int font_size, int baseline_skip,
                           double margins[4], kissvg_TwoVector shift,
                           kissvg_Color *line_color)
{

    kissvg_Canvas2D *canvas;
    kissvg_Label2D *label;
    kissvg_TwoVector anchor;

    canvas = kissvg_GetCanvas(path);

    path->N_Labels += 1;
    path->labels = realloc(path->labels, sizeof(*path->labels)*path->N_Labels);

    label = path->labels[path->N_Labels-1];
    anchor = __GetPos(path, pos);
    label = kissvg_CreateLabel2D(label_content, anchor, canvas);

    kissvg_Label2DSetShift(label, shift);
    kissvg_Label2DSetMargins(label, margins);
    kissvg_Label2DSetFontSize(label, font_size);
    kissvg_Label2DSetBaselineSkip(label, baseline_skip);
    kissvg_SetCanvas(label, canvas);
    kissvg_SetLineColor(label, line_color);
    return;
}

void kissvg_Path2DCreateEasyLabel(kissvg_Path2D *path,
                                  char *label_content,
                                  double pos, int font_size,
                                  kissvg_TwoVector shift)
{
    double margins[4];

    margins[0] = kissvg_DefaultLabelMargin;
    margins[1] = kissvg_DefaultLabelMargin;
    margins[2] = kissvg_DefaultLabelMargin;
    margins[3] = kissvg_DefaultLabelMargin;

    kissvg_Path2DCreateLabel(path, label_content, pos, font_size,
                             kissvg_DefaultLabelBaselineSkip,
                             margins, shift, kissvg_Black);
    return;
}

extern void kissvg_Path2DAddEasyLabel(kissvg_Path2D *path,
                                      char *label_content,
                                      double pos, int font_size,
                                      kissvg_TwoVector shift)
{
    double margins[4];

    margins[0] = kissvg_DefaultLabelMargin;
    margins[1] = kissvg_DefaultLabelMargin;
    margins[2] = kissvg_DefaultLabelMargin;
    margins[3] = kissvg_DefaultLabelMargin;

    kissvg_Path2DAddLabel(path, label_content, pos, font_size,
                          kissvg_DefaultLabelBaselineSkip,
                          margins, shift, kissvg_Black);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Axis2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

void kissvg_Axis2DCreateTicks(kissvg_Axis2D *axis,
                              kissvg_TwoVector P,
                              kissvg_TwoVector Q)
{
    kissvg_Axis2DUseTicks(axis, kissvg_True);
    axis->tick_start = P;
    axis->tick_finish = Q;
    return;
}

void kissvg_Axis2DSetTickWidth(kissvg_Axis2D *axis, double tick_width)
{
    axis->tick_width = tick_width;
    return;
}

void kissvg_Axis2DSetTickDistance(kissvg_Axis2D *axis, double tick_dist)
{
    axis->tick_dx = tick_dist;
    return;
}

void kissvg_Axis2DSetTickColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->tick_color = color;
    return;
}

void kissvg_Axis2DSetTickHeight(kissvg_Axis2D *axis, double tick_height)
{
    axis->tick_height = tick_height;
}

void kissvg_Axis2DSetTickSemiHeight(kissvg_Axis2D *axis,
                                    double tick_semi_height)
{
    axis->tick_semi_height = tick_semi_height;
    return;
}

void kissvg_Axis2DSetTickSemiSemiHeight(kissvg_Axis2D *axis,
                                        double tick_semi_semi_height)
{
    axis->tick_semi_semi_height = tick_semi_semi_height;
    return;
}

void kissvg_Axis2DSetAxisStart(kissvg_Axis2D *axis, kissvg_TwoVector P)
{
    axis->start = P;
    return;
}

void kissvg_Axis2DSetAxisFinish(kissvg_Axis2D *axis, kissvg_TwoVector P)
{
    axis->finish = P;
    return;
}

void kissvg_Axis2DUseTicks(kissvg_Axis2D *axis, kissvg_Bool ticks)
{
    axis->has_ticks = ticks;
    return;
}

void kissvg_Axis2DUseUpTicks(kissvg_Axis2D *axis)
{
    axis->has_ticks = kissvg_True;
    axis->up_ticks = kissvg_True;
    axis->down_ticks = kissvg_False;
    return;
}

void kissvg_Axis2DUseDownTicks(kissvg_Axis2D *axis)
{
    axis->has_ticks = kissvg_True;
    axis->down_ticks = kissvg_True;
    axis->up_ticks = kissvg_False;
    return;
}

void kissvg_Axis2DCreateArrow(kissvg_Axis2D *axis, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    kissvg_SetHasArrows(axis, kissvg_True);
    axis->N_Arrows = 1;
    axis->arrows = malloc(sizeof(*axis->arrows));

    axis->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                         arrow_color, reverse_arrow, type,
                                         arrow_line_width);
    return;
}

void kissvg_Axis2DAddArrow(kissvg_Axis2D *axis, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    axis->N_Arrows += 1;
    axis->arrows = realloc(axis->arrows, sizeof(*axis->arrows)*axis->N_Arrows);

    axis->arrows[axis->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                        arrow_fill_color,
                                                        arrow_color,
                                                        reverse_arrow, type,
                                                        arrow_line_width);
    return;
}

kissvg_Axis2D *kissvg_CreateAxis2D(kissvg_TwoVector start,
                                   kissvg_TwoVector finish,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Axis2D *axis;

    axis = malloc(sizeof(*axis));

    if (axis == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateAxis2D\n\n"
            "Malloc failed to create axis and return NULL. Aborting."
        );
        exit(0);
    }

    kissvg_SetLineColor(axis, kissvg_Black);
    kissvg_SetLineWidth(axis, kissvg_DefaultAxes);
    kissvg_SetCanvas(axis, canvas);

    kissvg_Axis2DSetTickColor(axis, kissvg_Black);
    kissvg_Axis2DSetTickWidth(axis, kissvg_DefaultTickWidth);
    kissvg_Axis2DSetTickDistance(axis, kissvg_DefaultTickDist);
    kissvg_Axis2DSetTickHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetAxisStart(axis, start);
    kissvg_Axis2DSetAxisFinish(axis, finish);
    kissvg_Axis2DUseTicks(axis, kissvg_False);

    kissvg_Axis2DCreateArrow(axis, 1.0, kissvg_DefaultArrowSize,
                             kissvg_Black, kissvg_Black, kissvg_False,
                             kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    axis->up_ticks = kissvg_False;
    axis->down_ticks = kissvg_False;

    return axis;
}

void kissvg_Axis2DChangeEndArrow(kissvg_Axis2D *axis, double pos,
                                 double arrow_size,
                                 kissvg_Color *arrow_fill_color,
                                 kissvg_Color *arrow_color,
                                 kissvg_Bool reverse_arrow,
                                 kissvg_ArrowType type,
                                 double arrow_line_width)
{
    kissvg_Arrow *arrow;

    if (axis == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_Axis2DChangeEndArrow\n\n"
            "Input axis is NULL. Aborting."
        );
        exit(0);
    }

    arrow = kissvg_nthArrow(axis, 0);
    kissvg_DestroyArrow(arrow);

    arrow = kissvg_CreateArrow(pos, arrow_size,
                               arrow_fill_color, arrow_color, reverse_arrow,
                               type, arrow_line_width);

    axis->arrows[0] = arrow;
    return;
}

void kissvg_ResetAxis2D(kissvg_Axis2D* axis,
                        kissvg_TwoVector start,
                        kissvg_TwoVector finish)
{
    axis->start = start;
    axis->finish = finish;
    return;
}

void kissvg_DestroyAxis2D(kissvg_Axis2D *axis)
{
    long n, N_Arrows;
    kissvg_Arrow *current_arrow;

    N_Arrows = kissvg_NumberOfArrows(axis);

    if (kissvg_HasArrows(axis))
    {
        for (n=0; n<N_Arrows; ++n)
        {
            current_arrow = kissvg_nthArrow(axis, n);
            kissvg_DestroyArrow(current_arrow);
        }
    }

    free(axis);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Circle Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

void kissvg_CircleCreateArrow(kissvg_Circle *circle, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    kissvg_SetHasArrows(circle, kissvg_True);
    circle->N_Arrows = 1;
    circle->arrows = malloc(sizeof(*circle->arrows));

    circle->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                           arrow_color, reverse_arrow, type,
                                           arrow_line_width);
    return;
}

void kissvg_CircleAddArrow(kissvg_Circle *circle, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    circle->N_Arrows += 1;
    circle->arrows = realloc(
        circle->arrows, sizeof(*circle->arrows)*circle->N_Arrows
    );

    circle->arrows[circle->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                            arrow_fill_color,
                                                            arrow_color,
                                                            reverse_arrow,
                                                            type,
                                                            arrow_line_width);
    return;
}

kissvg_Circle *kissvg_CreateCircle(kissvg_TwoVector P, double r,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Circle *circle;

    circle = malloc(sizeof(*circle));

    if (circle == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateCircle\n\n"
             "Malloc failed to create circle and return NULL. Aborting.");
        exit(0);
    }

    kissvg_SetLineColor(circle, kissvg_Black);
    kissvg_SetFillColor(circle, kissvg_Black);
    kissvg_SetLineWidth(circle, kissvg_DefaultPen);
    kissvg_SetCanvas(circle, canvas);
    kissvg_CircleSetIsLine(circle, kissvg_False);
    kissvg_SetError(circle, kissvg_False);
    kissvg_SetHasArrows(circle, kissvg_False);
    kissvg_SetFillDraw(circle, kissvg_False);

    circle->arrows = NULL;
    circle->error_message = NULL;
    circle->center = P;
    circle->radius = r;

    return circle;
}

void kissvg_CircleSetErrorMessage(kissvg_Circle *C, char *mes)
{
    long mes_len;
    if (C == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CircleSetErrorMessage\n\n"
             "Input circle is NULL. Aborting.");
        exit(0);
    }

    if (mes == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CircleSetErrorMessage\n\n"
             "Input error message is NULL. Aborting.");
        exit(0);
    }

    kissvg_SetError(C, kissvg_True);
    mes_len = strlen(mes)+1;
    C->error_message = malloc(sizeof(*C->error_message)*mes_len);
    strcpy(C->error_message, mes);
    return;
}

void kissvg_ResetCircle(kissvg_Circle *C, kissvg_TwoVector P, double r)
{
    if (C == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateCircle\n\n"
            "Malloc failed to create circle and return NULL. Aborting."
        );
        exit(0);
    }

    C->center = P;
    C->radius = r;
    return;
}

void kissvg_DestroyCircle(kissvg_Circle *circle)
{
    char *err_mes;
    long n, N_Arrows;
    kissvg_Arrow *current_arrow;
    if (kissvg_HasError(circle))
    {
        err_mes = kissvg_ErrorMessage(circle);
        if (err_mes != NULL)
            free(err_mes);
    }

    if (kissvg_HasArrows(circle))
    {
        N_Arrows = kissvg_NumberOfArrows(circle);
        for (n=0; n<N_Arrows; ++n)
        {
            current_arrow = kissvg_nthArrow(circle, n);
            kissvg_DestroyArrow(current_arrow);
        }
        free(circle->arrows);
    }

    free(circle);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Line2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_Line2D *kissvg_CreateLineFromTwoPoints(kissvg_TwoVector P,
                                              kissvg_TwoVector Q,
                                              kissvg_Canvas2D *canvas)
{
    kissvg_Line2D *line;
    kissvg_TwoVector V;
    line = malloc(sizeof(*line));
    if (line == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLineFromTwoPoints\n\n"
             "Malloc failed to create line and return NULL. Aborting.");
        exit(0);
    }

    V = kissvg_TwoVectorSubtract(Q, P);

    line->P = P;
    line->V = V;

    kissvg_SetLineWidth(line, kissvg_DefaultPen);
    kissvg_SetLineColor(line, kissvg_Black);
    kissvg_SetCanvas(line, canvas);
    kissvg_SetError(line, kissvg_False);
    kissvg_SetHasArrows(line, kissvg_False);
    line->arrows = NULL;
    line->error_message = NULL;

    return line;
}

kissvg_Line2D *kissvg_CreateLineFromPointAndTangent(kissvg_TwoVector P,
                                                    kissvg_TwoVector V,
                                                    kissvg_Canvas2D *canvas)
{
    kissvg_Line2D *line;
    line = malloc(sizeof(*line));
    if (line == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLineFromPointAndTangent\n\n"
             "Malloc failed to create line and return NULL. Aborting.");
        exit(0);
    }

    line->P = P;
    line->V = V;

    kissvg_SetLineWidth(line, kissvg_DefaultPen);
    kissvg_SetLineColor(line, kissvg_Black);
    kissvg_SetCanvas(line, canvas);
    kissvg_SetError(line, kissvg_False);
    kissvg_SetHasArrows(line, kissvg_False);
    line->arrows = NULL;
    line->error_message = NULL;

    return line;
}

void kissvg_DestroyLine2D(kissvg_Line2D *L)
{
    free(L);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                       Begin Drawing Functions                              *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

typedef void (*__arrow_func)(cairo_t *cr, kissvg_TwoVector P1,
                             kissvg_TwoVector Q, double arrow_size,
                             kissvg_Color *fill_color, kissvg_Color *line_color,
                             double line_width, kissvg_Canvas2D *canvas);

static void kissvg_DrawStealthArrow(cairo_t *cr,
                                    kissvg_TwoVector P1,
                                    kissvg_TwoVector Q,
                                    double arrow_size,
                                    kissvg_Color *fill_color,
                                    kissvg_Color *line_color,
                                    double line_width,
                                    kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2;
    kissvg_TwoByTwoMatrix R;
    double x, y;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A0));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A0));
    cairo_move_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A1));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A1));
    cairo_line_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(P1));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(P1));
    cairo_line_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A2));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A2));
    cairo_line_to(cr, x, y);

    cairo_close_path(cr);
    cairo_save(cr);

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }
    cairo_stroke(cr);
    return;
}

static void kissvg_DrawTriangularArrow(cairo_t *cr,
                                      kissvg_TwoVector P1,
                                      kissvg_TwoVector Q,
                                      double arrow_size,
                                      kissvg_Color *fill_color,
                                      kissvg_Color *line_color,
                                      double line_width,
                                      kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2;
    kissvg_TwoByTwoMatrix R;
    double x, y;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A0));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A0));
    cairo_move_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A1));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A1));
    cairo_line_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A2));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A2));
    cairo_line_to(cr, x, y);

    cairo_close_path(cr);
    cairo_save(cr);

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }

    cairo_stroke(cr);
    return;
}

static void kissvg_DrawLatexArrow(cairo_t *cr,
                                  kissvg_TwoVector P1,
                                  kissvg_TwoVector Q,
                                  double arrow_size,
                                  kissvg_Color *fill_color,
                                  kissvg_Color *line_color,
                                  double line_width,
                                  kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2, O, extra, B0, B1;
    kissvg_TwoByTwoMatrix R;
    double x, y, ox, oy, bx0, by0, bx1, by1;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    extra = kissvg_TwoVectorScale(0.05, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    B0 = kissvg_EuclideanMidPoint2D(A0, A1);
    B1 = kissvg_EuclideanMidPoint2D(A0, A2);

    B0 = kissvg_TwoVectorScale(0.5, B0);
    B1 = kissvg_TwoVectorScale(0.5, B1);

    A0 = kissvg_TwoVectorScale(0.8, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);
    B0 = kissvg_TwoVectorAdd(B0, P1);
    B1 = kissvg_TwoVectorAdd(B1, P1);

    A0 = kissvg_TwoVectorAdd(A0, extra);
    A1 = kissvg_TwoVectorAdd(A1, extra);
    A2 = kissvg_TwoVectorAdd(A2, extra);
    B0 = kissvg_TwoVectorAdd(B0, extra);
    B1 = kissvg_TwoVectorAdd(B1, extra);

    O = kissvg_EuclideanMidPoint2D(P1, A0);

    ox = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(O));
    oy = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(O));

    bx0 = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(B0));
    by0 = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(B0));

    bx1 = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(B1));
    by1 = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(B1));

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A0));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A0));
    cairo_move_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A1));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A1));
    cairo_curve_to(cr, ox, oy, bx0, by0, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A2));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A2));
    cairo_line_to(cr, x, y);

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(A0));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(A0));
    cairo_curve_to(cr, bx1, by1, ox, oy, x, y);

    cairo_close_path(cr);
    cairo_save(cr);

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }

    cairo_stroke(cr);
    return;
}

static void kissvg_DrawPolygonalArrows(cairo_t *cr, kissvg_Path2D *path)
{
    kissvg_TwoVector Q;
    kissvg_TwoVector P0, P1;
    kissvg_Canvas2D *canvas;
    kissvg_Color *line_color, *fill_color;
    kissvg_Arrow *arrow;
    kissvg_Bool reverse_arrow;
    __arrow_func DrawArrows;
    double norm;
    double arrow_size, arrow_line_width;
    double path_length;
    double *path_norms;
    double pos, current_arrow_length, arr_pos_length;
    long m, n, N, N_Arrows, current_arrow_pos;
    int arrow_type;

    canvas = kissvg_GetCanvas(path);
    N = kissvg_Path2DNumberOfPoints(path);
    N_Arrows = kissvg_NumberOfArrows(path);

    path_norms = malloc(sizeof(*path_norms) * (N-1));

    P0 = kissvg_Path2DData(path)[0];
    P1 = kissvg_Path2DData(path)[1];
    Q = kissvg_TwoVectorSubtract(P1, P0);

    norm = kissvg_EuclideanNorm2D(Q);
    path_length = norm;
    path_norms[0] = norm;

    for (n=1; n<N-1; ++n)
    {
        P0 = kissvg_Path2DData(path)[n];
        P1 = kissvg_Path2DData(path)[n+1];
        Q = kissvg_TwoVectorSubtract(P1, P0);

        norm = kissvg_EuclideanNorm2D(Q);

        path_length += norm;
        path_norms[n] = path_length;
    }

    for (n=0; n<N_Arrows; ++n)
    {
        arrow = kissvg_nthArrow(path, n);
        arrow_type = kissvg_ArrowType(arrow);

        if (arrow_type == kissvg_StealthArrow)
            DrawArrows = &kissvg_DrawStealthArrow;
        else if (arrow_type == kissvg_TriangularArrow)
            DrawArrows = &kissvg_DrawTriangularArrow;
        else if (arrow_type == kissvg_LatexArrow)
            DrawArrows = &kissvg_DrawLatexArrow;
        else
        {
            puts("Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawPolygonalArrows\n\n"
                "Illegal arrow type selected.\n\n");
            exit(0);
        }

        pos = kissvg_ArrowPosition(arrow);
        line_color = kissvg_LineColor(arrow);
        fill_color = kissvg_FillColor(arrow);
        arrow_size = kissvg_ArrowSize(arrow);
        reverse_arrow = kissvg_ArrowIsReversed(arrow);
        arrow_line_width = kissvg_LineWidth(arrow);

        if (pos < 0.0)
            pos = 0.0;
        else if (pos > 1.0)
            pos = 1.0;

        if (pos == 0.0)
        {
            norm = path_norms[0];

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "The first two points in the input path are the same.\n"
                    "Cannot compute the tangent vector at start of path.\n"
                );
                exit(0);
            }

            P0 = kissvg_Path2DData(path)[0];
            P1 = kissvg_Path2DData(path)[1];

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            Q = kissvg_TwoVectorScale(1.0/norm, Q);

            DrawArrows(cr, P0, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
        else if (pos == 1.0)
        {
            norm = path_norms[N-2];

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "The last two points in the input path are the same.\n"
                    "Cannot compute the tangent vector at end of path.\n"
                );
                exit(0);
            }

            P0 = kissvg_Path2DData(path)[N-2];
            P1 = kissvg_Path2DData(path)[N-1];

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            Q = kissvg_TwoVectorScale(1.0/norm, Q);

            DrawArrows(cr, P1, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
        else
        {
            current_arrow_pos = 0;
            current_arrow_length = path_norms[0];
            arr_pos_length = pos * path_length;

            for (m=0; m<N-1; ++m)
            {
                if (arr_pos_length < current_arrow_length)
                    break;
                current_arrow_pos += 1;
                current_arrow_length = path_norms[current_arrow_pos];
            }

            P0 = kissvg_Path2DData(path)[current_arrow_pos];
            P1 = kissvg_Path2DData(path)[current_arrow_pos+1];
            Q = kissvg_TwoVectorSubtract(P1, P0);

            norm = kissvg_EuclideanNorm2D(Q);

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "Two of the points used for arrows are the same.\n"
                    "Cannot compute the tangent vector.\n"
                );
                exit(0);
            }

            Q = kissvg_TwoVectorScale(1.0/norm, Q);
            norm = arr_pos_length-path_norms[current_arrow_pos-1];
            Q = kissvg_TwoVectorScale(norm, Q);
            P1 = kissvg_TwoVectorAdd(P0, Q);

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            norm = kissvg_EuclideanNorm2D(Q);
            Q = kissvg_TwoVectorScale(1.0/norm, Q);
            DrawArrows(cr, P1, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
    }

    return;
}

void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;
    kissvg_Color *color;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_GetCanvas(path);
    path_size = kissvg_Path2DNumberOfPoints(path);

    if (path_size<2)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_DrawPolygon2D\n\n"
            "Input path has less than two points.\n"
        );
        exit(0);
    }

    Pn = kissvg_Path2DData(path)[0];

    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(Pn));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(Pn));

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];
        x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(Pn));
        y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(Pn));
        cairo_line_to(cr, x, y);
    }

    if (kissvg_Path2DIsClosed(path))
        cairo_close_path(cr);

    cairo_set_line_width(cr, kissvg_LineWidth(path));

    color = kissvg_LineColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

    cairo_stroke(cr);

    if (kissvg_HasArrows(path))
        kissvg_DrawPolygonalArrows(cr, path);
}

void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;
    kissvg_Color *color;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_GetCanvas(path);
    path_size = kissvg_Path2DNumberOfPoints(path);

    if (path_size<2)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_DrawPolygon2D\n\n"
            "Input path has less than two points.\n"
        );
        exit(0);
    }

    Pn = kissvg_Path2DData(path)[0];
    x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(Pn));
    y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(Pn));

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];
        x = canvas->TransformX(canvas, kissvg_TwoVectorXComponent(Pn));
        y = canvas->TransformY(canvas, kissvg_TwoVectorYComponent(Pn));

        cairo_line_to(cr, x, y);
    }

    cairo_close_path(cr);
    cairo_save(cr);
    color = kissvg_FillColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_set_line_width(cr, kissvg_LineWidth(path));

    color = kissvg_LineColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

    cairo_stroke(cr);
}

void kissvg_DrawCircle2D(cairo_t *cr, kissvg_Circle *circle)
{
    kissvg_TwoVector P;
    kissvg_TwoVector center;
    kissvg_Path2D *path;
    double radius;
    double theta;
    double x, y;
    double theta_factor;
    long n, N;

    N = 300;

    theta_factor = 2.0*M_PI/N;

    center = kissvg_CircleCenter(circle);
    radius = kissvg_CircleRadius(circle);

    P = kissvg_NewTwoVector(radius, 0.0);
    P = kissvg_TwoVectorAdd(center, P);

    path = kissvg_CreatePath2D(P, circle->canvas);

    kissvg_SetLineColor(path, kissvg_LineColor(circle));
    kissvg_SetLineWidth(path, kissvg_LineWidth(circle));
    kissvg_SetClosedPath(path, kissvg_True);

    if (kissvg_HasArrows(circle))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(circle);
        path->arrows = circle->arrows;
    }

    for (n=1; n<N; ++n)
    {
        theta = n*theta_factor;
        x = radius*cos(theta);
        y = radius*sin(theta);

        P = kissvg_NewTwoVector(x, y);
        P = kissvg_TwoVectorAdd(P, center);
        kissvg_AppendPath2D(path, P);
    }

    kissvg_DrawPolygon2D(cr, path);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_DestroyPath2D(path);

    return;
}

void kissvg_FillDrawCircle2D(cairo_t *cr, kissvg_Circle *circle)
{
    kissvg_TwoVector P;
    kissvg_TwoVector center;
    kissvg_Path2D *path;
    double radius;
    double theta;
    double x, y;
    double theta_factor;
    long n, N;

    N = 200;

    theta_factor = 2.0*M_PI/N;

    center = kissvg_CircleCenter(circle);
    radius = kissvg_CircleRadius(circle);

    P = kissvg_NewTwoVector(radius, 0.0);
    P = kissvg_TwoVectorAdd(center, P);

    path = kissvg_CreatePath2D(P, circle->canvas);

    kissvg_SetLineColor(path, kissvg_LineColor(circle));
    kissvg_SetLineWidth(path, kissvg_LineWidth(circle));
    kissvg_SetFillColor(path, kissvg_FillColor(circle));

    if (kissvg_HasArrows(circle))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(circle);
        path->arrows = circle->arrows;
    }

    for (n=1; n<N; ++n)
    {
        theta = n*theta_factor;
        x = radius*cos(theta);
        y = radius*sin(theta);

        P = kissvg_NewTwoVector(x, y);
        P = kissvg_TwoVectorAdd(P, center);
        kissvg_AppendPath2D(path, P);
    }

    kissvg_FillDrawPolygon2D(cr, path);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_DestroyPath2D(path);

    return;
}

void kissvg_DrawAxis2D(cairo_t *cr, kissvg_Axis2D *axis)
{
    kissvg_Path2D *path;
    kissvg_Path2D *tick_path;
    kissvg_TwoVector dxtick, dytick, tick;
    kissvg_TwoVector tick_top, tick_bottom;
    kissvg_TwoVector tick_perp, tick_perp_semi, tick_perp_semi_semi;
    long n, N_Ticks;
    double norm;
    double tick_factor;
    double height, semi_height, semi_semi_height;
    double dist;

    path = kissvg_CreatePath2D(axis->start, axis->canvas);

    kissvg_AppendPath2D(path, axis->finish);
    kissvg_SetLineColor(path, kissvg_LineColor(axis));
    kissvg_SetLineWidth(path, kissvg_LineWidth(axis));

    if (kissvg_HasArrows(axis))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(axis);
        path->arrows = axis->arrows;
    }

    if (kissvg_Axis2DHasTicks(axis))
    {
        dist = kissvg_Axis2DTickDistance(axis);
        if (dist <= 0.0)
        {
            puts(
                "Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawAxis2D\n\n"
                "Axis ticks_dx variables is not positive.\n"
            );
            exit(0);
        }

        dxtick = kissvg_TwoVectorSubtract(axis->tick_finish, axis->tick_start);
        norm = kissvg_EuclideanNorm2D(dxtick);

        if (norm == 0)
        {
            puts(
                "Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawAxis2D\n\n"
                "Distance between tick_start and tick_finish is zero.\n"
            );
            exit(0);
        }

        tick_factor = 0.5 / norm;
        height = tick_factor * kissvg_Axis2DTickHeight(axis);
        semi_height = tick_factor * kissvg_Axis2DTickSemiHeight(axis);
        semi_semi_height = tick_factor * kissvg_Axis2DTickSemiSemiHeight(axis);

        tick = kissvg_EuclideanOrthogonalVector2D(dxtick);

        dxtick = kissvg_TwoVectorScale(dist/norm, dxtick);
        tick_perp = kissvg_TwoVectorScale(height, tick);
        tick_perp_semi = kissvg_TwoVectorScale(semi_height, tick);
        tick_perp_semi_semi = kissvg_TwoVectorScale(semi_semi_height, tick);

        N_Ticks = (long)(norm/dist);

        tick = axis->tick_start;

        for (n=0; n<N_Ticks; ++n)
        {
            if ((n % 4) == 0)
                dytick = tick_perp;
            else if ((n % 2) == 0)
                dytick = tick_perp_semi;
            else
                dytick = tick_perp_semi_semi;

            if (axis->down_ticks)
                tick_top = tick;
            else
                tick_top = kissvg_TwoVectorAdd(tick, dytick);

            if (axis->up_ticks)
                tick_bottom = tick;
            else
                tick_bottom = kissvg_TwoVectorSubtract(tick, dytick);

            tick_path = kissvg_CreatePath2D(tick_bottom, axis->canvas);
            kissvg_AppendPath2D(tick_path, tick_top);

            kissvg_SetLineWidth(tick_path, kissvg_Axis2DTickWidth(axis));
            kissvg_SetLineColor(tick_path, kissvg_Axis2DTickColor(axis));
            kissvg_DrawPolygon2D(cr, tick_path);
            kissvg_DestroyPath2D(tick_path);
            tick = kissvg_TwoVectorAdd(tick, dxtick);
        }
    }

    kissvg_DrawPolygon2D(cr, path);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_DestroyPath2D(path);
    return;
}

void kissvg_DrawLine2D(cairo_t *cr, kissvg_Line2D *line, double t0, double t1)
{
    kissvg_Path2D *path;
    kissvg_TwoVector A, B, P, V;

    P = kissvg_Line2DPoint(line);
    V = kissvg_Line2DTangent(line);

    A = kissvg_TwoVectorAdd(P,kissvg_TwoVectorScale(t0, V));
    B = kissvg_TwoVectorAdd(P,kissvg_TwoVectorScale(t1, V));

    path = kissvg_CreatePath2D(A, line->canvas);

    kissvg_SetLineColor(path, kissvg_LineColor(line));
    kissvg_SetLineWidth(path, kissvg_LineWidth(line));
    kissvg_SetClosedPath(path, kissvg_False);
    kissvg_AppendPath2D(path, B);

    kissvg_DrawPolygon2D(cr, path);
    kissvg_DestroyPath2D(path);
    return;
}


void kissvg_GenerateFile(char *filename, void (*instruction)(cairo_t *),
                         kissvg_FileType type, double x_inches, double y_inches)
{
    cairo_surface_t *surface;
    cairo_t *cr;
    char *filename_ext, *ext_name;
    FILE *file;
    int ext_length;
    cairo_surface_t *(*surface_func)(const char*, double, double);

    if (type == kissvg_PS)
    {
        ext_length = 4;
        surface_func = &cairo_ps_surface_create;
        ext_name = ".ps";
    }
    else if (type == kissvg_SVG)
    {
        ext_length = 5;
        surface_func = &cairo_svg_surface_create;
        ext_name = ".svg";
    }
    else if (type == kissvg_PDF)
    {
        ext_length = 5;
        surface_func = &cairo_pdf_surface_create;
        ext_name = ".pdf";
    }
    else
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_GenerateFileFromInstructions\n\n"
             "Illegal file type selected. Currently only PS, SVG, and.\n"
             "PDF outputs are supported.\n\n");
        exit(0);
    }

    /*  Allocate enough memory for the file name, plus the extension (.pdf,   *
     *  .ps, or .svg) and +1 for the null terminator \0, so +4 or +5 total.   */
    filename_ext = malloc(sizeof(*filename_ext)*(strlen(filename)+ext_length));

    /*  Copy FILENAME (should be defined at the top) to filename and then     *
     *  concatenate the ".pdf" file extension. Both functions are found in    *
     *  the C standard library header string.h.                               */
    strcpy(filename_ext, filename);
    strcat(filename_ext, ext_name);

    /*  Create filename.pdf, open it, and set write permissions "w".          */
    file = fopen(filename_ext, "w");

    /*  If fopen failed, file should be NULL. Check this.                     */
    if (file == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_GenerateFileFromInstructions\n\n"
             "fopen failed to open file for writing.\n\n");
        exit(0);
    }

    /*  Create the PDF surface to be drawn on and set cr to this.             */
    surface = surface_func(filename_ext, x_inches, y_inches);
    cr = cairo_create(surface);
    cairo_surface_destroy(surface);

    /*  Invoke the drawing routine and generate the pdf.                      */
    instruction(cr);
    cairo_show_page(cr);
    cairo_destroy(cr);

    /*  Close the file, free the filename pointer, and return.                */
    fclose(file);
    free(filename_ext);
    return;
}
