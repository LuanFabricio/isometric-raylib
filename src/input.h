#ifndef INPUT_H_
#define INPUT_H_

#include "raylib.h"
#include "raymath.h"

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


#endif // INPUT_H_
