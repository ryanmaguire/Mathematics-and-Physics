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
 *      This is the main header file for KissVG. It includes several defined  *
 *      data types and most of the primary functions for drawing and includes *
 *      the header files for Euclidean geometry routines as well as           *
 *      hyperbolic and complex analysis functions.                            *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) kissvg_bool.h:                                                        *
 *      Header file where kissvg_bool is typedef'd, as well as kissvg_true    *
 *      and kissvg_false.                                                     *
 *  2.) kissvg_defs.h:                                                        *
 *      Header file where all data types are defined.                         *
 *  3.) cairo.h                                                               *
 *      Main header file for the cairo library.                               *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 18, 2020                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_H_
#define _KISSVG_H_

/*  Most typedefs are here.                                                   */
#include <kissvg/src/kissvg_defs.h>

/*  Math stuff here.                                                          */
#include <kissvg/src/kissvg_math.h>

/*  We use cairo for producing .ps, .svg, .pdf, etc., files.                  */
#include <cairo/src/cairo.h>

/*  Various defaults for things like line width and arrow sizes.              */
#define kissvg_Default_Arrow_Size 0.1
#define kissvg_Default_Arrow_Linewidth 0.05
#define kissvg_Default_Tick_Size 0.2
#define kissvg_Default_Tick_Dist 1.0
#define kissvg_Default_Tick_Height 0.1
#define kissvg_Default_Label_Margin 1
#define kissvg_Default_Label_Font_Size 10
#define kissvg_Default_Label_Baseline_Skip 12

#include <kissvg/src/kissvg_vector.h>
#include <kissvg/src/kissvg_matrix.h>
#include <kissvg/src/kissvg_pen.h>

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Canvas Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Use these macros to access the data in a pointer to kissvg_Canvas.        */
#define kissvg_Canvas_X_Inches(canvas)    ((canvas)->x_inches)
#define kissvg_Canvas_Y_Inches(canvas)    ((canvas)->y_inches)
#define kissvg_Canvas_X_Scale(canvas)     ((canvas)->x_scale)
#define kissvg_Canvas_Y_Scale(canvas)     ((canvas)->y_scale)
#define kissvg_Canvas_X_Shift(canvas)     ((canvas)->x_shift)
#define kissvg_Canvas_Y_Shift(canvas)     ((canvas)->y_shift)
#define kissvg_Canvas_X_Transform(canvas) ((canvas)->X_Transform)
#define kissvg_Canvas_Y_Transform(canvas) ((canvas)->Y_Transform)
#define kissvg_Canvas_Filetype(canvas)    ((canvas)->filetype)

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Create_Canvas                                                  *
 *  Purpose:                                                                  *
 *      Create a kissvg_Canvas from two double arrays.                        *
 *  Arguments:                                                                *
 *      double scales[2]:                                                     *
 *          The x and y values used to scale the coordinate system to the     *
 *          geometry of the actual file.                                      *
 *      double shifts[2]:                                                     *
 *          The x and y values used to translate the figure so that it is     *
 *          centered in the actual file.                                      *
 *  Outputs:                                                                  *
 *      kissvg_Canvas canvas:                                                 *
 *          The canvas for the image.                                         *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      Malloc is used in this file to allocate the appropriate memory. You   *
 *      must called kissvg_Destroy_Canvas when you are done with the canvas.  *
 ******************************************************************************/
extern kissvg_Canvas *kissvg_Create_Canvas(double x_inches, double y_inches,
                                           double x_min, double x_max,
                                           double y_min, double y_max,
                                           kissvg_Bool one_to_one_apect_ratio,
                                           kissvg_FileType filetype);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Destroy_Canvas                                                 *
 *  Purpose:                                                                  *
 *      Destroy a kissvg_Canvas and free its memory.                          *
 *  Arguments:                                                                *
 *      kissvg_Canvas canvas:                                                 *
 *          The canvas to be destroyed.                                       *
 *  Outputs:                                                                  *
 *      None, this is a void function.                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      This function must be called if kissvg_Create_Canvas was used. Since  *
 *      kissvg_Create_Canvas should be used for every image, this function    *
 *      should always be called at the end.                                   *
 ******************************************************************************/
extern void kissvg_Destroy_Canvas(kissvg_Canvas **canvas_pointer);


/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Palette Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Arrows are stored in the palette for drawing later. These macros are for  *
 *  accessing the data an arrow contains.                                     */
#define kissvg_Arrow_Type(arrow)     ((arrow)->arrow_type)
#define kissvg_Arrow_Position(arrow) ((arrow)->arrow_pos)
#define kissvg_Arrow_Size(arrow)     ((arrow)->arrow_size)
#define kissvg_Arrow_Color(arrow)    ((arrow)->line_pen)
#define kissvg_Arrow_Fill(arrow)     ((arrow)->fill_pen)

