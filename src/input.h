#ifndef INPUT_H_
#define INPUT_H_

#include "raylib.h"
#include "raymath.h"
#include "./types.h"

#define MOUSE_MOVE_BTN MOUSE_RIGHT_BUTTON

static Vector3 handle_input()
{
	Vector3 player_vel = {0};
	if(IsKeyDown(KEY_W)) {
		player_vel.x = -1;
	}
	if(IsKeyDown(KEY_S)) {
		player_vel.x = 1;
	}
	if(IsKeyDown(KEY_D)) {
		player_vel.z = -1;
	}
	if(IsKeyDown(KEY_A)) {
		player_vel.z = 1;
	}

	return Vector3Normalize(player_vel);
}

static void move_by_click(GameState *gs, Vector3 ray_point)
{
	if (IsMouseButtonDown(MOUSE_MOVE_BTN)) {
		gs->steps = 0;
		gs->walking = true;
		gs->target_pos.x = ray_point.x;
		gs->target_pos.z = ray_point.z;
	}
}

#endif // INPUT_H_
