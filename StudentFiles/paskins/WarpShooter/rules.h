#ifndef rules_h
#define rules_h

class shot_instance;
class player_instance;

class object & load_warpshooter(void);
void collide(shot_instance & instance, const float * position, float radius);
void collide(player_instance & instance, const float * position, float radius);

#endif
