#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_SPEED 50.0f

const Vector3 camera_padding = { .x = 15.f, .y = 15.0f, .z = 0.0f };

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

	Vector3 cube_pos = { .x = 0.0f, 0.0f, 0.0f };
	const Vector3 cube_size = { .x = 4.0f, 1.0f, 4.0f };

	SetTargetFPS(60);
	DisableCursor();

	Vector3 player_vel = {0};

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		// UpdateCamera(&camera, CAMERA_FREE);
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


		player_vel = Vector3Normalize(player_vel);
		cube_pos = Vector3Add(cube_pos, Vector3Scale(player_vel, PLAYER_SPEED * dt));
		camera.target = cube_pos;
		camera.position = Vector3Add(cube_pos, camera_padding);

		player_vel = Vector3Zero();

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY);
				DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);
				DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
				DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);

				DrawCubeV(cube_pos, cube_size, BLUE);
			EndMode3D();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
