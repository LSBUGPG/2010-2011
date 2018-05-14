#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

class introduction: public state {
     int line;
     float size[2];
     float timer;
public:
     introduction(void) {
          TTF_Font * font = load_font("LiberationMono-Italic.ttf", 16);
          if (font) {
               line = load_text_line(font, "Story goes here...", size);
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
               change_state(game_state());
          }
     }

     void draw(void) {
          float position[] = { 0.0f, 0.0f };
          draw_bitmap(line, position, size, radius);
     }

     void leave(void) {
     }
};

state * introduction_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static introduction instance;
          singleton = &instance;
     }
     return singleton;
}
