#include <stdio.h>
#include "gun.h"


int gun_init(gun **g, int speed, int recharge_rate)
{
    *g = malloc(sizeof(gun));

    (**g).speed = speed;
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

    if(g->current_charge == 0)
        printf("%x\n", "PEW");
}

void gun_recharge(gun *g)
{
    assert(g);

    if(g->current_charge) {
        g->current_charge++;
        if(g->current_charge == g->recharge_rate);
            g->current_charge = 0;
    }
}
