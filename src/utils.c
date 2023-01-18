/* Updates player
	@params: player, entities, amount of entities
*/
#include "maths.h"
int random = 0;
enum game_state game;
enum game_state game = WIN;
void DrawLineL(Line line, Color color){
	DrawLineV(line.startPos, line.endPos, color);
}
bool CheckBounds(Player* player, Rectangle* object, int i){
	if(i % 2 == 0){
		return CheckCollisionPointRec((Vector2) {(player->bounds[i].startPos.x + player->bounds[i].endPos.x ) / 2, player->bounds[i].startPos.y}, *object);
	}else{
		return CheckCollisionPointRec((Vector2) {player->bounds[i].startPos.x, (player->bounds[i].startPos.y + player->bounds[i].endPos.y) / 2}, *object);
	}
}
void StartTimer(Timer *timer, double lifetime)
{
	timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return 0 >= timer.lifeTime;
}
void UpdateTimer(Timer* timer){
}
double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}
void HandleMovement(Player* player){
	if(!(/*player->rect.x < 0 || player->rect.x + player->rect.width > screenWidth*/ false)){
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
		player->rect.x -= player->speed.x;
		player->direction = 0;
	}
	if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) {
		player->rect.x += player->speed.x;
		player->direction = 1;
	}
	player->rect.y += player->speed.y;
    player->speed.y += 0.3;
    player->canJump = false;
	} else {
		player->rect.x = screenWidth;
	}
}
void HandleLadder(Player* player){
	if ((IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)))
	{
		player->rect.y += 1;
	}
}
void UpdatePlayer(Player* player, Rectangle* ground, Rectangle* ladder, float d){
	if ((IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) && player->canJump) {
		player->speed.y = -9;
		player->canJump = false;
		player->rect.y += player->speed.y;
	}
	
	if (CheckBounds(player, ground, 2)){
		if (CheckBounds(player, ladder, 2)){
			player->speed.y = 0;
			if ((IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S))) {
				player->rect.y += 1;
			}
			if (IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
				if ((IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) && !player->canJump) {
					player->speed.y = -8;
					player->canJump = false;
				}else{
	}
				player->rect.y -= 1;
			}
		} else {
			player->speed.y = 0;
			player->rect.y = ground->y - player->rect.height;
			player->canJump = true;
		}
	} else {
		if (CheckBounds(player, ladder, 2)){
			player->speed.y = 0;
			if ((IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S))){
				player->rect.y += 1;
			}
			if (IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
				player->rect.y -= 1;
			}
		} else {
		}
	}
};
void UpdatePlayerGround(Player* player, Rectangle* ground, Rectangle* ladder, float d){
	if ((IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) && player->canJump) {
		player->speed.y = -9;
		player->canJump = false;
		player->rect.y += player->speed.y;
	}
	if(CheckCollisionPointRec((Vector2){player->rect.x + player->rect.width/2, player->rect.y + player->rect.height}, *ground)){
		player->speed.y = 0;
		player->rect.y = ground->y - player->rect.height;
		player->canJump = true;
	}
}
void UpdateEnemy(Enemy* enemy, Timer* timer, Player* player, Rectangle* ground){
	/*
	make enemy move left and right randomly by changing enemy.x using raylib getrandomvalue*/
if( fmod(GetTime(), GetRandomValue(0, 5)) >= 0 && fmod(GetTime(), GetRandomValue(0,5)) <= 0.02 ){
	if(enemy->space.x + enemy->space.width > screenWidth || enemy->space.x < 0){
		enemy->space.x = 100;
	}
	enemy->speed = GetRandomValue(-1, 1);
}
if (enemy->space.x < 0 || enemy->space.x + enemy->space.width > screenWidth){
	enemy->space.x = 400;
}
if( fmod(GetTime(), GetRandomValue(1,5)) >= 0 && fmod(GetTime(), GetRandomValue(1,5)) <= 1 ){
			enemy->space.x -= enemy->speed;
}
enemy->space.y += enemy_speed;
if(CheckCollisionRecs(player->fist, enemy->space)){
		enemy->space = (Rectangle){0,0,0,0};
}
if(CheckCollisionRecs(player->fist, enemy->space)){
		enemy->space = (Rectangle){0,0,0,0};
		score += 200;
}
if(CheckCollisionRecs(enemy->space, *ground)){
	enemy->space.y = ground->y - enemy->space.height;
} else{
}
if(CheckCollisionRecs(enemy->space, player->rect)){
	game = OVER;
}
}
void HandleBorders(Rectangle* space, Rectangle* border, int i){
	if (CheckCollisionRecs(*space, *border)){
		if(i == 1){
		space->x =  border->x - space->width ;
		} else {
			space->x =  border->x + border->width;
		}
	} else{
	}
}