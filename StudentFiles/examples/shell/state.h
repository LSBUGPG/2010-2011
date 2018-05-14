#include "object.h"

class state : public object {
public:
     virtual void enter() = 0;
     virtual void leave() = 0;
};

state* legal_state();
state* logo_state();
state* title_state();
state* instructions_state();
state* introduction_state();
state* game_state();
state* gameover_state();
state* credits_state();

void change_state(state* next);

object* load_shell();