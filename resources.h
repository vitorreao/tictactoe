#include <SDL.h>

#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

struct game_resources;

struct game_resources *new_game_resources();

int load_game_resources(struct game_resources *gr);

void destroy_game_resources(struct game_resources *gr);

#endif /* GAME_RESOURCES_H */
