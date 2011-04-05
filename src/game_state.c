#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"

int game_state_init(game_state* state)
{
    assert(state);

    state->player_ship = (ship *) malloc(sizeof(ship));
    if(state->player_ship == NULL)
        return ERR_MALLOC;

    return GAME_SUCCESS;
}

void game_state_Free(game_state* state)
{
    assert(state);

    free(state->player_ship);
}
