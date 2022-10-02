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