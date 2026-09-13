#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float x;
    float y;

    float width;
    float height;
} Camera;

void camera_init(
    Camera *camera,
    float width, 
    float height
);

void camera_update(
    Camera *camera,
    float target_x,
    float target_y,

    float world_width,
    float world_height
);

#endif