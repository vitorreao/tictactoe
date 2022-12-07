#include <stdlib.h>
#include <SDL.h>

#include "board.h"

enum board_state {
	BOARD_STATE_UNDECIDED,
	BOARD_STATE_NOUGHT_WON,
	BOARD_STATE_CROSS_WON,
	BOARD_STATE_TIE,
};

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

enum tictactoe_player {
	PLAYER_NOUGHT,
	PLAYER_CROSS,
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
	enum tictactoe_player current_player;
	enum tictactoe_player board[9];
	enum board_state      state;
};

struct board_tile *get_board_tile(int x, int y)
{
	for (int i = 0; i < 9; i++) {
		int x1 = board_tiles[i].rect.x;
		int x2 = board_tiles[i].rect.x + board_tiles[i].rect.w;
		int y1 = board_tiles[i].rect.y;
		int y2 = board_tiles[i].rect.y + board_tiles[i].rect.h;
		if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
			return &board_tiles[i];
		}
	}
	return NULL;
}

enum board_state check_board_state_column(struct game_board *gb, int tile_value, int c)
{
	for (int i = c; i < 9; i += 3) {
		if (gb->board[i] != tile_value) return BOARD_STATE_UNDECIDED;
	}
	if (tile_value == PLAYER_CROSS) {
		return BOARD_STATE_CROSS_WON;
	} else if (tile_value == PLAYER_NOUGHT) {
		return BOARD_STATE_NOUGHT_WON;
	}
	return BOARD_STATE_UNDECIDED;
}

enum board_state check_board_state_line(struct game_board *gb, int tile_value, int l)
{
	for (int i = l; i < (l + 3); i++) {
		if (gb->board[i] != tile_value) return BOARD_STATE_UNDECIDED;
	}
	if (tile_value == PLAYER_CROSS) {
		return BOARD_STATE_CROSS_WON;
	} else if (tile_value == PLAYER_NOUGHT) {
		return BOARD_STATE_NOUGHT_WON;
	}
	return BOARD_STATE_UNDECIDED;
}

enum board_state check_board_state_diagonal(struct game_board *gb, int tile_value, int d, int step, int max)
{
	for (int i = d; i <= max; i += step) {
		if (gb->board[i] != tile_value) return BOARD_STATE_UNDECIDED;
	}
	if (tile_value == PLAYER_CROSS) {
		return BOARD_STATE_CROSS_WON;
	} else if (tile_value == PLAYER_NOUGHT) {
		return BOARD_STATE_NOUGHT_WON;
	}
	return BOARD_STATE_UNDECIDED;
}

void check_board_state(struct game_board *gb)
{
	int has_tiles_left = 0;
	for (int i = 0; i < 9; i++) {
		int tile_value = gb->board[i];
		if (tile_value < 0) {
			has_tiles_left = 1;
			continue;
		}
		if ((i % 3) == i) {
			gb->state = check_board_state_column(gb, tile_value, i);
		}
		if ((i % 3) == 0 && gb->state == BOARD_STATE_UNDECIDED) {
			gb->state = check_board_state_line(gb, tile_value, i);
		}
		if ((i == 0 || i == 2) && gb->state == BOARD_STATE_UNDECIDED) {
			int step = i == 0 ? 4 : 2;
			int max = i == 0 ? 8 : 6;
			gb->state = check_board_state_diagonal(gb, tile_value, i, step, max);
		}
		if (gb->state != BOARD_STATE_UNDECIDED) break;
	}
	if (!has_tiles_left && gb->state == BOARD_STATE_UNDECIDED) {
		gb->state = BOARD_STATE_TIE;
	}
}

void tictactoe_play(struct game_board *board, int x, int y)
{
	if (board->state != BOARD_STATE_UNDECIDED) return;
	struct board_tile *tile = get_board_tile(x, y);
	if (tile == NULL) return;
	int pos_value = board->board[tile->name];
	if (pos_value >= 0) {
		return;
	}
	board->board[tile->name] = board->current_player;
	board->current_player = (board->current_player + 1) % 2;
	check_board_state(board);
}

void tictactoe_draw_board(
	SDL_Renderer      *renderer,
	SDL_Texture       *board_texture,
	SDL_Texture       *nought_texture,
	SDL_Texture       *cross_texture,
	struct game_board *board)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, board_texture, NULL, NULL);

	for (int i = 0; i < 9; i++) {
		int board_value = board->board[i];
		if (board_value < 0) continue;
		struct board_tile tile = board_tiles[i];
		int x = tile.rect.x + (tile.rect.w / 2) - (165 / 2);
		int y = tile.rect.y + (tile.rect.h / 2) - (115 / 2);
		SDL_Rect dstrect = { x, y, 165, 115 };
		SDL_Texture *tile_texture = NULL;
		if (board_value == PLAYER_CROSS) {
			tile_texture = cross_texture;
		} else if (board_value == PLAYER_NOUGHT) {
			tile_texture = nought_texture;
		}
		if (tile_texture == NULL) continue;
		SDL_RenderCopy(renderer, tile_texture, NULL, &dstrect);
	}
}

struct game_board *new_game_board()
{
	struct game_board *gb = malloc(sizeof(struct game_board));
	for (int i = 0; i < 9; i++) {
		gb->board[i] = -1;
	}
	gb->current_player = PLAYER_CROSS;
	gb->state = BOARD_STATE_UNDECIDED;
	return gb;
}

void destroy_game_board(struct game_board *gb)
{
	free(gb);
}
