#include <SDL.h>
#include <stdio.h>

#include "manager.h"

int main(int argc, char* argv[])
{
	struct game_manager *gm = init_game();

	run_game_loop(gm);

	quit_game(gm);

	return 0;
}
