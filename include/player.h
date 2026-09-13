#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;

    float width;
    float height;

    float velocity_x;
    float velocity_y;

    bool double_jump;
    bool on_ground;
} Player;

void player_init(Player *player);

void player_handle_event(
    Player *player,
    const SDL_Event *event
);

void player_handle_input(Player *player);

void player_render(
    const Player *player,
    SDL_Renderer *renderer
);

#endif