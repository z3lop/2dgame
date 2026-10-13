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

bool collision_torch_object(
    WorldObject *torch,
    const WorldObject *object
)
{
    return
    torch->x < object->x + object->width &&
    torch->x + torch->width > object->x &&
    torch->y < object->y + object->height &&
    torch->y + torch->height > object-> y;
}

bool collision_player_left(
    const Player *player
)
{
    return
        player->x < 0.0f;
}



