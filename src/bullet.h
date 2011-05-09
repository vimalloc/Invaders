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

X and Y position, function pointer, and bullet number stored inside the bullet
void bullet_update_position(bullet *b);
*/


/* Function to create different types of bullets, these will call hte bull_create functions bellow

void bullet_create_basic(int level);
void bullet_create_spread(int level);
void bullet_create_fast(int level);
void bullet_create_etc(int level);
*/


/* Need a way to create the initial bullet, based on the starting x an y position. This
   should be called by the bullet_create_ functions above

void bullet_creates(bullet **bullet[], number_of_bullets, start_x, start_y, sprite, update_function);
 */

#endif
