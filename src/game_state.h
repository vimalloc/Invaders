/*
 * game_state.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ship.h"
#include "linked_list.h"

/* Handle for the game state object */
typedef struct {
    ship_t *player_ship;    /* The player controlled ship */
    int player_move_up;     /* Indicates the player ship wants to move up */
    int player_move_down;   /* Indicates the player ship wants to move down */
    int player_move_left;   /* Indicates the player ship wants to move left */
    int player_move_right;  /* Indicates the player ship wants to move right */
    int player_fire;        /* Indicates the player ship wants to firing */
    ll_t *bullets;          /* Linked list of all currently active bullets */
} game_state_t;

/**
 * Initalizes everything needed for the game state
 *
 * @param state The game state being initalized
 * @return 0 on success, errcode (< 0) on failure
 */
void game_state_init(game_state_t **state);

/**
 * Frees all the memory used by the game state
 *
 * @param state The game state to free
 */
void game_state_free(game_state_t *state);

/**
 * Gets the deminisions of the game_state
 */
int game_state_get_width();
int game_state_get_height();

/**
 * Updates the game state by 1 step
 */
void game_state_update(game_state_t *state);

#endif
