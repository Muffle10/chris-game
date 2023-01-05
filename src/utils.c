/* Updates player
	@params: player, entities, amount of entities
*/
#include "maths.h"
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
void HandleMovement(Player* player){
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player->rect.x -= player->speed.x;
	if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) player->rect.x += player->speed.x;
	player->rect.y += player->speed.y;
    player->speed.y += 0.3;
    player->canJump = false;
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
			if ((IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)))
	{
		player->rect.y += 1;
	}
	if (IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
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
			if ((IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)))
	{
		player->rect.y += 1;
	}
	if (IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
		player->rect.y -= 1;
	}
		} 
	}
};