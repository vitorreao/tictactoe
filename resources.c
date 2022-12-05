#include <stdlib.h>
#include <SDL_image.h>

#include "resources.h"

#define NUMBER_OF_RESOURCES 1

struct game_resources {
	SDL_Surface **surfaces;
};

struct game_resources *new_game_resources()
{
	return malloc(sizeof(struct game_resources));
}

SDL_Surface *load_png_image(const char *path, const SDL_PixelFormat *fmt)
{
	SDL_Surface *optimized_surface = NULL;

	SDL_Surface *file_surface = IMG_Load(path);
	if (file_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		return NULL;
	}

	optimized_surface = SDL_ConvertSurface(file_surface, fmt, 0);
	if (optimized_surface == NULL) {
		printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(file_surface);

	return optimized_surface;
}

int load_game_resources(struct game_resources *gr, const SDL_PixelFormat *fmt)
{
	gr->surfaces = malloc(sizeof(SDL_Surface *) * NUMBER_OF_RESOURCES);

	SDL_Surface *board_surface = load_png_image("assets/board.png", fmt);
	if (board_surface == NULL) {
		return -1;
	} else {
		gr->surfaces[RESOURCE_BOARD_IMAGE] = board_surface;
	}

	return 0;
}

SDL_Surface *get_surface(struct game_resources *gr, int surface_index)
{
	return gr->surfaces[surface_index];
}

void destroy_game_resources(struct game_resources *gr)
{
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		SDL_FreeSurface(gr->surfaces[i]);
		gr->surfaces[i] = NULL;
	}
	free(gr);
}
