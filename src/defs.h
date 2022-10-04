#define G 400
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
//void UpdatePlayer(Player* player, float delta);
void calcPlayerMovement(Player* player, Vector2 vertex);
// TODO: Implement entity collision