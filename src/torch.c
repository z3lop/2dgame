#include "../include/torch.h"
#include "../include/collision.h"
#include "../include/config.h"

bool torch_system_init(TorchSystem *system)
{
    system->count = 0;
    system->capacity = MAX_TORCHES;

    system->items = calloc(
        system->capacity,
        sizeof *system->items
    );

    if (system->items == NULL) {
        system->capacity = 0;
        return false;
    }

    return true;
}

void torch_system_destroy(TorchSystem *system)
{
    free(system->items);

    system->items = NULL;

    system->count = 0;
    system->capacity = 0;
}

bool torch_throw(
    TorchSystem *system,
    const Player *player,
    int direction
)
{
    if (system->count >= system->capacity) {
        return false;
    }

    if (direction != -1 && direction != 1) {
        return false;
    }

    Torch *torch = &system->items[system->count];

    *torch = (Torch){0};

    torch->body.width = 18.0f;
    torch->body.height = 10.0f;

    torch->body.x =
        player->body->x + player->body->width / 2.0f
        - torch->body.width / 2.0f
        + direction * 30.0f;

    torch->body.y =
        player->body->y + player->body->height / 2.0f;

    torch->velocity_x =
        direction * TORCH_THROW_SPEED;

    torch->velocity_y =
        TORCH_UPWARD_SPEED;

    torch->state = TORCH_FLYING;
    torch->resting_platform = -1;

    torch->burning = true;

    torch->light_radius = 220.0f;
    torch->light_intensity = 1.0f;

    torch->light_color = (SDL_Color){
        255, 190, 100, 255
    };

    system->count++;

    return true;
}

void torch_update(
    TorchSystem *system,
    const World *world, 
    float dt
) 
{
    for (int i = 0; i < system->count; i++) {
        Torch *torch = &system->items[i];

        if (torch->state == TORCH_RESTING) {
            continue;
        }

        torch->velocity_y += TORCH_GRAVITY * dt;

        torch->body.x += torch->velocity_x * dt; 
        torch->body.y += torch->velocity_y * dt;
        

        for (int j = 0; j < world->object_count; j++) {
            const WorldObject *object = &world->objects[j];

            if (!collision_torch_object(&torch->body, object)) {
                continue;
            }

            // Bei Kollision Player verschieben
            if (torch->velocity_x > 0.0f) {
                torch->body.x = object->x - torch->body.width;

                torch->velocity_x = 0.0f;
            }
            else if (torch->velocity_x < 0.0f) {
                torch->body.x = object->x + object->width;

                torch->velocity_x = 0.0f;
            }

            if (torch->velocity_y > 0.0f) {
                torch->body.y = object->y - torch->body.height;

                torch->velocity_y = 0.0f;
                torch->state = TORCH_RESTING;

            } 
            
            // Spieler stößt gegen Objekt
            if (torch->velocity_y < 0.0f) {

                torch->body.y =
                    object->y + object->height;

                torch->velocity_y = 0.0f;
            }


        }


    }
}