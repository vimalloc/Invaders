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
    ship* player_ship;  /* The player controlled ship */
    int player_changed; /* Tracks if the players ship has changed */
    int xmax;           /* The max x position on the playing grid */
    int ymax;           /* The max y position on the playing grid */
} game_state;

/**
 * Initalizes everything needed for the game state
 *
 * @param state The game state being initalized
 * @param xmax The maximum x position for this game
 * @param ymax The maximum y position for this game
 * @return 0 on success, errcode (< 0) on failure
 */
int game_state_init(game_state* state, int xmax, int ymax);

/**
 * Frees all the memory used by the game state
 *
 * @param state The game state to free
 */
void game_state_free(game_state* state);

/**
 * Functions for moving the players ship
 *
 * @param state The game state to move the ship on
 */
void game_state_move_up(game_state* state);
void game_state_move_down(game_state* state);
void game_state_move_left(game_state* state);
void game_state_move_right(game_state* state);

#endif
