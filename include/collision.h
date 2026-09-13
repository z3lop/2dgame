#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "player.h"
#include "world.h"

bool collision_player_object(
    const Player *player,
    const WorldObject *object
);

#endif