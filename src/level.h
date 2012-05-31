#ifndef LEVEL_H
#define LEVEL_H

#include "linked_list.h"
#include "bullet.h"

/* Forward declaration so we can have a pointer to a bullet_t in the struct */
typedef struct level_t level_t;
struct level_t {
    int complete;     /* Flag for if the level has been completed */
    int num_of_aliens; /* The number of aliens left in the level */
    ll_t *aliens;      /* List of all active aliens in this level */

    /* function pointer for the function which will create new
     * bullets for this level. This function will return a
     * linked list of new bullets that were fired */
    ll_t* (*fire_function)(level_t *level);
};


level_t* level_create_basic();

void level_free(level_t* level);

/* Takes a bullet and checks for any colisions. If a colision
 * did occure then the colision on the level (for example, an
 * alien being hit) will be handled, and 1 will be returned to
 * indicate that this bullet hit something. If no colision occurred,
 * 0 will be returned */
int level_process_colision(level_t *level, bullet_t *bullet);

/* Updates this level by one step, and returns a linked list
 * of new bullets that have been fired this step. If no new bullets
 * have been fired, then an empty list is returned
 *
 * Updating includes:
 * 1) Moving aliens
 * 2) Firing new bullets (from aliens, platforms, toweres, or whatever)
 * 3) Setting the completion of level flag if the level is over
 * 4) Any special events this level may have
 */
ll_t* level_update(level_t *level);

#endif

