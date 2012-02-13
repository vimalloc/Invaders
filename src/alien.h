#ifndef ALIEN_H
#define ALIEN_H

#include "ship.h"

/* Handle for all gun related stuff */
typedef struct {
    ship_t *ship; /* The ship this alien will be using */
} alien_t;

/* Creates and returns a basic alien ship */
alien_t* alien_basic_init();

/* Frees an alien ship */
void alien_free(alien_t *alien);

/*
 * TODO
 * AI
 *  Movement
 *  Firing
 * Health
 */

#endif

