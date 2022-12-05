#include <stdlib.h>
#include <SDL_image.h>

#include "resources.h"

#define NUMBER_OF_RESOURCES 1

struct game_resources {
	SDL_Texture **textures;
};

struct game_resources *new_game_resources()
{
	return malloc(sizeof(struct game_resources));
}

SDL_Texture *load_png_image(const char *path, SDL_Renderer *renderer)
{
	SDL_Texture *texture = NULL;

	SDL_Surface *file_surface = IMG_Load(path);
	if (file_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, file_surface);
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(file_surface);

	return texture;
}

int load_game_resources(struct game_resources *gr, SDL_Renderer *renderer)
{
	gr->textures = malloc(sizeof(SDL_Texture *) * NUMBER_OF_RESOURCES);

	SDL_Texture *board_texture = load_png_image("assets/board.png", renderer);
	if (board_texture == NULL) {
		return -1;
	} else {
		gr->textures[RESOURCE_BOARD_IMAGE] = board_texture;
	}

	return 0;
}

SDL_Texture *get_resource_texture(struct game_resources *gr, int texture_index)
{
	return gr->textures[texture_index];
}

void destroy_game_resources(struct game_resources *gr)
{
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		SDL_DestroyTexture(gr->textures[i]);
		gr->textures[i] = NULL;
	}
	free(gr);
}
