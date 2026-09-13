#include "../include/collision.h"

bool collision_player_object(
    const Player *player, 
    const WorldObject *object
)
{
    return
        player->x < object->x + object->width &&
        player->x + player->width > object->x &&
        player->y < object->y + object->height &&
        player->y + player->height > object-> y;
}



