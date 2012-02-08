#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "sprite.h"
#include "bullet.h"
#include "gun.h"

static void gun_init(gun_t **g, int charge_rate) {
    *g = malloc(sizeof(gun_t));
    if(!*g)
        system_error("malloc error in gun_init");

    (**g).recharge_rate = charge_rate;
    (**g).current_charge = 0;
}

gun_t* gun_basic() {
    gun_t *basic_gun;

    gun_init(&basic_gun, 20);
    return basic_gun;
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
    b = bullet_create_basic(xpos, ypos, sprite_get_basic_bullet());
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
