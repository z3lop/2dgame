#include "../include/render.h"
#include <SDL2/SDL_render.h>

static void render_world(
    SDL_Renderer *renderer,
    const World *world,
    const Camera *camera
);

static void render_player(
    SDL_Renderer *renderer,
    const Player *player,
    const Camera *camera
);

void render_frame(
    SDL_Renderer *renderer, 
    const Player *player, 
    const World *world, 
    const Camera *camera
)
{
    // Hintergrund
    SDL_SetRenderDrawColor(
        renderer,
        30, 30, 40, 255
    );

    // Alten Frame löschen
    SDL_RenderClear(renderer);

    render_world(renderer, world, camera);

    //Player
    render_player(
        renderer,
        player, 
        camera
    );

    SDL_RenderPresent(renderer);

}

static void render_world(
    SDL_Renderer *renderer,
    const World *world,
    const Camera *camera
)
{
    SDL_SetRenderDrawColor(
        renderer, 
        100, 200, 100, 255
    );

    for (int i = 0; i < world->object_count; i++) {
        const WorldObject *object = &world->objects[i];

        SDL_FRect rect = {
            object->x - camera->x, 
            object->y - camera->y / 3.0f,
            object->width,
            object->height
        };

        SDL_RenderFillRectF(renderer, &rect);
    }
}

static void render_player(
    SDL_Renderer *renderer,
    const Player *player, 
    const Camera *camera
)
{
    SDL_FRect player_rect = {
        player->x - camera->x,
        player->y - camera->y / 3.0f,
        player->width,
        player->height
    };

    SDL_SetRenderDrawColor(
        renderer, 
        255, 100, 100, 255
    );

    SDL_RenderFillRectF(
        renderer,
        &player_rect
    );
}