#define G 400
/*
Player
	attr: 
		- rect: Vector (x,y) int (width,height)
		  Used to render player to screen
		- speed: Vector (x, y)
		  Determines speed of player
		- canJump: boolean
		  Allows player to have proper jump physics
		- JumpVel: float
*/
bool getCollision(Rectangle object1, Rectangle object2);
typedef struct EnvEntity{
	Rectangle space;
	int blocking;
	Color color;
} EnvEntity;
typedef struct {
	Vector2 startPos;
	Vector2 endPos;
} Line;
typedef struct Player{
	Rectangle rect;
	Vector2 speed;
	bool canJump;
	float jumpVel;
	Line bounds[];
} Player;
void DrawLineL(Line line, Color color);
const int screenWidth = 800;
const int screenHeight = 450;
const char* title = "chris game";

//void UpdatePlayer(Player* player, float delta);