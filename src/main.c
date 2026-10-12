#include "../include/game.h"

int main(void)
{
    Game *game = calloc(1, sizeof *game);

    if (game == NULL) {
        fprintf(stderr, "Could not allocate Game\n");
        return 1;
    }

    if (!game_init(game)) {
        free(game);
        return 1;
    }

    game_run(game);

    game_cleanup(game);
    free(game);

    return 0;
}