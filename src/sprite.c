#include "sprite.h"
#include "errors.h"

#include <assert.h>
#include <stdlib.h>

int sprite_load_bmp(sprite **s, char *file)
{
    *s = malloc(sizeof(sprite));
    if(!s)
        return ERR_MALLOC;

    if(((*s)->pic = SDL_LoadBMP(file)) == NULL)
        return ERR_SPRITE;

    return HUGE_SUCCESS;
}

void sprite_free(sprite* s)
{
    assert(s);

    free(s->pic);
	free(s);
}

int sprite_width(sprite *s)
{
    return s->pic->w;
}

int sprite_height(sprite *s)
{
    return s->pic->h;
}
