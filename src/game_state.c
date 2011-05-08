#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"
#include "ship.h"
#include "gun.h"

/* Game state information */
enum {
    /* Width of the screen for the playable game area */
    GAME_WIDTH = 640,

    /* Height of the screen for the playable game area */
    GAME_HEIGHT = 480,

    /* How many pixels the player moves per update */
    PLAYER_SPEED = 4,

    /* How fast the players gun recharges (counted in game updates) */
    PLAYER_GUN_RECHARGE = 20,
};


int game_state_init(game_state **state)
{
    int error;
    int ship_height;
    int ship_width;
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
    error = ship_init(&(**state).player_ship, player_sprite,
            PLAYER_SPEED, PLAYER_GUN_RECHARGE);
    if(error != HUGE_SUCCESS) {
        free(*state);
        sprite_free(player_sprite);
        return error;
    }

    /* Center the ships position on the game board */
    ship_height = ship_get_height((**state).player_ship);
    ship_width = ship_get_width((**state).player_ship);
    (**state).player_ship->ypos = GAME_HEIGHT - ship_height;
    (**state).player_ship->xpos = (GAME_WIDTH + ship_width) / 2;

    /* Set the queues to zero by default */
    (**state).player_move_up = 0;
    (**state).player_move_down = 0;
    (**state).player_move_left = 0;
    (**state).player_move_right = 0;
    (**state).player_fire = 0;

    return HUGE_SUCCESS;
}


void game_state_free(game_state* state)
{
    assert(state);

    ship_free(state->player_ship);
    sprite_free(state->player_ship->sprite);
    free(state);
}


int game_state_get_width()
{
    return GAME_WIDTH;
}


int game_state_get_height()
{
    return GAME_HEIGHT;
}


static void move_ship_up(ship *ship)
{
    ship->ypos -= ship_get_speed(ship);
    if(ship->ypos < 0)
        ship->ypos = 0;
}

static void move_ship_down(ship *ship)
{
    ship->ypos += ship_get_speed(ship);
    if(ship->ypos + ship_get_height(ship) > GAME_HEIGHT)
        ship->ypos = GAME_HEIGHT - ship_get_height(ship);
}


static void move_ship_left(ship *ship)
{
    ship->xpos -= ship_get_speed(ship);
    if(ship->xpos < 0)
        ship->xpos = 0;
}


static void move_ship_right(ship *ship)
{
    ship->xpos += ship_get_speed(ship);
    if(ship->xpos + ship_get_width(ship) > GAME_WIDTH)
        ship->xpos = GAME_WIDTH - ship_get_width(ship);
}

static void process_player_actions(game_state *state)
{
    if(state->player_move_up)
        move_ship_up(state->player_ship);

    if(state->player_move_down)
        move_ship_down(state->player_ship);

    if(state->player_move_left)
        move_ship_left(state->player_ship);

    if(state->player_move_right)
        move_ship_right(state->player_ship);

    if(state->player_fire)
        gun_fire(state->player_ship->gun);
}

static void update_gun_charge(game_state *state)
{
    gun_recharge(state->player_ship->gun);
}

void game_state_update(game_state *state)
{
    /* Update the guns recharge */
    update_gun_charge(state);

    /* Process player actions */
    process_player_actions(state);

    /* Process gun fire movement */

    /* Process alien movement */
}
