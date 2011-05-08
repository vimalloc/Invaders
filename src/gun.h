#ifndef GUN_H
#define GUN_H

/* Handle for all gun related stuff */
typedef struct {
    int recharge_rate;  /* How ofter this gun can fire */
    int current_charge; /* Time until this gun can fire again */
} gun;

/* Init */
int gun_init(gun **g, int recharge_rate);

/* Free */
void gun_free(gun *g);

/* Fire, returns a bullet that was fired from this gun, or NULL if it isn't
 * ready to be fired again yet */
void gun_fire(gun *g);

/* Recharges this gun by 1 step */
void gun_recharge(gun *g);

#endif
