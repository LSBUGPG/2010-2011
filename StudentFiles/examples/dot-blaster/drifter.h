#include "rules.h"

class object& load_drifters(const char* image,
                                  const char* spawn_audio,
                                  const char* hit_audio,
                                       float radius);
void spawn_drifter();
bool hit_drifters(const float* position, float radius);
void expire_drifter(class drifter_instance& drifter);