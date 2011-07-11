#include "errors.h"

static struct {
    int errcode;
    char* errstring;
} errcodes[] = {
    {ERR_MALLOC, "An error occured during a malloc"},
    {ERR_SDL, "An unknown SDL error occured"},
    {ERR_SDL_INIT, "SDL was unable to properly initalize"},
    {ERR_SPRITE, "Error regarding a SDL_Surface (sprite)"}
};

const char* err_string(int errcode)
{
    unsigned int i;

    for(i=0; i<(sizeof(errcodes)/sizeof(errcodes[0])); i++) {
        if(errcodes[i].errcode == errcode)
            return errcodes[i].errstring;
    }

    return "An unknown error occurred";
}
