#include <raylib.h>
#include <unistd.h> 
#include <string.h>
#include <time.h>
#include "src/defs.h"
#include "src/utils.c"
int main(){
	//Definitions
	Player player = {{200, 700, 40, 40}, {5, 7}, true, 0, {200, 700, 40, 40} };
	double deltaTime;
	int cookies = 0;
	int lives = 3;
	bool showing = false;
	game = GAME;
	Timer timer;
	Color colors[4] = {BLUE, RED, GREEN, YELLOW};
	Rectangle clicker = {200, 300, 100, 100};
	Rectangle ground = {0, screenHeight - 30, screenWidth, 40};
	Rectangle* platforms = MemAlloc(sizeof(Rectangle)*4);
	Rectangle* ladders = MemAlloc(sizeof(Rectangle)*4);
	Rectangle left = {0,0,30, screenHeight};
	Rectangle right = {screenWidth - 30,0,30, screenHeight};
	Rectangle goal = {100, 80, 50, 50};
	Enemy* enemies = MemAlloc(sizeof(Enemy)*10);
	static const Rectangle platforms_mem[] = {
		{0, screenHeight - 270, screenWidth, 30},
		{0, screenHeight - 490, screenWidth, 30},
		{0, screenHeight -  690, screenWidth, 30}
	};
	static const Enemy enemies_mem[] = {
		{{50, screenHeight -  725, 35, 35}, IDLE},
		{{250, screenHeight -  725, 35, 35}, IDLE},
		{{400, screenHeight -  725, 35, 35}, IDLE}
	};
	static const Rectangle ladders_mem[]= {
		{screenWidth - 80 - 70, screenHeight - 270,70,250},
		{70, screenHeight - 490,70,250},
		{screenWidth - 75 - 70, screenHeight - 690,70,230},
	};
	float levels[3] = {screenHeight - 270 - 30, screenHeight - 490 - 30, screenHeight -  690 - 30};
	memcpy(platforms, platforms_mem, sizeof(platforms_mem));
	memcpy(ladders, ladders_mem, sizeof(ladders_mem));
	memcpy(enemies, enemies_mem, sizeof(enemies_mem));

   	InitWindow(screenWidth, screenHeight, title);
   	SetTargetFPS(60);
	int enemy_size = sizeof(enemies_mem) / sizeof(Enemy);
	while (!WindowShouldClose()){
		HandleMovement(&player);
		UpdatePlayerGround(&player, &ground, &ladders[1], deltaTime);
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
		if(showing){
		if(player.direction == 0){
			player.fist = (Rectangle) {player.rect.x - 30, player.rect.y + (player.rect.height / 2) - 15 ,30,30};
		} else {
			player.fist = (Rectangle) {player.rect.x + player.rect.width, player.rect.y + (player.rect.height / 2) - 15,30,30};
		}} else{
			player.fist = (Rectangle) {0};
		}
		if(IsKeyPressed(KEY_SPACE)){
			showing = true;
		} else{
			showing = false;
		}

		BeginDrawing();
		if(game == GAME){
			if( (fmod(GetTime(), 5) >= 0 && fmod(GetTime(), 5) <= 0.02)){
			score += GetRandomValue(30, 50);
			if(enemy_size > 9){
				enemy_size = 0;
			} else {
				if(enemies[enemy_size].space.width == (float)0){
					enemies[enemy_size] = (Enemy) {{100 * GetRandomValue(1,4), 0/*levels[GetRandomValue(0,2)]*/, 30, 30},GetRandomValue(-5,5), 0};
				} else {
				}
				enemy_size++;
			}
		}
			DrawRectangleRec(left, BLACK);
			DrawRectangleRec(right, BLACK);
			DrawRectangleRec(goal, PINK);
          	ClearBackground(RAYWHITE);
			for(int i = 0; i < 3; i++){
			DrawRectangleRec(platforms[i], BLACK);
			DrawRectangleRec(ladders[i], GRAY);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			UpdatePlayer(&player, &platforms[i], &ladders[i], deltaTime);
			}
			if(showing)DrawRectangleRec(player.fist, RED);
			for(int i = 0; i < 10; i++){
				if(CheckCollisionRecs(player.fist, enemies[i].space)){
				score += 200;
				}
				UpdateEnemy(&enemies[i], &timer, &player, &ground);
				if(CheckCollisionRecs(ground, enemies[3].space)){
					DrawRectangleRec((Rectangle){30,30,100,100}, RED);
					//enemies[i].space.y -= 20;
				} else{
					enemies[i].space.y += 7;
				}
				UpdateEnemy(&enemies[i], &timer, &player, &platforms[ i % 4]);
				HandleBorders(&player.rect, &left, 0);
				HandleBorders(&player.rect, &right, 1);
				HandleBorders(&enemies[i].space, &left, 0);
				HandleBorders(&enemies[i].space, &right, 1);
				/* at an interval make player speed a random number create enemy struct speed// at fmod, enemy.speed = random()// pos or neg*/
				/* work on making enemies spawn more in player level*/
				DrawRectangleRec(enemies[i].space, RED);
			}
			DrawText(TextFormat("%d", CheckCollisionRecs(enemies[3].space, ground)), 400, 200,20,BLACK);
			DrawText(TextFormat("%f", fmod(GetTime(), 5)), GetFrameTime(),100,20,BLACK);
			/*for(int i = 0; i < 4; i++){
				DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 10, RED);
				if(CheckBounds(&player, &ground, i)){
					DrawLineEx(player.bounds[i].startPos, player.bounds[i].endPos, 100, PINK);
				}
			}*/
			if(CheckCollisionRecs(player.rect, goal)){
				game = WIN;
			}
			DrawRectangleRec(player.rect, BLUE);
			DrawRectangleRec(ground, BLACK);
			DrawText(TextFormat("%i", score), 400 , 100, 20, BLACK);
		} else if(game == OVER){
			sleep(1);
			if(lives == 0){
				ClearBackground(BLACK);
				DrawText("GAME OVER", 100, 400, 40, RAYWHITE);
				DrawText(TextFormat("Score: %i", score), 100, 600, 20, RAYWHITE);
			} else {
			player = (Player) {{200, 700, 40, 40}, {5, 7}, true, 0, {200, 700, 40, 40} };
			enemies[0]= (Enemy){{50 * GetRandomValue(1,10), screenHeight -  725, 35, 35}, IDLE};
			enemies[1]= (Enemy){{50 * GetRandomValue(1,10), screenHeight -  725, 35, 35}, IDLE};
			enemies[2]= (Enemy){{50 * GetRandomValue(1,10), screenHeight -  725, 35, 35}, IDLE};
			for(int i = 3; i<10; i++){
				enemies[i]= (Enemy){{0,0,0,0}, IDLE};
			}
			lives--;
			/*memcpy(enemies, enemies_mem, sizeof(enemies_mem));*/
			ClearBackground(BLACK);
			game = GAME;
			}
		}else if(game == WIN){
			ClearBackground(BLACK);
			DrawText(TextFormat("Score: %i", score), 100,200, 20, RAYWHITE);
			DrawText("You Win!",100,100,30,WHITE);
			if(score >= 4269){
				DrawCircleV((Vector2){clicker.x + 20, clicker.y}, 50, DARKBROWN);
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)  && CheckCollisionPointCircle(GetMousePosition(), (Vector2){clicker.x + 10, clicker.y}, 50)){
					cookies++;
				}
				DrawText(TextFormat("%i", cookies), clicker.x, clicker.y + clicker.width, 20, WHITE);
			}

		}
		EndDrawing();
		deltaTime = GetFrameTime();
	}
	CloseWindow(); 
	return 0;
}

