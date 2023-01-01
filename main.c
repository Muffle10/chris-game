#include <raylib.h>
#include "src/defs.h"
#include "src/utils.c"
int main(){
	//Definitions
	float deltaTime = GetFrameTime();
	const Rectangle ground = (Rectangle) {0, 300, screenWidth, 30};;
	Player player = {{20, 20, 40, 40}, {5, 7}, true, 0};
	EnvEntity entities[2];
   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	while (!WindowShouldClose()){
		UpdatePlayer(&player, &ground, deltaTime);
		/*
		bounds[0]= top
		bounds[1]= left
		bounds[2]= bottom
		bounds[3]= right
		even = vertical 
		odd = horizontal
		*/
		entities[0].space = (Rectangle){100,100,100,100};
		entities[1].space = (Rectangle){300,100,30,30};
		player.bounds[0]= (Line) {{player.rect.x, player.rect.y,}, {player.rect.x + player.rect.width, player.rect.y}};
		player.bounds[1]= (Line) {{player.rect.x, player.rect.y,}, {player.rect.x, player.rect.y + player.rect.height}};
		player.bounds[2]= (Line) {{player.rect.x, player.rect.y + player.rect.height,}, {player.rect.x + player.rect.width, player.rect.y + player.rect.height}};
		player.bounds[3]= (Line) {{player.rect.x + player.rect.width, player.rect.y}, {player.rect.x + player.rect.width, player.rect.y + player.rect.height}};
		BeginDrawing();
          	ClearBackground(RAYWHITE);
			DrawRectangleRec(entities[1].space, RED);
			for(int i = 0; i < 4; i++){
				DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 10, RED);
				if(CheckBounds(&player, &ground, i)){
					DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 100, PINK);
				}
			}
			DrawRectangleRec(player.rect, BLACK);
			DrawRectangleRec(ground, BLUE);
		EndDrawing();
	}
	CloseWindow(); 
	return 0;
}

