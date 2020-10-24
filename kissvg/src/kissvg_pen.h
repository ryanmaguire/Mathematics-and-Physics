/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_PEN_H_
#define _KISSVG_PEN_H_

#include <kissvg/src/kissvg_defs.h>

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                      Begin kissvg_Pen Functions                            *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Default sizes for thin, medium, and thick pens, as well as axes.          */
#define kissvg_Axes_Pen 1.0
#define kissvg_Thin_Pen 0.2
#define kissvg_Thick_Pen 0.8
#define kissvg_Default_Pen 0.4

/*  Macros for accessing the data in the kissvg_Color struct.                 */
#define kissvg_Pen_Red(pen)             ((pen)->dat[0])
#define kissvg_Pen_Green(pen)           ((pen)->dat[1])
#define kissvg_Pen_Blue(pen)            ((pen)->dat[2])
#define kissvg_Pen_Is_Transparent(pen)  ((pen)->has_transparency)
#define kissvg_Pen_Alpha(pen)           ((pen)->alpha)
#define kissvg_Pen_Linewidth(pen)       ((pen)->linewidth)

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Create_Pen                                                     *
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
extern kissvg_Pen *kissvg_Create_Pen(double red, double green, double blue,
                                     double linewidth, kissvg_Bool transparent,
                                     double alpha);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_DestroyColor                                                   *
 *  Purpose:                                                                  *
 *      Destroy a kissvg_Color and free its memory.                           *
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
extern void kissvg_Destroy_Pen(kissvg_Pen **color_pointer);

extern void kissvg_Pen_Change_Linewidth(kissvg_Pen *pen, double linewidth);
extern void kissvg_Pen_Change_Transparency(kissvg_Pen *pen, double alpha);

extern kissvg_Pen *kissvg_Blue;
extern kissvg_Pen *kissvg_Green;
extern kissvg_Pen *kissvg_Red;
extern kissvg_Pen *kissvg_Black;
extern kissvg_Pen *kissvg_White;
extern kissvg_Pen *kissvg_DarkGray;
extern kissvg_Pen *kissvg_Gray;
extern kissvg_Pen *kissvg_LightGray;
extern kissvg_Pen *kissvg_Aqua;
extern kissvg_Pen *kissvg_Purple;
extern kissvg_Pen *kissvg_Violet;
extern kissvg_Pen *kissvg_Pink;
extern kissvg_Pen *kissvg_Yellow;
extern kissvg_Pen *kissvg_Crimson;
extern kissvg_Pen *kissvg_DarkGreen;
extern kissvg_Pen *kissvg_Orange;
extern kissvg_Pen *kissvg_LightBlue;
extern kissvg_Pen *kissvg_Teal;
extern kissvg_Pen *kissvg_DarkBlue;
extern kissvg_Pen *kissvg_Lavender;
extern kissvg_Pen *kissvg_Magenta;
extern kissvg_Pen *kissvg_DeepPink;
extern kissvg_Pen *kissvg_Marine;
extern kissvg_Pen *kissvg_Lime;
extern kissvg_Pen *kissvg_Carrot;
extern kissvg_Pen *kissvg_Brown;
extern kissvg_Pen *kissvg_Azure;
extern kissvg_Pen *kissvg_Silver;
extern kissvg_Pen *kissvg_Sand;

#endif
