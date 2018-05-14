#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

class instructions : public state {
     int texture;
     float timer;
public:
     instructions() {
          texture = load_bitmap("instructions.png");
     }

     void enter() {
          reset();
     }

     void reset() {
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
               change_state(introduction_state());
          }
     }

     void draw() {
          float position[] = { 0.0f, 0.0f };
          float size[2] = { 128.0f, 128.0f };
          draw_bitmap(texture, position, size);
     }

     void leave() {
     }
};

state* instructions_state()
{
     static state* singleton = 0;
     if (!singleton) {
          static instructions instance;
          singleton = &instance;
     }
     return singleton;
}
