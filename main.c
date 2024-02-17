#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"

#include "./src/input.h"
#include "./src/move.h"
#include "./src/defines.h"
#include "./src/consts.h"
#include "src/types.h"

Camera game_init_camera()
{
	Camera camera = {0};

	camera.position = CLITERAL(Vector3) { 0.0, 32.0, 32.0 };
	camera.up = CLITERAL(Vector3) { 0.0, 1.0, 0.0 };
	camera.target = CLITERAL(Vector3) { 0.0, 0.0, 0.0 };
	camera.fovy = 60;
	camera.projection = CAMERA_PERSPECTIVE;

	return camera;
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib isometric");

	Camera camera = game_init_camera();

	const Vector3 cube_size = { .x = 4.0f, .y = 4.0f, .z = 4.0f };
	Vector3 cube_pos = { .x = 0.0f, .y = cube_size.y / 2.0f, .z = 0.0f };

	SetTargetFPS(60);
	// DisableCursor();

	Vector3 player_vel = {0};

	Vector3 plane_pos = Vector3Zero();
	Vector2 plane_size = { PLANE_SIZE, PLANE_SIZE };

	GameState gs = {
		.steps = 10,
		.walking = false,
		.target_pos = cube_pos,
	};


	Object objs[] = {
		{ .position =  { -16.0f, 2.5f, 0.0f }, .size = { 1.0f, 5.0f, 32.0f } },
		{ .position =  { 16.0f, 2.5f, 0.0f }, .size = { 1.0f, 5.0f, 32.0f } },
		{ .position =  { 0.0f, 2.5f, 16.0f }, .size = { 32.0f, 5.0f, 1.0f } },
	};

	const BoundingBox plain_collision = {
		.min = {
			.x = -plane_size.x / 2.0f,
			.y = 0.0f,
			.z = -plane_size.y / 2.0f
		},
		.max = {
			.x = plane_size.x / 2.0f,
			.y = 0.0f,
			.z = plane_size.y / 2.0f
		}
	};

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		player_vel = handle_input();
		cube_pos = Vector3Add(cube_pos, Vector3Scale(player_vel, PLAYER_SPEED * dt));
		camera.target = cube_pos;
		camera.position = Vector3Add(cube_pos, camera_padding);

		Vector2 mouse_pos = GetMousePosition();
		Ray ray = GetMouseRay(mouse_pos, camera);

		RayCollision ray_col = GetRayCollisionBox(ray, plain_collision);

		move_player(&gs, &cube_pos, objs);
		move_by_click(&gs, ray_col.point);

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				DrawPlane(plane_pos, plane_size, LIGHTGRAY);

				DrawCubeV(objs[0].position, objs[0].size, BLUE);
				DrawCubeV(objs[1].position, objs[1].size, LIME);
				DrawCubeV(objs[2].position, objs[2].size, GOLD);

				DrawCubeV(cube_pos, cube_size, DARKBLUE);

				DrawLine3D(cube_pos, ray_col.point, BLACK);
			EndMode3D();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
