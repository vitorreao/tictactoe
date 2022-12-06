#include <SDL.h>

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

struct game_board;

struct game_board *new_game_board();
void destroy_game_board(struct game_board *gb);

void tictactoe_play(struct game_board *board, int x, int y);
void tictactoe_draw_board(
	SDL_Renderer      *renderer,
	SDL_Texture       *board_texture,
	SDL_Texture       *nought_texture,
	SDL_Texture       *cross_texture,
	struct game_board *board);

#endif /* GAME_BOARD_H */