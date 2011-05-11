#include <assert.h>
#include <stdio.h>

#include "bullet.h"
#include "errors.h"

/* Should create the update function pointers here staticaly so that we we can
 * use the same function pointer for multiple bullets instead of creating a new
 * one for each bullet */

void bullet_update_position(bullet *b)
{
    assert(b);

    /* Call the function pointer stored in b */
}

static int create_bullet(bullet **results[], int number_of_bullets, int start_x,
                         int start_y, sprite *sprite, funcion_pointer)
{
    int i;

    assert(sprite);

    /* Create space for the bullets */
    *results = malloc(sizeof(bullet) * number_of_bullets);

    for(i=0; i<number_of_bullets; i++) {
        (*results)[i]->xpos = start_x;
        (*results)[i]->ypos = start_y;
        (*results)[i]->sprite = sprite;
        (*results)[i]->bullet_number = i;
        /* set the function pointer */

        /* Call the function pointer first to move the bullet past the ship */
    }
}

int bullet_create_basic(bullet **results[], int number_of_bullets, int start_x,
                        int start_y, sprite *sprite)
{
    return create_bullet(results, number_of_bullets, start_x, start_y, sprite,
                         function_pointer);
}
