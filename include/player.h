#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "camera.h"
#include "world.h"

typedef struct {
    WorldObject *body;

    float velocity_x;
    float velocity_y;

    bool double_jump;
    bool on_ground;

    int riding_platform;

    bool wall_slide;
    int facing;

} Player;

void player_init(Player *player);

void player_handle_event(
    Player *player,
    const SDL_Event *event
);

void player_handle_input(Player *player);

void player_render(
    const Player *player,
    const Camera *camera,
    SDL_Renderer *renderer
);

#endif