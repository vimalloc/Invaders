#include <stdlib.h> /* rand and srand */
#include <time.h>   /* seed for srand */

#include "level.h"
#include "errors.h"
#include "alien.h"
#include "bullet.h"


/*
 * Function used to check if any of the given aliens are
 * firing. This is used for the basic level
 */
static ll_t* basic_aliens_fire (level_t *level) {
    ll_t *new_bullets;
    bullet_t *bullet;
    ll_node_t *node;
    alien_t *alien;

    new_bullets = ll_init();
    node = ll_get_first_node(level->aliens);
    while(node) {
        alien = (alien_t*)ll_get_item(node);
        gun_recharge(alien->ship->gun);

        /* Randomly determin if a gun will attempt to fire */
        if((rand() % 100 + 1) == 1) {
            bullet = gun_fire(alien->ship->xpos, alien->ship->ypos, alien->ship->gun);
            if(bullet)
                ll_insert(new_bullets, (void *) bullet);
        }

        node = ll_next_node(level->aliens, node);
    }

    return new_bullets;
}

level_t* level_create_basic() {
    int i, j; /* loop counters */
    level_t *level;
    alien_t *alien;

    /* This is used for random bullet generation. We don't want to seed
     * it in the actual fire_function, because we update fast enough
     * that if we use the time as a seed we often see the same seed
     * used over multiple ticks */
    srand(time(NULL));

    level = malloc(sizeof(level_t));
    if(!level)
        system_error("Malloc error in level_create_basic");

    level->complete = 0;
    level->num_of_aliens = 40;
    level->aliens = ll_init();
    level->fire_function = &basic_aliens_fire;

    /* Create the aliens on the screen */
    for(i=0; i<10; i++) {
        for(j=0; j<4; j++) {
            alien = alien_basic_init(40 + (i * 60), 45 + (j * 50));
            ll_insert(level->aliens, (void *)alien);
        }
    }

    return level;
}

void level_free(level_t* level) {
    ll_node_t *node;

    /* Free all of the aliends in the linked list, then the list itself */
    node = ll_get_first_node(level->aliens);
    while(node) {
        alien_free((alien_t *) ll_get_item(node));
        node = ll_remove(level->aliens, node);
    }
    ll_free(level->aliens);

    free(level);
}

/*
 * Checks if this bullet colided with anything in this level. If a colision
 * does a occure, the we will process it, and return 1. If no colision
 * occurres we will return 0.
 */
int level_process_colision(level_t *level, bullet_t *bullet) {
    /*
     * This is based on Charles Brentana's answer this stack overflow question:
     * http://stackoverflow.com/questions/306316
     *
     * For visualization see: http://silentmatt.com/rectangle-intersection/
     */

    /*
     * bx1 = bullets x position
     * bx2 = bullets x position + bullet width
     * by1 = bullets y position
     * by2 = bullets y position + bullet height
     * sx1 = alien x posision
     * sx2 = alien x position + alien width
     * sy1 = alien y position
     * sy2 = alien y position + alien height
     */
    int bx1, bx2, by1, by2, sx1, sx2, sy1, sy2;
    ll_node_t *node;      /* Current node of a linked list */
    alien_t *alien;       /* The alien we are proccess colisions on */

    /* Get the poisionts of the bullets */
    bx1 = bullet->xpos;
    bx2 = bx1 + bullet_get_width(bullet);
    by1 = bullet->ypos;
    by2 = by1 + bullet_get_height(bullet);

    /* Process all of the aliens */
    node = ll_get_first_node(level->aliens);
    while(node) {
        /* Get everything from the alien ship being processed */
        alien = (alien_t *)ll_get_item(node);
        sx1 = alien->ship->xpos;
        sx2 = sx1 + ship_get_width(alien->ship);
        sy1 = alien->ship->ypos;
        sy2 = sy1 + ship_get_height(alien->ship);

        /* Check for a colision */
        if(bx1 < sx2 && bx2 > sx1 && by1 < sy2 && by2 > sy1) {
            if(alien_process_damage(alien, bullet->damage)) {
                ll_remove(level->aliens, node);
                alien_free(alien);
                level->num_of_aliens--;
            }
            return 1;
        }
        node = ll_next_node(level->aliens, node);
    }

    return 0;
}

ll_t* level_update(level_t *level) {
    if(level->num_of_aliens == 0)
        level->complete = 1;

    return level->fire_function(level);
}

