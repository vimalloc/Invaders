#ifndef GUN_H
#define GUN_H

/* Handle for all gun related stuff */
typedef struct {
    int recharge_rate;  /* How ofter this gun can fire */
    int current_charge; /* Time until this gun can fire again */
} gun_t;

/* Init */
void gun_init(gun_t **g, int recharge_rate);

/* Free */
void gun_free(gun_t *g);

/* Fire, returns a bullet that was fired from this gun, or NULL if it isn't
 * ready to be fired again yet */
void gun_fire(gun_t *g);

/* Recharges this gun by 1 step. Once the gun is fully recharged, current_charge
 * will be set to zero */
void gun_recharge(gun_t *g);

#endif

