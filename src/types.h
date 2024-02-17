#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <stdbool.h>
#include "raylib.h"

typedef struct {
	size_t steps;
	bool walking;
	Vector3 target_pos;
} GameState;

typedef struct {
	Vector3 position, size;
} Object;

#endif // TYPES_H_
