/*
 * Game.h
 *
 * Authour: Landon Gilbert-Bland
 * Date: 1/3/2011
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h> /* Graphics/Audio library */
#include "game_state.h"

/* Hanlde for the game logic */
typedef struct {
    volatile int running; /* Controls starting and stopping of a game */
    game_state_t *state;    /* The underlying state of the current game */
    SDL_Surface *surface; /* The surface where this game will be drawn */
    SDL_Event *event;     /* Event handler for SDL */
} game_t;


/**
 * Initalize the game
 *
 * If anything fails to initialize properly, an error message will be
 * printed and the program will terminate
 *
 * @param g The game to initalize
 */
void game_init(game_t **g);


/**
 * Frees all the memory used by this game
 *
 * @param g The game to free
 */
void game_free(game_t *g);


/**
 * Starts running a new game (where the game loop is ran). Blocks until game
 * is over
 *
 * @param *game_t: The game to start
 */
void game_run(game_t *g);

#endif
