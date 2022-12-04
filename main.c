#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[])
{
	SDL_Window* gameWindow;
	SDL_Renderer* renderer;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return 1;
	}

	gameWindow = SDL_CreateWindow(
		"Minimal SDL2",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (gameWindow == NULL) {
		printf("Window could not be created! Error: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(gameWindow, -1, 0);
	if (renderer == NULL) {
		printf("Renderer could not be created! Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	while (1) {
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		if (SDL_WaitEvent(&event) && event.type == SDL_QUIT) break;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();

	return 0;
}
