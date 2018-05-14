class object & load_player(void);
enum control { none, up, down, left, right };
enum keystate { press, release };
void control_player(control action, keystate state);
