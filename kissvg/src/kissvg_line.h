
#ifndef _KISSVG_LINE_H_
#define _KISSVG_LINE_H_

#include <kissvg/src/kissvg_defs.h>

#define kissvg_Line2D_Point(L)   ((L)->P)
#define kissvg_Line2D_Tangent(L) ((L)->V)

extern kissvg_Line2D *
kissvg_Create_Line2D_From_Two_Points(kissvg_TwoVector P,
                                     kissvg_TwoVector Q,
                                     kissvg_Palette *palette);

extern kissvg_Line2D *
kissvg_Create_Line2D_From_Point_And_Tangent(kissvg_TwoVector P,
                                            kissvg_TwoVector V,
                                            kissvg_Palette *palette);

extern void kissvg_Destroy_Line2D(kissvg_Line2D **line_pointer);

#endif
/*  End of include guard.                                                     */
