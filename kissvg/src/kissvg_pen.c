
#include <stdlib.h>
#include <stdio.h>
#include <kissvg/src/kissvg_pen.h>

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                      Begin kissvg_Pen Functions                            *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/*  Function for creating a color in RGB (red-green-blue) format with real    *
 *  values between 0 and 1. If the transparent Boolean is set to true, one    *
 *  may use the alpha value to set the opacity of the color.                  */
kissvg_Pen *kissvg_Create_Pen(double red, double green, double blue,
                              double linewidth, kissvg_Bool transparent,
                              double alpha)
{
    /*  Declare the necessary variable.                                       */
    kissvg_Pen *pen;

    /*  Allocate memory for the color.                                        */
    pen = malloc(sizeof(*pen));

    /*  Check to make sure malloc didn't fail. Abort if it did.               */
    if (pen == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Create_Pen\n\n"
             "Malloc failed to create pen and returned NULL. Aborting.\n\n");
        exit(0);
    }

    /*  Set the attributes for the color and return.                          */
    pen->dat[0] = red;
    pen->dat[1] = green;
    pen->dat[2] = blue;
    pen->has_transparency = transparent;
    pen->alpha = alpha;
    pen->linewidth = linewidth;

    return pen;
}

/*  Function for destroying new colors. Note you should NOT call this         *
 *  function on predefined colors like kissvg_Black since these are not       *
 *  created using malloc, so free'ing them causes errors.                     */
void kissvg_Destroy_Pen(kissvg_Pen **pen_pointer)
{
    /*  Check that the input pointer was not NULL.                            */
    if (pen_pointer == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Destroy_Pen\n\n"
             "Input color_pointer is NULL. Aborting.");
        exit(0);
    }

    /*  The only thing malloc'd by kissvg_Create_Pen is the pen itself so we  *
     *  only need to free this. If you already destroyed this, the pen is set *
     *  to NULL after being free'd to prevent you from free'ing it twice.     *
     *  However it's best to keep track of what you've created and destroyed. */
    if (*pen_pointer == NULL)
    {
        puts("Warning: KissVG\n"
             "\tFunction: kissvg_Destroy_Pen\n\n"
             "You are calling kissvg_Destroy_Pen on a color that is\n"
             "NULL. You likely already destroyed this color. Returning.\n");
    }
    else
    {
        /*  If pen is not NULL, we can safely free it.                        */
        free(*pen_pointer);

        /*  After freeing, set pen to NULL to prevent user's from trying      *
         *  to free this twice.                                               */
        *pen_pointer = NULL;
    }

    return;
}

/*  The following are pre-defined colors for ease of use. This macro allows   *
 *  us to avoid repeatedly typing the same lines.                             */

#define __kissvg_set_pen__(__pen__, r, g, b)                                   \
static kissvg_Pen __pen__ = {                                                  \
    {r, g, b},                                                                 \
    0.0,                                                                       \
    kissvg_Default_Pen,                                                        \
    kissvg_False                                                               \
}

