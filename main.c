#include <raylib.h>
#include <string.h>
#include "src/defs.h"
#include "src/utils.c"
int main(){
	//Definitions
	float deltaTime = GetFrameTime();
	Player player = {{20, 20, 40, 40}, {5, 7}, true, 0};
	Color colors[4] = {BLUE, RED, GREEN, YELLOW};
	Rectangle ground = {0, screenHeight - 30, screenWidth, 40};
	Rectangle* platforms = MemAlloc(sizeof(Rectangle)*4);
	Rectangle* ladders = MemAlloc(sizeof(Rectangle)*3);
	Enemy* enemies = MemAlloc(sizeof(Enemy)*3);
	static const Rectangle platforms_mem[] = {
		{0, screenHeight - 270, screenWidth, 30},
		{0, screenHeight - 490, screenWidth, 30},
		{0, screenHeight -  690, screenWidth, 30}
	};
	static const Enemy enemies_mem[] = {
		{{100, 270, 100, 30}, IDLE},
		{0},
		{0}
	};
	static const Rectangle ladders_mem[]= {
		{screenWidth - 80, screenHeight - 270,70,250},
		{70, screenHeight - 490,70,250},
		{screenWidth - 75, screenHeight - 690,70,230},
	};
	memcpy(platforms, platforms_mem, sizeof(platforms_mem));
	memcpy(ladders, ladders_mem, sizeof(ladders_mem));
	memcpy(enemies, enemies_mem, sizeof(enemies_mem));

   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	while (!WindowShouldClose()){
		HandleMovement(&player);
		/*
		bounds[0]= top
		bounds[1]= left
		bounds[2]= bottom
		bounds[3]= right
		even = vertical 
		odd = horizontal
		*/
		player.bounds[0]= (Line) {{player.rect.x, player.rect.y,}, {player.rect.x + player.rect.width, player.rect.y}};
		player.bounds[1]= (Line) {{player.rect.x, player.rect.y,}, {player.rect.x, player.rect.y + player.rect.height}};
		player.bounds[2]= (Line) {{player.rect.x, player.rect.y + player.rect.height,}, {player.rect.x + player.rect.width, player.rect.y + player.rect.height}};
		player.bounds[3]= (Line) {{player.rect.x + player.rect.width, player.rect.y}, {player.rect.x + player.rect.width, player.rect.y + player.rect.height}};
		BeginDrawing();
          	ClearBackground(RAYWHITE);
			for(int i = 0; i < 3; i++){
			DrawRectangleRec(platforms[i], BLACK);
			DrawRectangleRec(ladders[i], GRAY);
			DrawRectangleRec(enemies[i].space, GRAY);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i],deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i],deltaTime);
			UpdatePlayer(&player, &ground, &ladders[i], deltaTime);
			}
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

