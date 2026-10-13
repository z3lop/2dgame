#include "../include/player.h"
#include "../include/config.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <math.h>

void player_init(Player *player)
{
    player->body->width = 50.0f;
    player->body->height = 50.0f;

    player->body->x = 375.0f;
    player->body->y = GROUND_Y - player->body->height;

    player->velocity_x = 0.0f;
    player->velocity_y = 0.0f;
    
    player->on_ground = true;
    player->double_jump = false;
    player->wall_slide = false;

    player->riding_platform = -1;
    player->facing = 1;
}

void player_handle_event(
    Player *player,
    const SDL_Event *event
)
{
    if (event->type == SDL_KEYDOWN &&
        event->key.repeat == 0) {
        
        if (event->key.keysym.sym == SDLK_SPACE) {
        
            if (player->on_ground) {
                player->velocity_y = PLAYER_JUMP_VELOCITY;
                player->on_ground = false;
            }

            else if (!player->double_jump) {
                player->velocity_y = PLAYER_JUMP_VELOCITY;
                player->double_jump = true;
            }
        }
    }
}

void player_handle_input(Player *player) 
{
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    // Langsames Abschwellen der Geschwindigkeit
    if (fabs(player->velocity_x) < 1.0f) {
        player->velocity_x = 0.0f;
    }
    
    else if (player->velocity_x > 0.0f) {
        player->velocity_x -= 25.0f;
    }

    else if (player->velocity_x < 0.0f) {
        player->velocity_x += 25.0f;
    }

    if(keyboard[SDL_SCANCODE_A]) {
        player->velocity_x = -250.0f;
        player->facing = -1;
    }

    if(keyboard[SDL_SCANCODE_D]) {
        player->velocity_x = 250.0f;
        player->facing = 1;
    }
}

