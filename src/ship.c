#include <assert.h>
#include <stdlib.h>

#include "ship.h"
#include "errors.h"

int ship_init(ship **s, sprite *sprite, int ship_speed, int gun_recharge)
{
    int error;

    assert(sprite);

    *s = malloc(sizeof(ship));
    if(!s)
        return ERR_MALLOC;

    /* Create the gun this ship will use */
    error = gun_init(&((**s).gun), gun_recharge);
    if(error != HUGE_SUCCESS) {
        free(*s);
        return error;
    }

    /* Set the values for this ship */
    (**s).sprite = sprite;
    (**s).speed = ship_speed;
    (**s).xpos = 0;
    (**s).ypos = 0;

    return HUGE_SUCCESS;
}

void ship_free(ship *s)
{
    assert(s);
    gun_free(s->gun);
    free(s);
}

int ship_get_speed(ship *s)
{
    assert(s);
    return s->speed;
}

int ship_get_width(ship *s)
{
    return sprite_width(s->sprite);
}

int ship_get_height(ship *s)
{
    return sprite_height(s->sprite);
}
