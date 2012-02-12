#include <assert.h>
#include <stdlib.h>

#include "sprite.h"
#include "errors.h"

/* Temp, to get this working. Will Change so that sprite.c owns all sprites */
static sprite_t *basic_bullet;

void sprite_load_bmp(sprite_t **s, char *file) {
    *s = malloc(sizeof(sprite_t));
    if(!s)
        system_error("malloc error in sprite_load_bmp");

    (**s).pic = SDL_LoadBMP(file);
    if(!(**s).pic)
        app_error(strcat(file, ": Couldn't be loaded into a sprite"));
}

void sprite_free(sprite_t* s) {
    assert(s);

    free(s->pic);
	free(s);
}

int sprite_width(sprite_t *s) {
    return s->pic->w;
}

int sprite_height(sprite_t *s) {
    return s->pic->h;
}

sprite_t* sprite_get_basic_bullet() {
    /* Basically a singleton */
    if(!basic_bullet) {
        sprite_load_bmp(&basic_bullet, "../images/basic_bullet.bmp");
    }

    return basic_bullet;
}
