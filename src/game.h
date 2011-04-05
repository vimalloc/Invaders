/*
 * Game.h
 *
 * Authour: Landon Gilbert-Bland
 * Date: 1/3/2011
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h> /* Graphics/Audio library */

/* Hanlde for the game logic */
typedef struct {
    volatile int running; /* Controls starting and stopping of a game */
    SDL_Surface *surface; /* The surface where this game will be drawn */
    SDL_Event *event;     /* Event handler for SDL */
} game;


/**
 * Initalize the game
 *
 * @param g The game to initalize
 * @return 0 on success, errcode (< 0) on failure
 */
int game_init(game *g);


/**
 * Frees all the memory used by this game
 *
 * @param g The game to free
 */
void game_free(game *g);


/**
 * Starts running a new game (where the game loop is ran). Blocks until game
 * is over
 *
 * @param g The game to start
 * @return 0 on success, errcode (< 0) on failure
 */
int game_start(game *g);

#endif
