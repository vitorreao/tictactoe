#include <stdlib.h>

#include "board.h"

struct game_board {

};

struct game_board *new_game_board()
{
    return malloc(sizeof(struct game_board));
}

void destroy_game_board(struct game_board *gb)
{
    free(gb);
}
