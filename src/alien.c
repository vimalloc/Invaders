#include "errors.h"
#include "alien.h"
#include "sprite.h"
#include "gun.h"

#define BASIC_ALIEN_SPEED 4
#define BASIC_ALIEN_HEALTH 25

alien_t* alien_basic_init(int xpos, int ypos) {
    alien_t *alien;

    alien = malloc(sizeof(alien_t));
    if(!alien)
        system_error("malloc error in alien_basic_init");

    alien->ship = ship_init(sprite_get_basic_alien_ship(), BASIC_ALIEN_SPEED,
                            gun_alien_basic());

    alien->health = BASIC_ALIEN_HEALTH;
    alien->ship->xpos = xpos;
    alien->ship->ypos = ypos;

    return alien;
}

void alien_free(alien_t *alien) {
    ship_free(alien->ship);
}

int alien_process_damage(alien_t *alien, int damage) {
    alien->health -= damage;
    return alien->health <= 0;
}

