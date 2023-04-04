#ifndef NBH_FUNCTION_TYPES_H
#define NBH_FUNCTION_TYPES_H

#include "nbh_bool.h"
#include "nbh_vec3.h"
#include "nbh_vec6.h"
#include "nbh_color.h"

typedef struct nbh_vec3 (*acceleration)(const struct nbh_vec3 *);
typedef nbh_bool (*stopper)(const struct nbh_vec3 *);
typedef struct nbh_color (*colorer)(const struct nbh_vec6 *);
typedef void (*raytracer)(struct nbh_vec6 *, acceleration, stopper);

#endif