__kissvg_set_pen__(__kissvg_Blue,       0.00, 0.20, 1.00);
__kissvg_set_pen__(__kissvg_Green,      0.00, 1.00, 0.10);
__kissvg_set_pen__(__kissvg_Red,        1.00, 0.10, 0.10);
__kissvg_set_pen__(__kissvg_Black,      0.00, 0.00, 0.00);
__kissvg_set_pen__(__kissvg_White,      1.00, 1.00, 1.00);
__kissvg_set_pen__(__kissvg_DarkGray,   0.30, 0.30, 0.30);
__kissvg_set_pen__(__kissvg_Gray,       0.60, 0.60, 0.60);
__kissvg_set_pen__(__kissvg_LightGray,  0.80, 0.80, 0.80);
__kissvg_set_pen__(__kissvg_Aqua,       0.10, 1.00, 1.00);
__kissvg_set_pen__(__kissvg_Purple,     0.70, 0.00, 1.00);
__kissvg_set_pen__(__kissvg_Violet,     0.50, 0.00, 1.00);
__kissvg_set_pen__(__kissvg_Pink,       1.00, 0.40, 1.00);
__kissvg_set_pen__(__kissvg_Yellow,     1.00, 1.00, 0.20);
__kissvg_set_pen__(__kissvg_Crimson,    0.80, 0.00, 0.13);
__kissvg_set_pen__(__kissvg_DarkGreen,  0.25, 0.50, 0.00);
__kissvg_set_pen__(__kissvg_Orange,     1.00, 0.40, 0.10);
__kissvg_set_pen__(__kissvg_LightBlue,  0.60, 0.80, 1.00);
__kissvg_set_pen__(__kissvg_Teal,       0.00, 0.50, 0.50);
__kissvg_set_pen__(__kissvg_DarkBlue,   0.00, 0.00, 0.60);
__kissvg_set_pen__(__kissvg_Lavender,   0.80, 0.83, 1.00);
__kissvg_set_pen__(__kissvg_Magenta,    1.00, 0.11, 0.81);
__kissvg_set_pen__(__kissvg_DeepPink,   1.00, 0.08, 0.58);
__kissvg_set_pen__(__kissvg_Marine,     0.30, 0.30, 1.00);
__kissvg_set_pen__(__kissvg_Lime,       0.75, 0.90, 0.00);
__kissvg_set_pen__(__kissvg_Carrot,     1.00, 0.65, 0.30);
__kissvg_set_pen__(__kissvg_Brown,      0.30, 0.15, 0.00);
__kissvg_set_pen__(__kissvg_Azure,      0.00, 0.50, 1.00);
__kissvg_set_pen__(__kissvg_Silver,     0.75, 0.75, 0.75);
__kissvg_set_pen__(__kissvg_Sand,       0.93, 0.84, 0.25);

kissvg_Pen *kissvg_Blue      = &__kissvg_Blue;
kissvg_Pen *kissvg_Green     = &__kissvg_Green;
kissvg_Pen *kissvg_Red       = &__kissvg_Red;
kissvg_Pen *kissvg_Black     = &__kissvg_Black;
kissvg_Pen *kissvg_White     = &__kissvg_White;
kissvg_Pen *kissvg_DarkGray  = &__kissvg_DarkGray;
kissvg_Pen *kissvg_Gray      = &__kissvg_Gray;
kissvg_Pen *kissvg_LightGray = &__kissvg_LightGray;
kissvg_Pen *kissvg_Aqua      = &__kissvg_Aqua;
kissvg_Pen *kissvg_Purple    = &__kissvg_Purple;
kissvg_Pen *kissvg_Violet    = &__kissvg_Violet;
kissvg_Pen *kissvg_Pink      = &__kissvg_Pink;
kissvg_Pen *kissvg_Yellow    = &__kissvg_Yellow;
kissvg_Pen *kissvg_Crimson   = &__kissvg_Crimson;
kissvg_Pen *kissvg_DarkGreen = &__kissvg_DarkGreen;
kissvg_Pen *kissvg_Orange    = &__kissvg_Orange;
kissvg_Pen *kissvg_LightBlue = &__kissvg_LightBlue;
kissvg_Pen *kissvg_Teal      = &__kissvg_Teal;
kissvg_Pen *kissvg_DarkBlue  = &__kissvg_DarkBlue;
kissvg_Pen *kissvg_Lavender  = &__kissvg_Lavender;
kissvg_Pen *kissvg_Magenta   = &__kissvg_Magenta;
kissvg_Pen *kissvg_DeepPink  = &__kissvg_DeepPink;
kissvg_Pen *kissvg_Marine    = &__kissvg_Marine;
kissvg_Pen *kissvg_Lime      = &__kissvg_Lime;
kissvg_Pen *kissvg_Carrot    = &__kissvg_Carrot;
kissvg_Pen *kissvg_Brown     = &__kissvg_Brown;
kissvg_Pen *kissvg_Azure     = &__kissvg_Azure;
kissvg_Pen *kissvg_Silver    = &__kissvg_Silver;
kissvg_Pen *kissvg_Sand      = &__kissvg_Sand;
