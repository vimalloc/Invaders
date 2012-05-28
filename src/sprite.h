#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

/* Handle for a sprite */
typedef struct {
    SDL_Surface *pic;
} sprite_t;

/**
 * Load a bmp file into a sprite
 *
 * @param s The sprite to load a bmp image into
 * @param file The file path of the bmp image to load
 * @return 0 on success, error (< 0) on failure
 */
sprite_t* sprite_load_bmp(char *file);

/**
 * Frees all the memory used by this sprite.
 *
 * @param s The sprite to free
 */
void sprite_free(sprite_t *s);

/* Returns the width of this sprite */
int sprite_width(sprite_t *s);

/* Returns the height of this sprite */
int sprite_height(sprite_t *s);

/* Returns the sprite for the basic bullet */
sprite_t* sprite_get_basic_bullet();

/* Returns the sprite for the player ship */
sprite_t* sprite_get_player_ship();

/* Returns the sprite for the basic alien ship */
sprite_t* sprite_get_basic_alien_ship();

#endif
