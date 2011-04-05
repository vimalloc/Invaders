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
    ship* player_ship; /* The player controlled ship */
    int xmax;          /* The max x position on the playing grid */
    int ymax;          /* The max y position on the playing grid */
} game_state;

/**
 * Initalizes everything needed for the game state
 *
 * @param state The game state being initalized
 * @return 0 on success, errcode (< 0) on failure
 */
int game_state_init(game_state* state);

/**
 * Frees all the memory used by the game state
 *
 * @param state The game state to free
 */
void game_state_free(game_state* state);

/* TODO - Get a list of every ship that has changed and needs to be redrawn */

#endif
