class object & load_player(const char * image, float radius);
enum control { none, thrust, left, right, fire };
enum keystate { press, release };
void control_ship(control action, keystate state);
void spawn_player();
void kill_player();