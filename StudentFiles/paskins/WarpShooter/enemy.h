#include "rules.h"

class object & load_enemies(const char * image,
                                  const char * spawn_audio,
                                  const char * hit_audio,
                                       float radius);
void spawn_enemy(void);
bool hit_enemies(const float * position, float radius);
void expire_enemy(class enemy_instance & enemy);