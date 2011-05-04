#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

/* Handle for a sprite */
typedef struct {
    SDL_Surface *pic;
} sprite;

/**
 * Load a bmp file into a sprite
 *
 * @param s The sprite to load a bmp image into
 * @param file The file path of the bmp image to load
 * @return 0 on success, error (< 0) on failure
 */
int sprite_load_bmp(sprite** s, char* file);

/**
 * Frees all the memory used by this sprite.
 *
 * @param s The sprite to free
 */
void sprite_free(sprite* s);

#endif
