#ifndef rules_h
#define rules_h

class poison_instance;
class player_instance;

class object & load_revenge_fly(void);
void collide(poison_instance & instance, const float * position, float radius);
void collide(player_instance & instance, const float * position, float radius);

#endif
