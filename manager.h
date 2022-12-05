#include <SDL.h>
#include <SDL_image.h>

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

struct game_manager;

struct game_manager *init_game();
void run_game_loop(struct game_manager *gm);
void quit_game(struct game_manager *gm);

#endif /* GAME_MANAGER_H */