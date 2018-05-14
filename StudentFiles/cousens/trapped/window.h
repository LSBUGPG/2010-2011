#include "rules.h"

class object & load_windows(const char * image,
                                  const char * spawn_audio,
                                  const char * hit_audio,
                                       float radius);
void spawn_window(void);
bool hit_windows(const float * position, float radius);
void expire_window(class window_instance & window);