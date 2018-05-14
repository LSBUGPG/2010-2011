#include "gameover.h"
#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"
#include "rules.h"

class game: public state {
     object * game_objects;
public:
     game(void) {
          game_objects = &load_dot_blaster();
     }

     void enter(void) {
          reset();
     }

     void reset(void) {
          game_objects->reset();
     }

     void update(float time) {
          game_objects->update(time);
     }

     void draw(void) {
          game_objects->draw();
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
