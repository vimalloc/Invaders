#include <assert.h>

#include "game.h"

#define ERR_SDL_INIT -11
#define ERR_SDL -10
#define ERR_MALLOC -1
#define GAME_SUCCESS 0

/* Screen and game state update settings */
enum
{
    /* How many times per second we want to update the game state */
    TICKS_PER_SECOND = 60,

    /* Milliseconds between when each game state update should occur */
    SKIP_TICKS = 1000 / TICKS_PER_SECOND,

    /* The maximum number of frames that can be skipped */
    MAX_FRAMESKIP = 10,
};


static int game_sdl_init(game *g)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return ERR_SDL_INIT;

    if((g->surface = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE |
                    SDL_DOUBLEBUF)) == NULL)
        return ERR_SDL_INIT;

    return GAME_SUCCESS;
}

static void game_stop(game *g)
{
    g->running = 0;
}

static void game_handle_input(game *g)
{
    while(SDL_PollEvent(g->event)) {
        if(g->event->type == SDL_QUIT)
            game_stop(g);
    }
}

static void game_update_display(game *g, float interpolation)
{
    /* TODO */
}

int game_init(game *g)
{
    assert(g);

    if((g->event = (SDL_Event *) malloc(sizeof(SDL_Event))) == NULL)
        return ERR_MALLOC;

    if(game_sdl_init(g) < 0)
        return ERR_SDL;

    return GAME_SUCCESS;
}

void game_free(game *g)
{
    assert(g);

    free(g->event);
    SDL_FreeSurface(g->surface);
    SDL_Quit();
}

int game_start(game *g)
{
    /* The next time that the game state should be updated */
    unsigned int next_game_tick;

    /* The number of frames that have been skipped to try and keep the game
     * state updating 60 times a second */
    unsigned int frame_skip;

    assert(g);
    assert(g->surface);
    assert(g->event);

    /* Game loop */
    g->running = 1;
    next_game_tick = SDL_GetTicks();
    while(g->running) {
        frame_skip = 0;

        while(SDL_GetTicks() > next_game_tick && frame_skip <= MAX_FRAMESKIP) {
            game_handle_input(g);
            next_game_tick += SKIP_TICKS;
            frame_skip++;
        }

        /* The current time inbetween game state updates used to guess where
         * objects should be drawn (interpolation) */
        game_update_display(g, (float) (SDL_GetTicks() + SKIP_TICKS
                            - next_game_tick) / (float) (SKIP_TICKS));
    }

    return GAME_SUCCESS;
}

int main()
{
    game *g;
    int error;

    g = (game *) malloc(sizeof(game));

    error = game_init(g);
    if(error < 0)
        return error;

    error = game_start(g); /* main loop */
    if(error < 0)
        return error;

    game_free(g);
    free(g);
    return GAME_SUCCESS;
}
