#include "bullet.h"

void bullet_update_position(bullet *b)
{
    assert(b);

    /* Call the function pointer stored in b */
}

static int create_bullet(bullet **results[], int number_of_bullets, int start_x,
                         int start_y, sprite *sprite, funcion_pointer)
{

}

int bullet_create_basic(bullet **results[], int number_of_bullets, int start_x,
                        int start_y, sprite *sprite)
{
    /* Create the function pointer */

    return create_bullet(results, number_of_bullets, start_x, start_y, sprite,
                         function_pointer);
}
