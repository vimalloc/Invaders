#ifndef LEVEL_H
#define LEVEL_H

#include "linked_list.h"
#include "bullet.h"

/* Forward declaration so we can have a pointer to a bullet_t in the struct */
typedef struct {
    int complete;     /* Flag for if the level has been completed */
    int num_of_aliens; /* The number of aliens left in the level */
    ll_t *aliens;      /* List of all active aliens in this level */
} level_t;

level_t* level_create_basic();

void level_free(level_t* level);

/* Takes a bullet and checks for any colisions. If a colision
 * did occure then the colision on the level (for example, an
 * alien being hit) will be handled, and 1 will be returned to
 * indicate that this bullet hit something. If no colision occurred,
 * 0 will be returned */
int level_process_colision(level_t *level, bullet_t *bullet);

#endif

