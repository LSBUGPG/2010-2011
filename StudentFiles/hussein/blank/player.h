#include "rules.h"

class object & load_player(const char * image, const char * spawn_audio,
                                     const char * explode_audio, float radius);
enum control { none, thrust, left, right, fire };
enum keystate { press, release };
void control_ship(control action, keystate state);
void spawn_player();
void kill_player();