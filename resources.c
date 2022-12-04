#include <stdlib.h>

#include "resources.h"

struct game_resources {
};

struct game_resources *new_game_resources()
{
	return malloc(sizeof(struct game_resources));
}

int load_game_resources(struct game_resources *gr)
{
	return 0;
}

void destroy_game_resources(struct game_resources *gr)
{
	free(gr);
}
