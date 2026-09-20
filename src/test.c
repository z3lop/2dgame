#include "../include/world.h"

void world_update_moving_objects(
    World *world,
    float dt
)
{
    for (int i = 0; i < world->moving_count; i++) {

        MovingObject *object =
            &world->moving_objects[i];

        if (object->point_count <= 0) {
            continue;
        }

        SDL_FPoint target =
            object->path[object->next_point];

        float dx =
            target.x - object->object.x;

        float dy =
            target.y - object->object.y;

        float distance =
            sqrtf(dx * dx + dy * dy);


        /*
         * Bewegung dieses Frames zunächst zurücksetzen
         */
        object->delta_x = 0.0f;
        object->delta_y = 0.0f;


        /*
         * Ziel erreicht
         */
        if (distance <= 0.001f) {

            object->object.x = target.x;
            object->object.y = target.y;

            object->next_point++;

            if (object->next_point >= object->point_count) {

                if (object->loop) {
                    object->next_point = 0;
                }
                else {
                    object->next_point =
                        object->point_count - 1;
                }
            }

            continue;
        }


        float movement =
            object->speed * dt;


        /*
         * Ziel würde in diesem Frame überschritten werden
         */
        if (movement >= distance) {

            object->delta_x = dx;
            object->delta_y = dy;

            object->object.x = target.x;
            object->object.y = target.y;

            object->next_point++;

            if (object->next_point >= object->point_count) {

                if (object->loop) {
                    object->next_point = 0;
                }
                else {
                    object->next_point =
                        object->point_count - 1;
                }
            }

            continue;
        }


        /*
         * Richtungsvektor normalisieren
         */
        float direction_x = dx / distance;
        float direction_y = dy / distance;


        /*
         * Tatsächliche Bewegung dieses Frames
         */
        object->delta_x =
            direction_x * movement;

        object->delta_y =
            direction_y * movement;


        object->object.x += object->delta_x;
        object->object.y += object->delta_y;
    }
}