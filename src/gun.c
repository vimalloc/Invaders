#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "sprite.h"
#include "bullet.h"
#include "gun.h"

/* How fast each of the various guns will be able to fire */
#define BASIC_GUN_SPEED 20

static gun_t* gun_init(int charge_rate, bullet_t* (*bullet_creator)(int, int, sprite_t*)) {
    gun_t* g;

    g = malloc(sizeof(gun_t));
    if(!g)
        system_error("malloc error in gun_init");

    g->recharge_rate = charge_rate;
    g->current_charge = 0;
    g->bullet_type = bullet_creator;

    return g;
}

gun_t* gun_player_basic() {
    return gun_init(BASIC_GUN_SPEED, &bullet_create_player_basic);
}

gun_t* gun_alien_basic() {
    return gun_init(BASIC_GUN_SPEED, &bullet_create_alien_basic);
}

void gun_free(gun_t *g) {
    assert(g);
    free(g);
}

bullet_t* gun_fire(int xpos, int ypos, gun_t *g) {
    bullet_t *b; /* The bullet this gun creates */

    assert(g);

    /* If the gun isn't charged yet, return null */
    if(g->current_charge)
        return NULL;

    g->current_charge = 1;
    b = g->bullet_type(xpos, ypos, sprite_get_basic_bullet());
    return b;
}

void gun_recharge(gun_t *g) {
    assert(g);

    if(g->current_charge != 0) {
        g->current_charge++;
        if(g->current_charge == g->recharge_rate)
            g->current_charge = 0;
    }
}
