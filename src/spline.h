#ifndef _SPLINE_H
#define _SPLINE_H

#include "point.h"
#include "point_list.h"
#include "polynomial.h"

polynomial_t **spline_interpolate(point_list_t *nodes);

#endif /* _SPLINE_H */

