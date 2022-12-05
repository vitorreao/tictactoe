#include <SDL.h>

#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#define RESOURCE_BOARD_IMAGE 0

struct game_resources;

struct game_resources *new_game_resources();

int load_game_resources(struct game_resources *gr, const SDL_PixelFormat *fmt);

SDL_Surface *get_surface(struct game_resources *gr, int surface_index);

void destroy_game_resources(struct game_resources *gr);

#endif /* GAME_RESOURCES_H */
