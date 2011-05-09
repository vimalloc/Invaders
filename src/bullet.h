#ifndef BULLET_H
#define BULLET_H

typedef struct {
    /* A function pointer to a movement algorithm for each bullet */
    /* This bullets xpos */
    /* This bullets ypos */
    /* A sprite for this bullet */
    /* Bullet number (in case more then one bullet was shot from the
     * same gun at a time, in which case we could use the bullet
     * numbers in conjunction with the update position algorithm so
     * that different bullets will go different ways */
} bullet;

/* Update this bullets x and y position */
/* Call the function pointer with the old x and y position, and get the
 * newly updated x and y positions */

/* FUNCTION POINTER SIGNITURE IDEA
void bullet_update_position(bullet *b, int *xpos, int *ypos, int bullet_number);
 */

#endif
