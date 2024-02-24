#ifndef AABB_H_
#define AABB_H_

#include "../types.h"

#define AABB_PREFIX static

AABB_PREFIX bool AABB_contains_point(AABB aabb, Point p);

#ifdef AABB_IMPLEMENTATION

QUADTREE bool AABB_contains_point(AABB aabb, Point p)
{
	float left = aabb.center.x - aabb.half_dimension;
	float right = aabb.center.x + aabb.half_dimension;
	float top = aabb.center.y - aabb.half_dimension;
	float bottom = aabb.center.y + aabb.half_dimension;

	return left <= p.x && right >= p.x
		&& top <= p.y && bottom >= p.y;
}

#endif

#endif // AABB_H_