/*  These macros are for accessing data inside the actual palette.            */
#define kissvg_Palette_Has_Ticks(palette)          ((palette)->has_ticks)
#define kissvg_Palette_Has_UpTicks(palette)        ((palette)->up_ticks)
#define kissvg_Palette_Has_DownTicks(palette)      ((palette)->down_ticks)
#define kissvg_Palette_Tick_Start(palette)         ((palette)->tick_start)
#define kissvg_Palette_Tick_Finish(palette)        ((palette)->tick_finish)
#define kissvg_Palette_Tick_Distance(palette)      ((palette)->tick_dx)
#define kissvg_Palette_Tick_Height(palette)        ((palette)->tick_height)
#define kissvg_Palette_Tick_SemiHeight(palette)    ((palette)->tick_semi_height)
#define kissvg_Palette_Tick_SemiSemiHeight(palette) \
    ((palette)->tick_semi_semi_height)
#define kissvg_Palette_Tick_Pen(palette)           ((palette)->tick_pen)

extern kissvg_Palette *kissvg_Create_Palette(kissvg_Pen *line_pen,
                                             kissvg_Canvas *canvas);

extern void kissvg_Palette_Set_Fill_Pen(kissvg_Palette *palette,
                                        kissvg_Pen *fill_pen);

extern void kissvg_Palette_Add_Arrow(kissvg_Palette *palette,
                                     double pos,
                                     double arrow_size,
                                     kissvg_Pen *fill_pen,
                                     kissvg_Pen *line_pen,
                                     kissvg_ArrowType type);

extern void kissvg_Palette_Add_Ticks(kissvg_Palette *palette,
                                     double tick_start,
                                     double tick_end,
                                     kissvg_Pen *tick_pen,
                                     double tick_dist,
                                     double tick_height,
                                     double tick_semi_height,
                                     double tick_semi_semi_height);

extern void kissvg_Palette_Use_Up_Ticks(kissvg_Palette *palette);
extern void kissvg_Palette_Use_Down_Ticks(kissvg_Palette *palette);
extern void kissvg_Destroy_Palette(kissvg_Palette *palette);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Label2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

extern kissvg_Label2D *kissvg_Create_Label2D(const char *label_content,
                                             kissvg_TwoVector anchor,
                                             kissvg_Canvas *canvas);

extern void kissvg_DestroyLabel2D(kissvg_Label2D *label);

extern void kissvg_ResetLabel2DContent(kissvg_Label2D *label,
                                       const char *label_content);

extern void kissvg_Label2DSetAnchor(kissvg_Label2D *label,
                                    kissvg_TwoVector anchor);

extern void kissvg_Label2DSetShift(kissvg_Label2D *label,
                                   kissvg_TwoVector shift);

extern void kissvg_Label2DSetMargins(kissvg_Label2D *label,
                                     double margins[4]);

extern void kissvg_Label2DSetFontSize(kissvg_Label2D *label, int font_size);

extern void kissvg_Label2DSetBaselineSkip(kissvg_Label2D *label,
                                          int baseline_skip);

#define kissvg_Label2DMargins(label) (label->margins)
#define kissvg_Label2DFontSize(label) (label->font_size)
#define kissvg_Label2DBaselineSkip(label) (label->baseline_skip)
#define kissvg_Label2DAnchor(label) (label->anchor)
#define kissvg_Label2DShift(label) (label->shift)
#define kissvg_Label2DContent(label) (label->label_content)

extern void kissvg_DrawLabel2D(cairo_t *cr, kissvg_Label2D *label);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Path2D Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

#define kissvg_Path2D_Data(path) (path->data)
#define kissvg_Path2D_Number_Of_Points(path) (path->N_Pts)

extern kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start,
                                          kissvg_Palette *canvas);

extern void kissvg_Append_Path2D(kissvg_Path2D *path, kissvg_TwoVector P);
extern void kissvg_Close_Path2D(kissvg_Path2D *path);
extern void kissvg_Destroy_Path2D(kissvg_Path2D **path_pointer);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Line2D Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/


extern kissvg_Line2D *kissvg_CreateLineFromTwoPoints(kissvg_TwoVector P,
                                                     kissvg_TwoVector Q,
                                                     kissvg_Palette *palette);

extern kissvg_Line2D *
kissvg_CreateLineFromPointAndTangent(kissvg_TwoVector P, kissvg_TwoVector V,
                                     kissvg_Palette *palette);

extern void kissvg_Destroy_Line_2D(kissvg_Line2D *L);

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                       Begin Drawing Functions                              *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

extern void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);
extern void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path);

extern void kissvg_DrawCircle2D(cairo_t *cr, kissvg_Circle *circle);
extern void kissvg_FillDrawCircle2D(cairo_t *cr, kissvg_Circle *circle);

extern void kissvg_DrawLine2D(cairo_t *cr, kissvg_Line2D *line,
                              double t0, double t1);

extern void kissvg_GenerateFile(char *filename, void (*instruction)(cairo_t *),
                                kissvg_FileType type, double x_inches,
                                double y_inches);

#endif
/*  End of include guard.                                                     */
