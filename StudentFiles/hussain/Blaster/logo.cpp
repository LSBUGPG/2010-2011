#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

class logo: public state {
     int texture;
     float timer;

public:
     logo(void) {
          texture = load_bitmap("logo.png");
     }

     void enter(void) {
          reset();
     }

     void reset(void) {
          timer = 5.0f;
          skip = false;
     }

     void update(float time) {
          if (skip) {
               timer = 0.0f;
          }
          if (timer > time) {
               timer -= time;
          } else {
               change_state(title_state());
          }
     }

     void draw(void) {
          float position[] = { 0.0f, 0.0f };
          float size[2] = { 64.0f, 64.0f };
          draw_bitmap(texture, position, size, radius);
     }

     void leave(void) {
     }
};

state * logo_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static logo instance;
          singleton = &instance;
     }
     return singleton;
}
