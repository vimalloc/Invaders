#include <assert.h>
#include <stdio.h>

#include "game.h"
#include "errors.h"

/* Screen and game state update settings */
enum {
    /* How many times per second we want to update the game state */
    TICKS_PER_SECOND = 60,

    /* Milliseconds between when each game state update should occur */
    SKIP_TICKS = 1000 / TICKS_PER_SECOND,

    /* The maximum number of frames that can be skipped */
    MAX_FRAMESKIP = 10,

    /* Width of the screen for the playable game area */
    GAME_WIDTH = 640,

    /* Height of the screen for the playable game area */
    GAME_HEIGHT = 480,
};


static int game_sdl_init(game *g)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return ERR_SDL_INIT;

    if((g->surface = SDL_SetVideoMode(GAME_WIDTH, GAME_HEIGHT, 32,
                     SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
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

        else if(g->event->type == SDL_KEYDOWN) {
            if(g->event->key.keysym.sym == SDLK_UP)
                g->up_button = 1;
            if(g->event->key.keysym.sym == SDLK_DOWN)
                g->down_button = 1;
            if(g->event->key.keysym.sym == SDLK_LEFT)
                g->left_button = 1;
            if(g->event->key.keysym.sym == SDLK_RIGHT)
                g->right_button = 1;
        }

        else if(g->event->type == SDL_KEYUP) {
            if(g->event->key.keysym.sym == SDLK_UP)
                g->up_button = 0;
            if(g->event->key.keysym.sym == SDLK_DOWN)
                g->down_button = 0;
            if(g->event->key.keysym.sym == SDLK_LEFT)
                g->left_button = 0;
            if(g->event->key.keysym.sym == SDLK_RIGHT)
                g->right_button = 0;
        }
    }
}

static void game_process_movement(game *g)
{
    if(g->up_button)
        game_state_move_up(g->state);
    if(g->down_button)
        game_state_move_down(g->state);
    if(g->left_button)
        game_state_move_left(g->state);
    if(g->right_button)
        game_state_move_right(g->state);

    printf("%i %i \n", g->state->player_ship->xpos, g->state->player_ship->ypos);
}

static void game_update_display(game *g, float interpolation)
{
    /* TODO */
}

int game_init(game *g)
{
    assert(g);

    g->up_button = 0;
    g->down_button = 0;
    g->left_button = 0;
    g->right_button = 0;

    if((g->event = (SDL_Event *) malloc(sizeof(SDL_Event))) == NULL)
        return ERR_MALLOC;

    if((g->state = (game_state *) malloc(sizeof(game_state))) == NULL)
        return ERR_MALLOC;

    if(game_state_init(g->state, GAME_WIDTH, GAME_HEIGHT) < 0)
        return ERR_MALLOC;

    if(game_sdl_init(g) < 0)
        return ERR_SDL_INIT;

    return GAME_SUCCESS;
}

void game_free(game *g)
{
    assert(g);

    game_state_free(g->state);
    free(g->state);
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
            game_process_movement(g);
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
    int error;
    game g;

    if((error = game_init(&g)) < 0) {
        printf("%s \n", err_string(error));
        return error;
    }

    /* main loop */
    if((error = game_start(&g)) < 0) {
        printf("%s \n", err_string(error));
        return error;
    }

    game_free(&g);
    return GAME_SUCCESS;
}
