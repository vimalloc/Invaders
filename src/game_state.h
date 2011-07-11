/*
 * game_state.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ship.h"

/* Handle for the game state object */
typedef struct {
    ship* player_ship;      /* The player controlled ship */
    int player_move_up;     /* Queue the player ship to move up */
    int player_move_down;   /* Queue the player ship to move down */
    int player_move_left;   /* Queue the player ship to move left */
    int player_move_right;  /* Queue the player ship to move right */
    int player_fire;        /* Queue the player ship for firing */
} game_state;

/**
 * Initalizes everything needed for the game state
 *
 * @param state The game state being initalized
 * @return 0 on success, errcode (< 0) on failure
 */
int game_state_init(game_state **state);

/**
 * Frees all the memory used by the game state
 *
 * @param state The game state to free
 */
void game_state_free(game_state* state);

/**
 * Gets the deminisions of the game_state
 */
int game_state_get_width();
int game_state_get_height();

/**
 * Updates the game state by 1 step
 */
void game_state_update(game_state *state);

#endif
