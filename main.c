#include <raylib.h>
#include <unistd.h> 
#include <string.h>
#include <time.h>
#include "src/defs.h"
#include "src/utils.c"
int main(){
	//Definitions
	Player player = {{200, 700, 40, 40}, {5, 7}, true, 0};
	double deltaTime;
	Timer timer;
	Color colors[4] = {BLUE, RED, GREEN, YELLOW};
	Rectangle ground = {0, screenHeight - 30, screenWidth, 40};
	Rectangle* platforms = MemAlloc(sizeof(Rectangle)*4);
	Rectangle* ladders = MemAlloc(sizeof(Rectangle)*4);
	Enemy* enemies = MemAlloc(sizeof(Enemy)*10);
	static const Rectangle platforms_mem[] = {
		{0, screenHeight - 270, screenWidth, 30},
		{0, screenHeight - 490, screenWidth, 30},
		{0, screenHeight -  690, screenWidth, 30}
	};
	static const Enemy enemies_mem[] = {
		{{45, screenHeight -  725, 35, 35}, IDLE},
		{{70, screenHeight -  725, 35, 35}, IDLE},
		{{115, screenHeight -  725, 35, 35}, IDLE}
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
	int enemy_size = sizeof(enemies_mem) / sizeof(Enemy);
	while (!WindowShouldClose()){
		HandleMovement(&player);
		UpdatePlayerGround(&player, &ground, &ladders[1], deltaTime);
		if( (fmod(GetTime(), 5) >= 0 && fmod(GetTime(), 5) <= 0.02)){
			if(enemy_size >= 10){
			} else {
				enemies[enemy_size] = (Enemy) {{screenWidth - 50, 200, 100, 30}, 0};
				enemy_size++;
			}
		}
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
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			}
			DrawText(TextFormat("%d", enemy_size), 400 , 100, 20, BLACK);
			for(int i = 0; i < 5; i++){
				UpdateEnemy(&enemies[i], &timer, &player);
				DrawRectangleRec(enemies[i].space, RED);
			}
			DrawText(TextFormat("%f", fmod(GetTime(), 5)), GetFrameTime(),100,20,BLACK);
			for(int i = 0; i < 4; i++){
				DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 10, RED);
				if(CheckBounds(&player, &ground, i)){
					DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 100, PINK);
				}
			}
			DrawRectangleRec(player.rect, BLACK);
			DrawRectangleRec(ground, BLUE);
		EndDrawing();
		deltaTime = GetFrameTime();
	}
	CloseWindow(); 
	return 0;
}

