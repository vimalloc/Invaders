/*
 * Errors.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef ERRORS_H
#define ERRORS_H

enum {
    GAME_SUCCESS = 0,   /* Successful operation */
    ERR_MALLOC   = -1,  /* Malloc error */
    ERR_SDL      = -10, /* General error if something goes wrong with SDL */
    ERR_SDL_INIT = -11, /* Error with initialing SDL */
};

#endif
