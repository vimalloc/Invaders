#ifndef BULLET_H
#define BULLET_H

typedef struct {
    int xpos;       /* This bullets xpos */
    int ypos;       /* This bullets ypos */
    sprite *sprite; /* A sprite for this bullet */

    /* A function pointer to a movement algorithm for each bullet */
    /* void movement_function_pointer(bullet *b); */
    int (*move_bullet)(bullet *b);

    /* Bullet number (in case more then one bullet was shot from the
     * same gun at a time, in which case we could use the bullet
     * numbers in conjunction with the update position algorithm so
     * that different bullets will go different ways */
    int bullet_number;
} bullet;

/** 
 * Update this bullets x and y position by 1 tick
 */
void bullet_update_position(bullet *b);

/**
 * Frees the memory used by an array of bullets
 */
void bullet_free(bullet *bullets[]);

/** 
 * Create basic bullets
 * 
 * @param results A array of bullets containing the results of this function
 * @param number_of_bullets The number of bullets to create
 * @param start_x The x position where these bullets are being 'fired' from
 * @param start_y The y position where these bullets are being 'fired' from
 * @param sprite The sprite that these bullets will use for drawning. Not that
 * the sprite can be used for multiple bullets to save memory, so each bullet
 * does not own the sprite passed to it, and thus that sprite must be freed
 * elseware
 *
 * @return 0 on success, error otherwise
 */
int bullet_create_basic(bullet **results[], int number_of_bullets, int start_x,
                        int start_y, sprite *sprite);

#endif
