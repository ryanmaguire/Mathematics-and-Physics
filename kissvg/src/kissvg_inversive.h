#ifndef _KISSVG_INVERSIVE_H_
#define _KISSVG_INVERSIVE_H_

#include "kissvg_defs.h"

extern kissvg_TwoVector
kissvg_InversiveGeometryPoint(kissvg_Circle *C, kissvg_TwoVector P);

extern kissvg_Circle *
kissvg_InversiveGeometryCircle(kissvg_Circle *C0, kissvg_Circle *C1);

extern kissvg_Circle *
kissvg_InversiveGeometryLine(kissvg_Circle *C, kissvg_Line2D *L);
#endif
