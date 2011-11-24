#include "sprite.h"
#include "errors.h"

#include <assert.h>
#include <stdlib.h>

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
