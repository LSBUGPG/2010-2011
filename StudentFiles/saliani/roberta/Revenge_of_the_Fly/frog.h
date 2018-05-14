#include "rules.h"

class object & load_frogs(const char * image,
                                  const char * spawn_audio,
                                  const char * hit_audio,
                                       float radius);
void spawn_frog(void);
bool hit_frogs(const float * position, float radius);
void expire_frog(class frog_instance & frog);