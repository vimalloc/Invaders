#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"
#include "ship.h"
#include "gun.h"
#include "bullet.h"
#include "alien.h"

/* Width of the screen for the playable game area */
#define GAME_WIDTH 640

/* Height of the screen for the playable game area */
#define GAME_HEIGHT 480

/* How many pixels the player moves per update */
#define PLAYER_SPEED 4

void game_state_init(game_state_t **state) {
    int ship_height;
    int ship_width;

    *state = malloc(sizeof(game_state_t));
    if(!*state)
        system_error("malloc error on game_state_init");

    /* Init the linked list to hold bullets */
    (**state).bullets = ll_init();

    /* Load the players ship for this game */
    ship_init(&(**state).player_ship, sprite_get_player_ship(), PLAYER_SPEED);

    /* Center the ships position on the game board */
    ship_height = ship_get_height((**state).player_ship);
    ship_width = ship_get_width((**state).player_ship);
    (**state).player_ship->ypos = GAME_HEIGHT - ship_height;
    (**state).player_ship->xpos = (GAME_WIDTH + ship_width) / 2;

    /* Set the movement to zero by default */
    (**state).player_move_up = 0;
    (**state).player_move_down = 0;
    (**state).player_move_left = 0;
    (**state).player_move_right = 0;
    (**state).player_fire = 0;

    /* TODO - TESTING */
    (**state).alien = alien_basic_init();
}


void game_state_free(game_state_t* state) {
    assert(state);

    ll_free(state->bullets);
    ship_free(state->player_ship);
    free(state);
}


int game_state_get_width() {
    return GAME_WIDTH;
}


int game_state_get_height() {
    return GAME_HEIGHT;
}


static void move_ship_up(ship_t *ship) {
    ship->ypos -= ship_get_speed(ship);
    if(ship->ypos < 0)
        ship->ypos = 0;
}

static void move_ship_down(ship_t *ship) {
    ship->ypos += ship_get_speed(ship);
    if(ship->ypos + ship_get_height(ship) > GAME_HEIGHT)
        ship->ypos = GAME_HEIGHT - ship_get_height(ship);
}


static void move_ship_left(ship_t *ship) {
    ship->xpos -= ship_get_speed(ship);
    if(ship->xpos < 0)
        ship->xpos = 0;
}


static void move_ship_right(ship_t *ship) {
    ship->xpos += ship_get_speed(ship);
    if(ship->xpos + ship_get_width(ship) > GAME_WIDTH)
        ship->xpos = GAME_WIDTH - ship_get_width(ship);
}

static void process_player_actions(game_state_t *state) {
    bullet_t *bullet;

    if(state->player_move_up)
        move_ship_up(state->player_ship);

    if(state->player_move_down)
        move_ship_down(state->player_ship);

    if(state->player_move_left)
        move_ship_left(state->player_ship);

    if(state->player_move_right)
        move_ship_right(state->player_ship);

    if(state->player_fire) {
        /* Hard coded to fire from the center of the player ship, will fix
         * this in a more proper manner later TODO */
        bullet = gun_fire(state->player_ship->xpos + 9,
                          state->player_ship->ypos,
                          state->player_ship->gun);

        /* If a bullet was fired, add it to the bullets linked list */
        if(bullet) {
            ll_insert(state->bullets, bullet);
        }
    }
}

static void update_gun_charge(game_state_t *state) {
    gun_recharge(state->player_ship->gun);
}

/* Returns the alien ship this bullet colided with if a collision occurred,
 * or NULL otherwise */
static alien_t* check_alien_colisions(game_state_t *state, bullet_t *bullet) {
    /*
     * This is based on Charles Brentana's answer this stack overflow question:
     * http://stackoverflow.com/questions/306316
     *
     * For visualization see: http://silentmatt.com/rectangle-intersection/
     */

    /*
     * bx1 = bullets x position
     * bx2 = bullets x position + bullet width
     * by1 = bullets y position
     * by2 = bullets y position + bullet height
     * sx1 = alien x posision
     * sx2 = alien x position + alien width
     * sy1 = alien y position
     * sy2 = alien y position + alien height
     */
    int bx1, bx2, by1, by2, sx1, sx2, sy1, sy2;
    ship_t *ship;   /* The ship struct for the alien ship */

    ship = state->alien->ship;
    bx1 = bullet->xpos;
    bx2 = bx1 + bullet_get_width(bullet);
    by1 = bullet->ypos;
    by2 = bx2 + bullet_get_height(bullet);
    sx1 = ship->xpos;
    sx2 = sx1 + ship_get_width(ship);
    sy1 = ship->ypos;
    sy2 = sy1 + ship_get_height(ship);

    if(bx1 < sx2 &&
       bx2 > sx1 &&
       by1 < sy2 &&
       by2 > sy1)
        return state->alien;

    return NULL;
}

static void process_bullets(game_state_t *state) {
    ll_node_t *node;
    ll_node_t *next_node;
    bullet_t *bullet;
    alien_t *colided;   /* alien ship a bullet colided with */

    node = ll_get_first_node(state->bullets);
    while(node) {
        /* This is so we can remove a node from the linked list if the bullet
         * without having to do any special checks */
        next_node = ll_next_node(state->bullets, node);

        /* Update positions */
        bullet = (bullet_t *)ll_get_item(node);
        bullet_update_position(bullet);

        /* If the bullet is out of the screen then free it. Otherwise, check
         * and proccess colisions */
        if(bullet->ypos < 0 || bullet->ypos > GAME_HEIGHT ||
           bullet->xpos < 0 || bullet->xpos > GAME_WIDTH) {
            ll_remove(node);
            bullet_free(bullet);
        }
        else {
           colided =  check_alien_colisions(state, bullet);
           if(colided) {
                /* TODO - Process damage, etc with the colision */
                ll_remove(node);
                bullet_free(bullet);
           }
        }

        node = next_node;
    }
}

void game_state_update(game_state_t *state) {
    update_gun_charge(state);      /* Update the guns charge */
    process_player_actions(state); /* Handle players input actions */
    process_bullets(state);        /* Process gun fire movement and colisions */

    /* TODO - Process alien actions */
}
