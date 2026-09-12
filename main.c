#include <SDL2/SDL.h>
#include <stdbool.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Jump",
        800,
        600,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, Null);

    bool running = true;
    
    float x = 375.0f;
    float y = 500.0f;

    float velocity_y = 0.0f;
    float gravity = 1200.0f;
    float jump_velocity = -600.0f;

    float ground = 500.0f;

    Uint64 last_time = SDL_GetTicks();

    while (running) 
    {
        SDL_Event event;
        
        while(SDL_PolEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                if (event.key.key == SDLK_SPACE && y >= ground)
                {
                    velocity_y = jump_velocity;
                }
            }
        }
        
        Uint64 now = SDL_GetTicks();
        float dt = (now - last_time) / 1000.0f;
        last_time = now;

        velocity_y += gravity * dt;
        y += velocity_y * dt;

        if (y>ground) {
            y = ground;
            velocity_y = 0.0f;
        };

        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderClear(renderer);

        SDL_FRect ball = (
                x, 
                y, 
                50,
                50
        );

        SDL_RenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}














