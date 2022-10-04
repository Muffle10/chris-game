/* Updates player
	@params: player, entities, amount of entities
*/
#include "maths.h"
void UpdatePlayer(Player* player, float d){
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player->rect.x -= player->speed.x;
	if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) player->rect.x += player->speed.x;
	if ((IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) && player->canJump) {
		player->speed.y = -10;
		player->canJump = false;
		player->rect.y += player->speed.y;
	}
	
	if (player->rect.y <= 200){
		if (player->rect.y <= 200 && player->rect.x )
		player->rect.y += player->speed.y;
        player->speed.y += 0.3;
        player->canJump = false;
	}else{
		player->canJump = true;
	}
};