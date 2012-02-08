#include <assert.h>
#include <stdio.h>

#include "bullet.h"
#include "errors.h"
#include "sprite.h"
#include "errors.h"

/* Should create the update function pointers here staticaly so that we we can
 * use the same function pointer for multiple bullets instead of creating a new
 * one for each bullet */
static void move_basic_bullet (bullet_t *b) {
    b->ypos -= 5;
}

void bullet_update_position(bullet_t *b) {
    assert(b);
    /* b->(*move_bullet)(b); */
}


void bullet_free(bullet_t *bullet) {
    assert(bullet);
    free(bullet);
}


bullet_t* bullet_create_basic(int start_x, int start_y, sprite_t *sprite) {
    bullet_t *bullet;

    assert(sprite);

    /* Create memory for the bullet */
    bullet = malloc(sizeof(bullet_t));
    if(!bullet)
        system_error("malloc error in bullet_create_basic");

    /* Set all the attributes for this bullet */
    bullet->xpos = start_x;
    bullet->ypos = start_y;
    bullet->sprite = sprite;

    /* Call the function pointer first to move the bullet past the ship */
    bullet->move_bullet = &move_basic_bullet;

    return bullet;
}

