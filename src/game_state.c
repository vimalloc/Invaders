#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"
#include "ship.h"

int game_state_init(game_state **state, int xmax, int ymax)
{
    int error;
    sprite *player_sprite; /* will be owned by the game_state object */

    /* malloc this */
    *state = malloc(sizeof(game_state));
    if(!*state)
        return ERR_MALLOC;

    /* Load the sprite for the player ship */
    error = sprite_load_bmp(&player_sprite, "player.bmp");
    if(error != HUGE_SUCCESS) {
        free(*state);
        return error;
    }

    /* Load the players ship for this game. This sprite will now be owned
     * by this player ship */
    error = ship_init(&(**state).player_ship, player_sprite, 5);
    if(error != HUGE_SUCCESS) {
        free(*state);
        sprite_free(player_sprite);
        return error;
    }

    /* set default values */
    (**state).xmax = xmax;
    (**state).ymax = ymax;
    (**state).player_changed = 0;

    return HUGE_SUCCESS;
}

void game_state_free(game_state* state)
{
    assert(state);

    ship_free(state->player_ship);
    sprite_free(state->player_ship->sprite);
    free(state);
}

void game_state_move_up(game_state* state)
{
    ship *pship = state->player_ship;

    if(pship->ypos == 0)
        return;

    pship->ypos -= ship_get_speed(pship);

    if(pship->ypos < 0)
        pship->ypos = 0;

    state->player_changed = 1;
}

void game_state_move_down(game_state* state)
{
    ship *pship = state->player_ship;

    if(pship->ypos == state->ymax)
        return;

    pship->ypos += ship_get_speed(pship);

    if(pship->ypos > state->ymax)
        pship->ypos = state->ymax;

    state->player_changed = 1;
}

void game_state_move_left(game_state* state)
{
    ship *pship = state->player_ship;

    if(pship->xpos == 0)
        return;

    pship->xpos -= ship_get_speed(pship);

    if(pship->xpos < 0)
        pship->xpos = 0;

    state->player_changed = 1;
}

void game_state_move_right(game_state* state)
{
    ship *pship = state->player_ship;

    if(pship->xpos == state->xmax)
        return;

    pship->xpos += ship_get_speed(pship);

    if(pship->xpos > state->xmax)
        pship->xpos = state->xmax;

    state->player_changed = 1;
}
