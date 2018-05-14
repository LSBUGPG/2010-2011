#include "rules.h"

class object* load_ball_object(const char* image, const char* audio);
void bounce_ball();
void toss_ball();
void hold_ball(float* position);
void hit_ball(table_side side, float power);
void remove_ball_from_play();
