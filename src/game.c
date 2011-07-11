#include <assert.h>
#include <stdio.h>

#include "game.h"
#include "errors.h"

/* Screen update settings */
enum {
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

    g->surface = SDL_SetVideoMode(game_state_get_width(),
        game_state_get_height(), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(g->surface == NULL)
        return ERR_SDL_INIT;

    return HUGE_SUCCESS;
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
                g->state->player_move_up = 1;
            if(g->event->key.keysym.sym == SDLK_DOWN)
                g->state->player_move_down = 1;
            if(g->event->key.keysym.sym == SDLK_LEFT)
                g->state->player_move_left = 1;
            if(g->event->key.keysym.sym == SDLK_RIGHT)
                g->state->player_move_right = 1;
            if(g->event->key.keysym.sym == SDLK_SPACE)
                g->state->player_fire = 1;
        }

        else if(g->event->type == SDL_KEYUP) {
            if(g->event->key.keysym.sym == SDLK_UP)
                g->state->player_move_up = 0;
            if(g->event->key.keysym.sym == SDLK_DOWN)
                g->state->player_move_down = 0;
            if(g->event->key.keysym.sym == SDLK_LEFT)
                g->state->player_move_left = 0;
            if(g->event->key.keysym.sym == SDLK_RIGHT)
                g->state->player_move_right = 0;
            if(g->event->key.keysym.sym == SDLK_SPACE)
                g->state->player_fire = 0;
        }
    }
}

static void game_draw_player(game* g)
{
    SDL_Rect DestR;

    if(g->surface == NULL || g->state->player_ship->sprite->pic == NULL)
        assert(0);

    DestR.x = g->state->player_ship->xpos;
    DestR.y = g->state->player_ship->ypos;

    SDL_BlitSurface(g->state->player_ship->sprite->pic, NULL, g->surface, &DestR);
}

static void game_update_display(game *g, float interpolation)
{
    /* Prepare the background for redrawing */
    SDL_FillRect(g->surface, NULL, 0x000000);

    /* Add the player to the new surface */
    game_draw_player(g);

    /* Draw the new surface */
    SDL_Flip(g->surface);
}

static void game_update(game *g)
{
    game_handle_input(g);
    game_state_update(g->state);
}

int game_init(game **g)
{
    int error;

    *g = malloc(sizeof(game));
    if(!*g)
        return ERR_MALLOC;

    (**g).event = malloc(sizeof(SDL_Event));
    if(!(**g).event)
        return ERR_MALLOC;

    error = game_state_init(&((**g).state));
    if(error != HUGE_SUCCESS) {
        free(*g);
        return error;
    }

    error = game_sdl_init(*g);
    if(error != HUGE_SUCCESS) {
        game_state_free((**g).state);
        free(*g);
        return error;
    }

    return HUGE_SUCCESS;
}

void game_free(game *g)
{
    assert(g);

    game_state_free(g->state);
    SDL_FreeSurface(g->surface);
    SDL_Quit();
    free(g);
}

int game_start(game *g)
{
    /* The next time that the game state should be updated */
    unsigned int next_game_tick;

    /* The number of frames that have been skipped to try and keep the game
     * state updating 60 times a second */
    unsigned int frame_skip;

    assert(g);

    /* Game loop */
    g->running = 1;
    next_game_tick = SDL_GetTicks();
    while(g->running) {
        frame_skip = 0;

        while(SDL_GetTicks() > next_game_tick && frame_skip <= MAX_FRAMESKIP) {
            game_update(g);
            next_game_tick += SKIP_TICKS;
            frame_skip++;
        }

        /* The current time inbetween game state updates used to guess where
         * objects should be drawn (interpolation) */
        game_update_display(g, (float) (SDL_GetTicks() + SKIP_TICKS
                            - next_game_tick) / (float) (SKIP_TICKS));
    }

    return HUGE_SUCCESS;
}

int main()
{
    int error;
    game *g;

    error = game_init(&g);
    if(error != HUGE_SUCCESS) {
        printf("%s \n", err_string(error));
        return error;
    }

    /* main loop */
    error = game_start(g);
    if(error != HUGE_SUCCESS) {
        printf("%s \n", err_string(error));
    }

    /* cleanup */
    game_free(g);
    return error;
}
