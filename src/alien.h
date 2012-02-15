#ifndef ALIEN_H
#define ALIEN_H

#include "ship.h"

/* Handle for all gun related stuff */
typedef struct {
    ship_t *ship; /* The ship this alien will be using */
    int health;
} alien_t;

/* Creates and returns a basic alien ship */
alien_t* alien_basic_init();

/* Frees an alien ship */
void alien_free(alien_t *alien);

/*
 * Processes damage dealt to an alien ship
 *
 * Returns 1 if the alien ship was destroyed, 0 otherwsie
 */
int alien_process_damage(alien_t *alien, int damage);

/*
 * TODO
 * AI
 *  Movement
 *  Firing
 * Health
 */

#endif

