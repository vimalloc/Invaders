#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "gun.h"


void gun_init(gun_t **g, int charge_rate) {
    *g = malloc(sizeof(gun));
    if(!*g)
        system_error("malloc error in gun_init");

    (**g).recharge_rate = charge_rate;
    (**g).current_charge = 0;
}

void gun_free(gun_t *g) {
    assert(g);
    free(g);
}

void gun_fire(gun_t *g) {
    assert(g);

    if(g->current_charge == 0) {
        g->current_charge = 1;
        printf("%s\n", "PEW");
    }
}

void gun_recharge(gun_t *g) {
    assert(g);

    if(g->current_charge != 0) {
        g->current_charge++;
        if(g->current_charge == g->recharge_rate)
            g->current_charge = 0;
    }
}
