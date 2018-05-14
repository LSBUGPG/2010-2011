#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

class legal: public state {
     int texture;
     float size[2];
     float timer;
public:
     legal(void) {
          TTF_Font * font = load_font("LiberationMono-Regular.ttf", 16);
          if (font) {
               texture = load_text_line(font, "License information goes here...", size);
               release_font(font);
          }
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
               change_state(logo_state());
          }
     }

     void draw(void) {
          float position[] = { 0.0f, 0.0f };
          draw_bitmap(texture, position, size);
     }

     void leave(void) {
     }
};

state * legal_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static legal instance;
          singleton = &instance;
     }
     return singleton;
}
