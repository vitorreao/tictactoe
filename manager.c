#include <stdlib.h>

#include "board.h"
#include "manager.h"
#include "resources.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct game_manager {
	struct game_resources *resources;
	struct game_board     *board;
	SDL_Window            *window;
	SDL_Renderer          *renderer;
};

int init_sdl_window_and_renderer(struct game_manager *gm);

struct game_manager *init_game()
{
	struct game_manager *gm = malloc(sizeof(struct game_manager));
	if (init_sdl_window_and_renderer(gm) < 0) {
		return NULL;
	}

	gm->resources = new_game_resources();
	int load_out = load_game_resources(gm->resources, gm->renderer);
	if (gm->resources == NULL || load_out < 0) {
		return NULL;
	}

	gm->board = new_game_board();
	if (gm->board == NULL) {
		return NULL;
	}

	return gm;
}

int init_sdl_window_and_renderer(struct game_manager *gm)
{
	SDL_Window   *game_window;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return -1;
	}

	game_window = SDL_CreateWindow(
		"TIC TAC TOE",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (game_window == NULL) {
		printf("Window could not be created! Error: %s\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_SOFTWARE);

	if (renderer == NULL) {
		printf("Renderer could not be created! Error: %s\n", SDL_GetError());
		return -1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	gm->window   = game_window;
	gm->renderer = renderer;

	return 0;
}

void run_game_loop(struct game_manager *gm)
{
	SDL_Texture *board_texture = get_resource_texture(gm->resources, RESOURCE_BOARD_IMAGE);
	SDL_Texture *nought_texture = get_resource_texture(gm->resources, RESOURCE_NOUGHT_IMAGE);
	SDL_Texture *cross_texture = get_resource_texture(gm->resources, RESOURCE_CROSS_IMAGE);
	SDL_Event event;

	while (1) {
		int has_event = SDL_WaitEvent(&event);
		if (has_event && event.type == SDL_QUIT) {
			break;
		}

		if (has_event && event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent mouse_event = event.button;
			if (mouse_event.button == SDL_BUTTON_LEFT) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				tictactoe_play(gm->board, x, y);
			}
		}

		tictactoe_draw_board(gm->renderer, board_texture, nought_texture, cross_texture, gm->board);

		SDL_RenderPresent(gm->renderer);
	}
}

void quit_game(struct game_manager *gm)
{
	destroy_game_resources(gm->resources);
	gm->resources = NULL;

	destroy_game_board(gm->board);
	gm->board = NULL;

	if (gm->renderer != NULL) {
		SDL_DestroyRenderer(gm->renderer);
	}
	gm->renderer = NULL;

	if (gm->window != NULL) {
		SDL_DestroyWindow(gm->window);
	}
	gm->window = NULL;

	IMG_Quit();
	SDL_Quit();

	free(gm);
}
