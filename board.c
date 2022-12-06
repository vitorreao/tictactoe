#include <stdlib.h>
#include <SDL.h>

#include "board.h"


enum board_tile_name {
	BOARD_TILE_TOP_LEFT,
	BOARD_TILE_TOP_CENTER,
	BOARD_TILE_TOP_RIGHT,
	BOARD_TILE_CENTER_LEFT,
	BOARD_TILE_CENTER_CENTER,
	BOARD_TILE_CENTER_RIGHT,
	BOARD_TILE_BOTTOM_LEFT,
	BOARD_TILE_BOTTOM_CENTER,
	BOARD_TILE_BOTTOM_RIGHT,
};

struct board_tile {
	SDL_Rect             rect;
	enum board_tile_name name;
};

static struct board_tile board_tiles[] = {
	{ rect: {   5,   5, 180, 145 }, name: BOARD_TILE_TOP_LEFT      },
	{ rect: { 205,   5, 220, 145 }, name: BOARD_TILE_TOP_CENTER    },
	{ rect: { 445,   5, 190, 150 }, name: BOARD_TILE_TOP_RIGHT     },
	{ rect: {   5, 175, 185, 160 }, name: BOARD_TILE_CENTER_LEFT   },
	{ rect: { 210, 170, 220, 170 }, name: BOARD_TILE_CENTER_CENTER },
	{ rect: { 448, 175, 188, 162 }, name: BOARD_TILE_CENTER_RIGHT  },
	{ rect: {   5, 355, 185, 120 }, name: BOARD_TILE_BOTTOM_LEFT   },
	{ rect: { 210, 360, 220, 115 }, name: BOARD_TILE_BOTTOM_CENTER },
	{ rect: { 448, 358, 188, 115 }, name: BOARD_TILE_BOTTOM_RIGHT  },
};

struct game_board {

};

SDL_Rect *get_board_tile(int x, int y)
{
	for (int i = 0; i < 9; i++) {
		int x1 = board_tiles[i].rect.x;
		int x2 = board_tiles[i].rect.x + board_tiles[i].rect.w;
		int y1 = board_tiles[i].rect.y;
		int y2 = board_tiles[i].rect.y + board_tiles[i].rect.h;
		if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
			return &board_tiles[i].rect;
		}
	}
	return NULL;
}

struct game_board *new_game_board()
{
	return malloc(sizeof(struct game_board));
}

void destroy_game_board(struct game_board *gb)
{
	free(gb);
}
