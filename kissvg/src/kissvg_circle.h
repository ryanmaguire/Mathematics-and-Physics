
/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_CIRCLE_H_
#define _KISSVG_CIRCLE_H_

#include <kissvg/src/kissvg_defs.h>
#include <kissvg/src/kissvg.h>

#define kissvg_Circle_Center(circle)    ((circle)->center)
#define kissvg_Circle_Radius(circle)    ((circle)->radius)
#define kissvg_Circle_Is_Line(circle)   ((circle)->is_line)
#define kissvg_Circle_Point(circle)     ((circle)->P)
#define kissvg_Circle_Tangent(circle)   ((circle)->V)

extern kissvg_Circle *
kissvg_Create_Circle(kissvg_TwoVector P, double r, kissvg_Palette *palette);

extern void
kissvg_Circle_Set_Line(kissvg_Circle *circle, kissvg_TwoVector P,
                       kissvg_TwoVector V);

extern void
kissvg_Circle_Set_Error_Message(kissvg_Circle *circle, char *mes);

extern void
kissvg_Reset_Circle(kissvg_Circle *circle, kissvg_TwoVector P, double r);

extern void
kissvg_Destroy_Circle(kissvg_Circle **circle);

#endif
