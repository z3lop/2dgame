#include "../include/render.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

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

void render_text(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    float x,
    float y
)
{
    SDL_Color color = {
        255, 255, 255, 255
    };

    SDL_Surface *surface = 
        TTF_RenderUTF8_Blended(font, text, color);

    if (!surface) {return;}

    SDL_Texture *texture = 
        SDL_CreateTextureFromSurface(
            renderer, surface
        );

    SDL_FRect dst = {
        x, y,
        (float)surface->w,
        (float)surface->h
    };

    SDL_RenderCopyF(
        renderer,
        texture,
        NULL,
        &dst
    );

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render_game_over(
    SDL_Renderer *renderer,
    TTF_Font *title_font,
    TTF_Font *text_font
) 
{

    /*
    SDL_SetRenderDrawColor(
        renderer, 
        20, 20, 20, 255
    );
    

    SDL_RenderClear(renderer);
    */

    // Color of GAME OVER Box
    SDL_SetRenderDrawColor(
        renderer,
        138, 36, 36, 255
    );

    SDL_FRect box = {
        200.0f,
        200.0f,
        400.0f,
        200.0f
    };

    SDL_RenderFillRectF(
        renderer, &box);


    // Draw Box to indicate R key
    SDL_SetRenderDrawColor(
        renderer,
        74, 38, 38, 255
    );

    SDL_FRect box1 = {
        300.0f,
        302.0f,
        23.0f,
        30.0f
    };

    SDL_RenderFillRectF(
        renderer, &box1);


    // Draw Box to indicate ESC key
    SDL_SetRenderDrawColor(
        renderer,
        74, 38, 38, 255
    );

    SDL_FRect box2 = {
        300.0f,
        352.0f,
        50.0f,
        30.0f
    };

    SDL_RenderFillRectF(
        renderer, &box2);

    
    render_text(
        renderer, title_font,
        "GAME OVER",
        270.0f, 200.0f
    );

    render_text(
        renderer, text_font,
        "Press R to restart",
        220.0f, 300.0f
    );

    render_text(
        renderer, text_font,
        "Press ESC to end the game",
        220.0f, 350.0f
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
            object->y - camera->y,
            object->width,
            object->height
        };

        SDL_RenderFillRectF(renderer, &rect);
    }

    for (int i = 0; i < world->moving_count; i++) {
        const MovingObject *moving_object =
            &world->moving_objects[i];
        
        SDL_FRect rect = {
            moving_object->object.x - camera->x,
            moving_object->object.y - camera->y,
            moving_object->object.width,
            moving_object->object.height

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
        player->y - camera->y,
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