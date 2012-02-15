#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"

/* Forward declaration so we can have a pointer to a bullet_t in the struct */
typedef struct bullet_t bullet_t;
struct bullet_t {
    int xpos;       /* This bullets xpos */
    int ypos;       /* This bullets ypos */
    sprite_t *sprite; /* A sprite for this bullet_t */

    /* A function pointer to a movement algorithm for each bullet_t */
    /* void movement_function_pointer(bullet *b); */
    void (*move_bullet)(bullet_t *b);
};

/**
 * Update this bullets x and y position by 1 tick
 */
void bullet_update_position(bullet_t *b);

/**
 * Frees the memory used by an array of bullets
 */
void bullet_free(bullet_t *bullet);

/**
 * Create basic bullets
 *
 * These are your basic bullets, which travel in a straight line one at a time.
 *
 * If this function fails to create a bullet_t object, it will close
 * the program.
 *
 * @param start_x The x position where these bullets are being 'fired' from
 * @param start_y The y position where these bullets are being 'fired' from
 * @param sprite The sprite that these bullets will use for drawning. Note that
 *               the sprite can be used for multiple bullets to save memory,
 *               so each bulle tdoes not own the sprite passed to it, and thus
 *               that sprite must be freed elseware
 *
 * @return 0 on success, error otherwise
 */
bullet_t* bullet_create_basic(int start_x, int start_y, sprite_t *sprite);

int bullet_get_height(bullet_t *b);
int bullet_get_width(bullet_t *b);

#endif
