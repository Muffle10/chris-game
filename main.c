#include <raylib.h>
int main(){
	const int screenWidth = 800;
   	const int screenHeight = 450;
	const char* title = "chris game";
   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	while (!WindowShouldClose()){
		BeginDrawing();
          	ClearBackground(RAYWHITE);
		EndDrawing();
   
	}
	CloseWindow(); 
	return 0;
}
