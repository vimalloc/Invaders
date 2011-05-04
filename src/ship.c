#include <assert.h>
#include <stdlib.h>

#include "ship.h"
#include "errors.h"

int ship_init(ship **s, sprite *sprite, int speed)
{
    assert(sprite);

    *s = malloc(sizeof(ship));
    if(!s)
        return ERR_MALLOC;

    (*s)->sprite = sprite;
    (*s)->speed = speed;
    (*s)->xpos = 0;
    (*s)->ypos = 0;

    return HUGE_SUCCESS;
}

void ship_free(ship *s)
{
    assert(s);
    free(s);
}

int ship_get_speed(ship *s)
{
    assert(s);
    return s->speed;
}
