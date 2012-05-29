#include <assert.h>
#include <stdio.h>

#include "bullet.h"
#include "errors.h"
#include "sprite.h"
#include "errors.h"

#define BASIC_DAMAGE 15

/* Should create the update function pointers here staticaly so that we we can
 * use the same function pointer for multiple bullets instead of creating a new
 * one for each bullet */
static void move_basic_player_bullet (bullet_t *b) {
    b->ypos -= 7;
}

static void move_basic_alien_bullet (bullet_t *b) {
    b->ypos += 7;
}

void bullet_update_position(bullet_t *b) {
    assert(b);
    b->move_bullet(b);
}


void bullet_free(bullet_t *bullet) {
    assert(bullet);
    free(bullet);
}

static bullet_t* bullet_create(int start_x, int start_y, sprite_t *sprite,
                        void (*bullet_movement_function)(bullet_t*)) {
    bullet_t *bullet;

    assert(sprite);

    /* Create memory for the bullet */
    bullet = malloc(sizeof(bullet_t));
    if(!bullet)
        system_error("malloc error in bullet_create_basic");

    /* Set all the attributes for this bullet */
    bullet->xpos = start_x;
    bullet->ypos = start_y;
    bullet->damage = BASIC_DAMAGE;
    bullet->sprite = sprite;

    /* Set the move bullet function pointer */
    bullet->move_bullet = bullet_movement_function;

    return bullet;
}

/* Creates a bullet which uses hte move_basic_player_bullet as the function
 * to update the bullets position */
bullet_t* bullet_create_player_basic(int start_x, int start_y, sprite_t *sprite) {
    return bullet_create(start_x, start_y, sprite, &move_basic_player_bullet);
}

/* Creates a bullet which uses hte move_basic_alien_bullet as the function
 * to update the bullets position */
bullet_t* bullet_create_alien_basic(int start_x, int start_y, sprite_t *sprite) {
    return bullet_create(start_x, start_y, sprite, &move_basic_alien_bullet);
}

int bullet_get_width(bullet_t *b) {
    return sprite_width(b->sprite);
}

int bullet_get_height(bullet_t *b) {
    return sprite_height(b->sprite);
}

