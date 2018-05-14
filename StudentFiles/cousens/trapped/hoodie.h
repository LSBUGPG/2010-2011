#include "rules.h"

class object & load_hoodies(const char * image,
                                  const char * spawn_audio,
                                  const char * hit_audio,
                                       float radius);
void spawn_hoodie(void);
bool hit_hoodies(const float * position, float radius);
void expire_hoodie(class hoodie_instance & hoodie);