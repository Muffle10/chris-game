#include <raylib.h>
#include "src/defs.h"
#include "src/utils.c"
int main(){
	const int screenWidth = 800;
   	const int screenHeight = 450;
	const char* title = "chris game";
	float deltaTime = GetFrameTime();
	Player player = {{20, 20, 40, 40}, {5, 7}, true, 0};
	EnvEntity entities[] = {};
   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	while (!WindowShouldClose()){
		UpdatePlayer(&player, deltaTime);
		BeginDrawing();
          	ClearBackground(RAYWHITE);
			DrawRectangleRec(player.rect, BLACK);
		EndDrawing();
	}
	CloseWindow(); 
	return 0;
}

