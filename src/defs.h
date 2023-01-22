#define G 400
bool getCollision(Rectangle object1, Rectangle object2);
enum enemy_state {IDLE, MOVING, THROWING, CLIMBING};
int enemy_speed = 0;
int score = 0;
enum game_state{START, GAME, OVER, WIN};
typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;
typedef struct Enemy{
	Rectangle space;
	bool living;
	float speed;
} Enemy;
typedef struct {
	Vector2 startPos;
	Vector2 endPos;
} Line;
/*
	Line: Used to define lines using vectors
		- startPos: beginning position
		- endPos: ending position
*/
typedef struct Player{
	Rectangle rect;
	Vector2 speed;
	bool canJump;
	int direction;
	Rectangle fist;
	Line bounds[];
} Player;
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
		- bounds: used to calculate collisions
*/
void DrawLineL(Line line, Color color);
const int screenWidth = 540;
const int screenHeight = 820;
const char* title = "chris game";

//void UpdatePlayer(Player* player, float delta);