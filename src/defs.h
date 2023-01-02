#define G 400
bool getCollision(Rectangle object1, Rectangle object2);
enum entity_type {ENEMY, PROJECTILE, PLATFORM};
typedef struct EnvEntity{
	Rectangle space;
} EnvEntity;
/*
	Line: Entities the player interacts with i.e: enemies, platforms
		- space: space the entity takes up
		- type: what type of enemy
*/
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
	float jumpVel;
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
const int screenWidth = 800;
const int screenHeight = 450;
const char* title = "chris game";

//void UpdatePlayer(Player* player, float delta);