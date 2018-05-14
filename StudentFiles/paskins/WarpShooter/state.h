#include "object.h"

class state: public object {
public:
     virtual void enter(void) = 0;
     virtual void leave(void) = 0;
};

state * legal_state(void);
state * logo_state(void);
state * title_state(void);
state * instructions_state(void);
state * introduction_state(void);
state * game_state(void);
state * gameover_state(void);
state * credits_state(void);

void change_state(state * next);

object * load_shell(void);