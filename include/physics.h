#ifndef PHYSICS_H
#define PHYSICS_H

#include "player.h"
#include "world.h"

void physics_update_player(
    Player *player,
    const World *world,
    float dt
);

void world_update_moving_objects(
    World *world,
    float dt
);

#endif