#include "game.h"

int main(void)
{
    Game game;

    if (!game_init(&game)) {
        return 1;
    }

    game_run(&game);

    game_cleanup(&game);

    return 0;
}