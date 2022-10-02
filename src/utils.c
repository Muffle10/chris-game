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