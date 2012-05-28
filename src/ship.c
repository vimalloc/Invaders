#include <assert.h>
#include <stdlib.h>

#include "ship.h"
#include "errors.h"

ship_t* ship_init(sprite_t *sprite, int ship_speed) {
    ship_t *s;

    assert(sprite);

    s = malloc(sizeof(ship_t));
    if(!s)
        system_error("malloc error in ship_init");

    /* Create the gun this ship will use */
    s->gun = gun_basic();

    /* Set the values for this ship */
    s->sprite = sprite;
    s->speed = ship_speed;
    s->xpos = 0;
    s->ypos = 0;

    return s;
}

void ship_free(ship_t *s) {
    assert(s);
    gun_free(s->gun);
    free(s);
}

int ship_get_speed(ship_t *s) {
    assert(s);
    return s->speed;
}

int ship_get_width(ship_t *s) {
    assert(s);
    return sprite_width(s->sprite);
}

int ship_get_height(ship_t *s) {
    assert(s);
    return sprite_height(s->sprite);
}

