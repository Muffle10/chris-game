#include <raylib.h>
#include "types.h"
#include "utils.c"
int main(){
	const int screenWidth = 800;
   	const int screenHeight = 450;
	const char* title = "chris game";
	Player player = {{20, 20, 40, 40}, {5, 5}, true, 0};
	EnvEntity entities[] = {};
   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	while (!WindowShouldClose()){
		UpdatePlayer(&player, entities, 4);
		BeginDrawing();
          	ClearBackground(RAYWHITE);
		DrawRectangleRec(player.rect, BLACK);
		EndDrawing();
	}
	CloseWindow(); 
	return 0;
}

