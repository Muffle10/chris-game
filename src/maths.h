#include <math.h>
void calcPlayerMovement(Player* player, Vector2 vertex){
    for (player->rect.x; player->rect.x < player->speed.x; player->speed.x++ ){
        player->rect.y = -1 * ((player->rect.x - vertex.x) * (player->rect.x - vertex.x)) + vertex.y;
    }
}
Vector2 calcVert(Player* player){
    Vector2 vertex = {(player->rect.x + player->speed.x)/ 2, player->rect.y + player->speed.y};
    return vertex;
}