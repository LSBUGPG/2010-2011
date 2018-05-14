#ifndef rules_h
#define rules_h

class object* load_ping_pong_game();
enum table_side { none, left, right };
void notify_bounce(table_side side);
void notify_out_of_play();
void serve();
void add_point(table_side side);
void notify_racket_charge(table_side side);
void notify_swing(table_side side, float power);

#endif
