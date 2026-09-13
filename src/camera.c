#include "../include/camera.h"

void camera_init(
    Camera *camera,
    float width,
    float height
)
{
    camera->x = 0.0f;
    camera->y = height/2.0f;

    camera->width = width;
    camera->height= height;
}

void camera_update(
    Camera *camera,
    float target_x,
    float target_y,

    float world_width,
    float world_height
)
{
    camera->x = 
        target_x - camera->width / 2.0f;
    
    camera->y = 
        target_y - camera->height / 2.0f;

    if (camera->x < 0.0f) {
        camera->x = 0.0f;
    }

    if (camera->x + camera->width > world_width) {
        camera->x = 
            world_width - camera->width;
    }

    if (camera->y + camera->height > world_height) {
        camera->y = 
            world_height - camera->height;
    }
}