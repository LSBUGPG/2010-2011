#include "rules.h"

class object & load_evils(const char * image,
                                  const char * spawn_audio,
                                  const char * hit_audio,
                                       float radius);
void spawn_evil(void);
bool hit_evils(const float * position, float radius);
void expire_evil(class evil_instance & evil);