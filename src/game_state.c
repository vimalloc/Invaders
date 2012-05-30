#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"
#include "ship.h"
#include "gun.h"
#include "bullet.h"
#include "alien.h"

game_state_t* game_state_init() {
    game_state_t *state;
    int ship_height;
    int ship_width;

    state = malloc(sizeof(game_state_t));
    if(!state)
        system_error("malloc error on game_state_init");

    /* Init the linked list to hold bullets */
    state->player_bullets = ll_init();
    state->alien_bullets = ll_init();

    /* Load the players ship for this game */
    state->player_ship = ship_init(sprite_get_player_ship(), PLAYER_SPEED,
                                   gun_player_basic());

    /* Center the ships position on the game board */
    ship_height = ship_get_height(state->player_ship);
    ship_width = ship_get_width(state->player_ship);
    state->player_ship->ypos = GAME_HEIGHT - ship_height;
    state->player_ship->xpos = (GAME_WIDTH + ship_width) / 2;

    /* Set the movement to zero by default */
    state->player_move_up = 0;
    state->player_move_down = 0;
    state->player_move_left = 0;
    state->player_move_right = 0;
    state->player_fire = 0;

    /* Create the level */
    state->level = level_create_basic();

    return state;
}

void game_state_free(game_state_t* state) {
    ll_node_t *node;

    assert(state);

    /* Free all of the player bullets in memory from the linked list, then
     * free the linked list itself */
    node = ll_get_first_node(state->player_bullets);
    while(node) {
        bullet_free((bullet_t*) ll_get_item(node));
        node = ll_remove(state->player_bullets, node);
    }
    ll_free(state->player_bullets);

    /* Free all of the alien bullets in memory from the linked list, then
     * free the linked list itself */
    node = ll_get_first_node(state->alien_bullets);
    while(node) {
        bullet_free((bullet_t*) ll_get_item(node));
        node = ll_remove(state->alien_bullets, node);
    }
    ll_free(state->alien_bullets);

    ship_free(state->player_ship);
    level_free(state->level);
    free(state);
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
            ll_insert(state->player_bullets, bullet);
        }
    }
}

static void update_gun_charge(game_state_t *state) {
    gun_recharge(state->player_ship->gun);
}

/* Checks if a bullets position is currently outside of the
 * boundaries of the screen */
static int bullet_out_of_screen(bullet_t *b) {
    if(b->ypos < 0 ||
       b->ypos > GAME_HEIGHT ||
       b->xpos < 0 ||
       b->xpos > GAME_WIDTH) {
        return 1;
    }
    return 0;
}


static void process_player_bullets(game_state_t *state) {
    ll_node_t *node;
    bullet_t  *bullet;

    node = ll_get_first_node(state->player_bullets);
    while(node) {
        /* Update positions */
        bullet = (bullet_t *) ll_get_item(node);
        bullet_update_position(bullet);

        /* If the bullet is out of the screen then free it.
         * Otherwise, check and process colisions */
        if(bullet_out_of_screen(bullet)) {
            node = ll_remove(state->player_bullets, node);
            bullet_free(bullet);
        }
        else if(level_process_colision(state->level, bullet)) {
            node = ll_remove(state->player_bullets, node);
            bullet_free(bullet);
        }
        else
            node = ll_next_node(state->player_bullets, node);
    }
}

static void process_alien_bullets(game_state_t *state) {
    ll_node_t *node;
    bullet_t  *bullet;

    node = ll_get_first_node(state->alien_bullets);
    while(node) {
        /* Update positions */
        bullet = (bullet_t *) ll_get_item(node);
        bullet_update_position(bullet);

        /* If the bullet is out of the screen then free it.
         * Otherwise, check and process colisions */
        if(bullet_out_of_screen(bullet)) {
            node = ll_remove(state->alien_bullets, node);
            bullet_free(bullet);
        }
        else
            node = ll_next_node(state->alien_bullets, node);
    }
}

void game_state_update(game_state_t *state) {
    ll_t *new_alien_bullets;

    update_gun_charge(state);      /* Update the guns charge */
    process_player_actions(state); /* Handle players input actions */
    process_player_bullets(state); /* Process gun fire movement and colisions */

    /* Updates the game level by 1 tick, and add all of the new bullets that
     * were fired to our alien_bullets list */
    new_alien_bullets = level_update(state->level);
    ll_append_list(new_alien_bullets, state->alien_bullets);
    ll_free(new_alien_bullets);

    /* Process the alien bullets */
    process_alien_bullets(state);
}

