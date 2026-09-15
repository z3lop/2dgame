#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "camera.h"

typedef struct {
    float x;
    float y;

    float width;
    float height;

    float velocity_x;
    float velocity_y;

    bool double_jump;
    bool on_ground;

    bool wall_slide;
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