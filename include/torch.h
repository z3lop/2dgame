#ifndef TORCH_H
#define TORCH_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../include/player.h"
#include "../include/world.h"
#include "../include/config.h"

typedef enum {
    TORCH_FLYING,
    TORCH_RESTING,
} TorchState;

typedef struct {
    WorldObject body;

    float velocity_x;
    float velocity_y;

    TorchState state;

    float light_radius;
    float light_intensity;
    SDL_Color light_color;

    bool burning;
    int resting_platform;
} Torch;

typedef struct {
    Torch *items;
    int count;
    int capacity;
} TorchSystem;

bool torch_system_init(TorchSystem *system);
void torch_system_destroy(TorchSystem *system);

bool torch_throw(
    TorchSystem *system,
    const Player *player,
    int direction
);

void torch_update(
    TorchSystem *system,
    const World *world,
    float dt
);



#endif