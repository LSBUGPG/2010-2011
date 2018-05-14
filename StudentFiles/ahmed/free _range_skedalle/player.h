class object & load_player(const char * image, const float * size);
enum control { none, jump, left, right, };
enum keystate { press, release };
void control_player(control action, keystate state);
