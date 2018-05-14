
class object & load_player(const char * image, float radius);
class object & load_drifter(const char * image);
enum control { none, up, down, left, right };
enum keystate { press, release };
void control_player(control action, keystate state);
void spawn_player();
void kill_player();
