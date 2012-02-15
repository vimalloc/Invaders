#include "errors.h"
#include "alien.h"
#include "sprite.h"

#define BASIC_ALIEN_SPEED 4

alien_t* alien_basic_init() {
    alien_t *alien;

    alien = malloc(sizeof(alien_t));
    if(!alien)
        system_error("malloc error in alien_basic_init");

    ship_init(&(alien->ship), sprite_get_player_ship(), BASIC_ALIEN_SPEED);

    alien->health = 25;

    /* Set the alien ship to the middle of the screen for testing */
    alien->ship->xpos = 320;
    alien->ship->ypos = 100;

    return alien;
}

void alien_free(alien_t *alien) {
    ship_free(alien->ship);
}

int alien_process_damage(alien_t *alien, int damage) {
    alien->health -= damage;
    return alien->health <= 0;
}

