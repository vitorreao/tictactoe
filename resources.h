#include <SDL.h>

#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#define RESOURCE_BOARD_IMAGE 0
#define RESOURCE_NOUGHT_IMAGE 1
#define RESOURCE_CROSS_IMAGE 2

struct game_resources;

struct game_resources *new_game_resources();

int load_game_resources(struct game_resources *gr, SDL_Renderer *renderer);

SDL_Texture *get_resource_texture(struct game_resources *gr, int texture_index);

void destroy_game_resources(struct game_resources *gr);

#endif /* GAME_RESOURCES_H */
