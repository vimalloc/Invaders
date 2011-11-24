#include <assert.h>
#include <stdlib.h>

#include "ship.h"
#include "errors.h"

void ship_init(ship **s, sprite *sprite, int ship_speed, int gun_recharge) {
    assert(sprite);

    *s = malloc(sizeof(ship));
    if(!s)
        system_error("malloc error in ship_init");

    /* Create the gun this ship will use */
    gun_init(&((**s).gun), gun_recharge);

    /* Set the values for this ship */
    (**s).sprite = sprite;
    (**s).speed = ship_speed;
    (**s).xpos = 0;
    (**s).ypos = 0;
}

void ship_free(ship *s) {
    assert(s);
    gun_free(s->gun);
    free(s);
}

int ship_get_speed(ship *s) {
    assert(s);
    return s->speed;
}

int ship_get_width(ship *s) {
    assert(s);
    return sprite_width(s->sprite);
}

int ship_get_height(ship *s) {
    assert(s);
    return sprite_height(s->sprite);
}
