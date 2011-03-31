#ifndef _SPLINE_H
#define _SPLINE_H

#include "point.h"
#include "polynomial.h"

polynomial_t **spline_interpolate(point_t **nodes, int nodes_count);

#endif /* _SPLINE_H */

