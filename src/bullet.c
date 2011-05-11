#include <assert.h>
#include <stdio.h>

#include "bullet.h"
#include "errors.h"

/* Should create the update function pointers here staticaly so that we we can
 * use the same function pointer for multiple bullets instead of creating a new
 * one for each bullet */
static void move_basic_bullet (bullet *b)
{
    b->ypos -= 5;
}

void bullet_update_position(bullet *b)
{
    assert(b);

    /* Call the function pointer stored in b */
    b->(*move_bullet) (b);
}


void bullet_free(bullet *bullets[])
{
    assert(bullets);
    free(bullets);
}


static int create_bullet(bullet **results[], int number_of_bullets, int start_x,
                         int start_y, sprite *sprite, void(*move_bullet)(bullet *b))
{
    int i;

    assert(sprite);

    /* Create space for the bullets */
    *results = malloc(sizeof(bullet) * number_of_bullets);

    /* Create all of the bullets */
    for(i=0; i<number_of_bullets; i++) {
        /* TODO - initially space the bullets out here depending on how many
         * bullets there are */

        /* Set all the attributes for this bullet */
        (*results)[i]->xpos = start_x;
        (*results)[i]->ypos = start_y;
        (*results)[i]->sprite = sprite;
        (*results)[i]->bullet_number = i;
        (*results)[i]->move_bullet = move_bullet;

        /* Call the function pointer first to move the bullet past the ship */
        (*results)[i]->(*move_bullet) ((*results)[i]);
    }
}

int bullet_create_basic(bullet **results[], int number_of_bullets, int start_x,
                        int start_y, sprite *sprite)
{
    void (*move_bullet)(bullet *b) = &move_basic_bullet;

    return create_bullet(results, number_of_bullets, start_x, start_y, sprite,
                         move_bullet);
}
