#ifndef MOVE_H_
#define MOVE_H_

#include "raylib.h"
#include "raymath.h"
#include "./types.h"
#include <stdio.h>

static bool handle_collision_2(const Object *src, Vector3 move, Object *objects)
{
	// bool collides = false;
	Vector3 obj_half_size = Vector3Scale(src->size, 0.5f);
	Vector3 new_pos = Vector3Subtract(src->position, move);
	BoundingBox src_box = {
		.min = Vector3Subtract(new_pos, obj_half_size),
		.max = Vector3Add(new_pos, obj_half_size),
	};
	BoundingBox obj_box = {};


	for (int i = 0; i < 3; i++) {
		Object obj = objects[i];
		Vector3 half_size = Vector3Scale(obj.size, 0.5f);
		obj_box.min = Vector3Subtract(obj.position, half_size);
		obj_box.max = Vector3Add(obj.position, half_size);

		if (CheckCollisionBoxes(src_box, obj_box)) {
			return false;
		}
	}

	return true;
}

static bool handle_collision(Object *src, Vector3 move, Object *col_obj)
{
	bool collides = false;
	const BoundingBox col_obj_box = {
		.min = Vector3Subtract(col_obj->position, Vector3Scale(col_obj->size, 0.5f)),
		.max = Vector3Add(col_obj->position, Vector3Scale(col_obj->size, 0.5f)),
	};

	BoundingBox src_box = {
		.min = Vector3Subtract(src->position, Vector3Scale(src->size, 0.5f)),
		.max = Vector3Add(src->position, Vector3Scale(src->size, 0.5f)),
	};

	src_box.min = Vector3Subtract(src_box.min, CLITERAL(Vector3){ move.x, 0.0f, 0.0f });
	src_box.max = Vector3Subtract(src_box.max, CLITERAL(Vector3){ move.x, 0.0f, 0.0f });
	if (CheckCollisionBoxes(src_box, col_obj_box)) {
		if (move.x > 0.0f) {
			src_box.max.x = col_obj_box.min.x;
			src_box.min.x = src_box.max.x - src->size.x;
		} else if (move.x < 0.0f) {
			src_box.min.x = col_obj_box.max.x;
			src_box.max.x = src_box.min.x + src->size.x;
		}
		collides = true;
	}

	src_box.min = Vector3Subtract(src_box.min, CLITERAL(Vector3){ 0.0f, move.y, 0.0f });
	src_box.max = Vector3Subtract(src_box.max, CLITERAL(Vector3){ 0.0f, move.y, 0.0f });
	if (CheckCollisionBoxes(src_box, col_obj_box)) {
		if (move.y > 0.0f) {
			src_box.max.y = col_obj_box.min.y;
			src_box.min.y = src_box.max.y - src->size.y;
		} else if (move.y < 0.0f) {
			src_box.min.y = col_obj_box.max.y;
			src_box.max.y = src_box.min.y + src->size.y;
		}
		collides = true;
	}

	src_box.min = Vector3Subtract(src_box.min, CLITERAL(Vector3){ 0.0f, 0.0f, move.z });
	src_box.max = Vector3Subtract(src_box.max, CLITERAL(Vector3){ 0.0f, 0.0f, move.z });
	if (CheckCollisionBoxes(src_box, col_obj_box)) {
		if (move.z > 0.0f) {
			src_box.max.z = col_obj_box.min.z;
			src_box.min.z = src_box.max.z - src->size.z;
		} else if (move.z < 0.0f) {
			src_box.min.z = col_obj_box.max.z;
			src_box.max.z = src_box.min.z + src->size.z;
		}
		collides = true;
	}
	src->position = Vector3Add(src_box.min, Vector3Scale(src->size, 0.5));

	return collides;
}

static void move_player(GameState *gs, Vector3 *pos, Object objs[3], float delta_time)
{
	if (gs->steps < 10 && gs->walking) {
		Vector3 step_vec = Vector3Scale(Vector3Subtract(*pos, gs->target_pos), delta_time);

		Object src = {
			.position = *pos,
			.size = { .x = 4.0f, .y = 4.0f, .z = 4.0f },
		};

	//	for (size_t i = 0; i < 3; i++) {
	//		if (handle_collision(&src, step_vec, &objs[i])) {
	//			break;
	//		}
	//	}

		// Vector3 walk_vec = {0};
		// walk_vec.x = step_vec.x;
		// if (handle_collision_2(&src, walk_vec, objs)) {
		// 	*pos = Vector3Subtract(src.position, walk_vec);
		// }

		// walk_vec.x = 0;
		// walk_vec.y = step_vec.y;
		// if (handle_collision_2(&src, walk_vec, objs)) {
		// 	*pos = Vector3Subtract(src.position, walk_vec);
		// }

		// walk_vec.y = 0;
		// walk_vec.z = step_vec.z;
		// if (handle_collision_2(&src, walk_vec, objs)) {
		// 	*pos = Vector3Subtract(src.position, step_vec);
		// }

		if (!handle_collision_2(&src, step_vec, objs)) return;

		*pos = Vector3Subtract(src.position, step_vec);
		gs->steps += 1;
	} else {
		gs->steps = 0;
		gs->walking = false;
	}
}

#endif // MOVE_H_
