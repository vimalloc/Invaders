/*
 * Ship.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef SHIP_H
#define SHIP_H

#include "sprite.h"

/* Handle for a ship */
typedef struct {
    int xpos;
    int ypos;
    int speed;
    sprite *sprite;
} ship;

/**
 * Initializes a ship object
 *
 * @param s The ship to initialize
 * @param sprite An initialized sprite structure to be used for this ship. Note
 * that this sprite is designed to be used with multiple ships, and thus is not
 * owned by the ship, and will not get freeded when ship_free is called.
 * @return 0 on success, error (< 0) if failure
 */
int ship_init(ship **s, sprite *sprite, int speed);

/**
 * Frees all the memory used by a ship
 *
 * Note that the sprite passed into this ship is not freeded by this method.
 * This is designed so that many ships can use the same sprite to save memory,
 * and thus the sprite is owned seperatally and should be freed from there to
 * avoid possible double freeing issues.
 *
 * @param s The ship to free
 */
void ship_free(ship *s);

/**
 * @brief Returns the movement speed of a ship
 *
 * @param s The ship to get the speed of
 * @return The speed of the passed in ship
 */
int ship_get_speed(ship *s);

#endif
