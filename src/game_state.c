#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"

int game_state_init(game_state* state, int xmax, int ymax)
{
    assert(state);

    state->player_ship = (ship *) malloc(sizeof(ship));
    if(state->player_ship == NULL)
        return ERR_MALLOC;

    state->xmax = xmax;
    state->ymax = ymax;

    return GAME_SUCCESS;
}

void game_state_free(game_state* state)
{
    assert(state);

    free(state->player_ship);
}

void game_state_move_up(game_state* state)
{
    if(state->player_ship->ypos == 0)
        return;

    state->player_ship->ypos -= 1;

    if(state->player_ship->ypos < 0)
        state->player_ship->ypos = 0;

    /* Mark that this ships position has changed */
}

void game_state_move_down(game_state* state)
{
    if(state->player_ship->ypos == state->ymax)
        return;

    state->player_ship->ypos += 1;

    if(state->player_ship->ypos > state->ymax)
        state->player_ship->ypos = state->ymax;

    /* Mark that this ships position has changed */
}

void game_state_move_left(game_state* state)
{
    if(state->player_ship->xpos == 0)
        return;

    state->player_ship->xpos -= 1;

    if(state->player_ship->xpos < 0)
        state->player_ship->xpos = 0;

    /* Mark that this ships position has changed */
}

void game_state_move_right(game_state* state)
{
    if(state->player_ship->xpos == state->xmax)
        return;

    state->player_ship->xpos += 1;

    if(state->player_ship->xpos > state->xmax)
        state->player_ship->xpos = state->xmax;

    /* Mark that this ships position has changed */
}
