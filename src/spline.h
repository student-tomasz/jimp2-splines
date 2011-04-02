#ifndef _SPLINE_H
#define _SPLINE_H

#include "point.h"
#include "list.h"
#include "polynomial.h"

polynomial_t **spline_interpolate(list_t *nodes);

#endif /* _SPLINE_H */

