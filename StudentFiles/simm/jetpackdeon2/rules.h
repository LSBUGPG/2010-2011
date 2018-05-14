#ifndef rules_h
#define rules_h

class player_instance;

class object & load_deon(void);
void collide(player_instance & instance, const float * position, float radius);

#endif
