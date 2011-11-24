/*
 * Errors.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* used for strerror */

enum {
    HUGE_SUCCESS = 0,   /* I'm making a note here */
    ERR_MALLOC   = -1,  /* Malloc error */
    ERR_SDL      = -10, /* General error if something goes wrong with SDL */
    ERR_SDL_INIT = -11, /* Error with initialing SDL */
    ERR_SPRITE   = -12  /* Error regarding a SDL_Surface (sprite) */
};

/**
* Gets the string assosicated with this error code
*
* @param errcode The error code to get the string of
* @return A char* containging the string assosicated with this error code
*/
const char* err_string(int errcode);

void app_error(char *msg);
void system_error(char *msg);

#endif

