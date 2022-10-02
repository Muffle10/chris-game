#include <raylib.h>
typedef struct Player{
	Rectangle rect;
	Vector2 speed;
	bool canJump;
	float jumpVel;
} Player;
typedef struct EnvEntity{
	Rectangle space;
	int blocking;
	Color color;
} EnvEntity;
void UpdatePlayer(Player* player, EnvEntity* entity, int length);

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
void UpdatePlayer(Player* player, EnvEntity *entities, int length){
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player->rect.x -= player->speed.x;
	if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) player->rect.x += player->speed.x;
	if ((IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W))&& player->canJump) {
		player->jumpVel += player->speed.y * 20;
		player->speed.y = -5;
		player->canJump = false;
	}
	player->rect.y = 400 - player->jumpVel;
	bool isNotTouchingGround = player->rect.y <= 400;
	if (isNotTouchingGround){
		 player->jumpVel -= 5;
		 player->canJump = false;
	}else{
		player->canJump = true;
	}
};

