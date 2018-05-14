extern bool skip;   // skip the current screen
extern bool start;  // only used to start the game

// gameplay controls
enum control { none, warp, left, right, fire };
enum keystate { press, release };
void control_ship(control action, keystate state);
