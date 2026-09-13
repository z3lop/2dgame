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

bool collision_player_left(
    const Player *player
)
{
    return
        player->x < 0.0f;
}



