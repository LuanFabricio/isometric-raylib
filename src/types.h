#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <stdbool.h>
#include "raylib.h"
#include "./defines.h"

typedef struct {
	size_t steps;
	bool walking;
	Vector3 target_pos;
} GameState;

typedef struct {
	Vector3 position, size;
} Object;

typedef struct {
	float x, y;
} Point;

typedef struct {
	Point center;
	float half_dimension;
} AABB;

typedef struct QuadTree {
	AABB node;
	size_t points_size;
	Point *points[NODE_CAPACITY];
	struct QuadTree* north_west;
	struct QuadTree* north_east;
	struct QuadTree* south_west;
	struct QuadTree* south_east;
} QuadTree;

#endif // TYPES_H_
