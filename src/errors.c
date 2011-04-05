#include "errors.h"

/* TODO - find a way to get this at runtime instead of having to remember to
 * update this */
static const unsigned int NUM_OF_ERROR = 3;

static struct {
    int errcode;
    char* errstring;
} errcodes[] = {
    {ERR_MALLOC, "An error occured during a malloc"},
    {ERR_SDL, "An unknown SDL error occured"},
    {ERR_SDL_INIT, "SDL was unable to properly initalize"}
};

const char* err_string(int errcode)
{
    unsigned int i;

    for(i=0; i<NUM_OF_ERROR; i++) {
        if(errcodes[i].errcode == errcode)
            return errcodes[i].errstring;
    }

    return "Unknown error";
}
