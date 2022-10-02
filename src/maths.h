#include <math.h>
void calcPlayerMovement(Player* player){
    float startingPos, currentPos, topHeight;
}
Vector2 calcVertex(float a, float b, float c){
    Vector2 v = {0, 0};
    v.x = -b / (2*a);
    v.y = (a * v.x * v.x) + (b * v.x) + c;
    return v;
}