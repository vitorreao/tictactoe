#include <SDL.h>

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

struct game_board;

SDL_Rect *get_board_tile(int x, int y);
struct game_board *new_game_board();
void destroy_game_board(struct game_board *gb);

#endif /* GAME_BOARD_H */