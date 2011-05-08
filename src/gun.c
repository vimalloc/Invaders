#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "gun.h"


int gun_init(gun **g, int recharge_rate)
{
    *g = malloc(sizeof(gun));

    (**g).recharge_rate = recharge_rate;
    (**g).current_charge = 0;

    return HUGE_SUCCESS;
}

void gun_free(gun *g)
{
    assert(g);
    free(g);
}

void gun_fire(gun *g)
{
    assert(g);

    if(g->current_charge == 0) {
        printf("%s\n", "PEW");
        g->current_charge = 1;
    }
}

void gun_recharge(gun *g)
{
    assert(g);

    if(g->current_charge) {
        g->current_charge = g->current_charge + 1;
        if(g->current_charge == g->recharge_rate);
            g->current_charge = 0;
    }
}
