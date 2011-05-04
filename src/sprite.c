#include "sprite.h"
#include "errors.h"

#include <assert.h>
#include <stdlib.h>

int sprite_load_bmp(sprite **s, char *file)
{
    /* Format this sprite to go with the background display */
    /*
    SDL_Surface *tmp = NULL;
    if((tmp = SDL_LoadBMP(file)) == NULL)
        return ERR_SPRITE;

    s->pic = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    */

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
