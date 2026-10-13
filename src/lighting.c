#include <SDL2/SDL_surface.h>
#include <math.h>

#include "../include/lighting.h"
#include "../include/config.h"


static SDL_Texture *create_radial_texture(SDL_Renderer *renderer) 
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(
        0, 
        LIGHT_TEXTURE_SIZE, 
        LIGHT_TEXTURE_SIZE, 
        32, 
        SDL_PIXELFORMAT_RGBA8888);
    
    

}




