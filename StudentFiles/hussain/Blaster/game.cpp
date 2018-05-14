#include "gameover.h"
#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

class game: public state {
     float timer;
public:
     game(void) {
     }

     void enter(void) {
          reset();
     }

     void reset(void) {
          timer = 60.0f;
          action = false;
          notify_win(false);
     }

     void update(float time) {
          bool win = true;
          if (action) {
               timer = 0.0f;
               win = false;
          }
          if (timer > time) {
               timer -= time;
          } else {
               notify_win(win);
               change_state(gameover_state());
          }
     }

     void draw(void) {
     }

     void leave(void) {
     }
};

state * game_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static game instance;
          singleton = &instance;
     }
     return singleton;
}
